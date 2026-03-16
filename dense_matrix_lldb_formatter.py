import lldb
from enum import Enum

precision: int = 2
imag_char: str = 'i'

def __lldb_init_module(debugger: lldb.SBDebugger, dict):
    debugger.HandleCommand(
        f'type summary add -x "^DenseMatrix<.*>$" -F dense_matrix_lldb_formatter.dense_matrix_summary')
    print("Imported dense_matrix_lldb_formatter.py")


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

def is_zero(val: lldb.SBValue) -> bool:
    try:
        return float(val.value) == 0.0
    except:
        return False

def get_str_from_value(value: lldb.SBValue, scalar_type: ScalarType) -> str:
    if scalar_type == ScalarType.Floating:
        value_as_float: float = float(value.value)

        value_as_float_rounded: float = round(value_as_float, precision)

        value_as_str: str = str(value_as_float_rounded)

        return value_as_str

    if scalar_type == ScalarType.Integer:
        value_as_str: str = value.value

        return value_as_str

    if scalar_type in [ScalarType.ComplexFloating, ScalarType.ComplexInteger]:
        real: lldb.SBValue = value.GetChildMemberWithName("__re_")
        imag: lldb.SBValue = value.GetChildMemberWithName("__im_")

        if not real.IsValid() or not imag.IsValid():
            return "N/A invalid"

        inner_type: ScalarType = ScalarType.Floating if scalar_type == ScalarType.ComplexFloating else ScalarType.Integer

        real_is_zero: bool = is_zero(real)
        imag_is_zero: bool = is_zero(imag)

        if real_is_zero and imag_is_zero:
            return "0"

        if imag_is_zero:
            return get_str_from_value(real, inner_type)

        if real_is_zero:
            return get_str_from_value(imag, inner_type) + imag_char

        real_str = get_str_from_value(real, inner_type)
        imag_str = get_str_from_value(imag, inner_type)

        if imag_str.startswith('-'):
            return f"{real_str} - {imag_str.removeprefix('-')}{imag_char}"
        else:
            return f"{real_str} + {imag_str}{imag_char}"

    return "N/A"


def iterate_data_array(data_ptr: lldb.SBValue, index: int) -> lldb.SBValue:
    element_type = data_ptr.GetType().GetPointeeType()
    offset = index * element_type.GetByteSize()

    return data_ptr.CreateChildAtOffset(f"[{index}]", offset, element_type)


def dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    dense_matrix_type: lldb.SBType = valobj.GetType()

    if not dense_matrix_type.IsValid():
        raise RuntimeError("dense_matrix_type is invalid")

    t_type = dense_matrix_type.GetTemplateArgumentType(0)

    if not t_type.IsValid():
        raise RuntimeError("t_type is invalid")

    scalar_type = scalar_type_from_type(t_type)

    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")

    if not columns.IsValid():
        raise RuntimeError("columns member is not valid")

    columns_int: int = columns.GetValueAsSigned()

    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")

    if not rows.IsValid():
        raise RuntimeError("rows member is not valid")

    rows_int: int = rows.GetValueAsSigned()

    if columns_int == 0 or rows_int == 0:
        raise RuntimeError("empty dense matrix")

    if columns_int > 5 or rows_int > 5:
        return ""

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if not data.IsValid():
        raise RuntimeError("data member is not valid")

    if data.GetValueAsSigned() == 0:
        raise RuntimeError("data member is nullptr")

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "{"
        for c in range(0, columns_int):
            index: int = c * rows_int + r

            cur_element_data: lldb.SBValue = iterate_data_array(data, index)

            if not cur_element_data.IsValid():
                raise RuntimeError(f"cur_element at (c = {c}, r = {r}, index = {index}) is not valid")

            cur_element = get_str_from_value(cur_element_data, scalar_type)

            if c != columns_int - 1:
                summary += f"{cur_element}, "
            else:
                summary += cur_element

        if r != rows_int - 1:
            summary += "}, "
        else:
            summary += "}"

    summary += "}"

    return summary
