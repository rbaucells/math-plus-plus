from enum import Enum
import struct

import lldb

precision: int = 4
imag_char: str = 'i'

class ScalarType(Enum):
    Integer = 1
    Floating = 2
    ComplexInteger = 3
    ComplexFloating = 4


def scalar_type_from_type(t_type: lldb.SBType):
    flags = t_type.GetTypeFlags()

    is_integer = bool(flags & lldb.eTypeIsInteger)
    is_floating = bool(flags & lldb.eTypeIsFloat)
    is_complex = bool(flags & lldb.eTypeIsComplex)

    type_name: str = t_type.GetName()

    if len(type_name) == 0:
        raise RuntimeError("invalid t_type, cannot get ScalarType")

    if not is_complex and "complex" in type_name:
        if "float" in type_name or "double" in type_name:
            return ScalarType.ComplexFloating

        return ScalarType.ComplexInteger

    if is_integer:
        if is_complex:
            return ScalarType.ComplexInteger

        return ScalarType.Integer

    if is_floating:
        if is_complex:
            return ScalarType.ComplexFloating

        return ScalarType.Floating

    raise RuntimeError(f"could not get ScalarType for {type_name}")

def _complex_to_str(value: lldb.SBValue, scalar_type: ScalarType) -> str:
    """Render a std::complex<T> value as a string by reading raw memory.

    The C++ standard guarantees std::complex<T> is layout-compatible with T[2]
    (real part first, imaginary part second), so this works with both libc++ and
    libstdc++ regardless of their internal field naming conventions.
    """
    byte_size: int = value.GetByteSize()
    if byte_size == 0 or byte_size % 2 != 0:
        return "N/A"

    component_size: int = byte_size // 2
    addr: int = value.GetLoadAddress()
    if addr == lldb.LLDB_INVALID_ADDRESS:
        return "N/A"

    error: lldb.SBError = lldb.SBError()
    raw: bytes = bytes(value.GetTarget().GetProcess().ReadMemory(addr, byte_size, error))
    if error.Fail() or len(raw) != byte_size:
        return "N/A"

    is_float: bool = scalar_type == ScalarType.ComplexFloating
    fmt_char: str | None = (
        {4: "f", 8: "d"}.get(component_size)
        if is_float
        else {1: "b", 2: "h", 4: "i", 8: "q"}.get(component_size)
    )
    if fmt_char is None:
        return "N/A"

    real_val, imag_val = struct.unpack(f"{fmt_char}{fmt_char}", raw)

    real_zero: bool = real_val == 0
    imag_zero: bool = imag_val == 0

    if real_zero and imag_zero:
        return "0"

    real_str: str = f"{float(real_val):.{precision}g}" if is_float else str(real_val)
    imag_str: str = f"{float(imag_val):.{precision}g}" if is_float else str(imag_val)

    if imag_zero:
        return real_str
    if real_zero:
        return f"{imag_str}{imag_char}"
    if imag_val < 0:
        return f"{real_str} - {imag_str.lstrip('-')}{imag_char}"
    return f"{real_str} + {imag_str}{imag_char}"


def get_str_from_value(value: lldb.SBValue, scalar_type: ScalarType) -> str:
    if scalar_type == ScalarType.Floating:
        return f"{float(value.value):.{precision}g}"

    if scalar_type == ScalarType.Integer:
        return value.value

    if scalar_type in [ScalarType.ComplexFloating, ScalarType.ComplexInteger]:
        return _complex_to_str(value, scalar_type)

    return "N/A"


def iterate_data_array(data_ptr: lldb.SBValue, index: int) -> lldb.SBValue:
    element_type = data_ptr.GetType().GetPointeeType()
    offset = index * element_type.GetByteSize()

    return data_ptr.CreateChildAtOffset(f"[{index}]", offset, element_type)


def get_real_type(t_type: lldb.SBType) -> lldb.SBType:
    if t_type.IsPointerType():
        return t_type.GetPointeeType()

    if t_type.IsReferenceType():
        return t_type.GetDereferencedType()

    return t_type