import lldb
from enum import Enum

precision: int = 2
imag_char: str = 'i'
to_string_orientation: str = "horizontal"
# to_string_orientation: str = "vertical"

def __lldb_init_module(debugger: lldb.SBDebugger, dict):
    debugger.HandleCommand(f'type summary add -x "^DenseVector<.*>$" -F dense_vector_lldb_formatter.dense_vector_summary')
    debugger.HandleCommand(f'type synthetic add -x "^DenseVector<.*>$" --python-class dense_vector_lldb_formatter.DenseVectorSyntheticChildrenProvider')
    debugger.HandleCommand(f'command script add -f dense_vector_lldb_formatter.to_string_dv to_string_dv')


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


def get_real_type(dense_vector_type: lldb.SBType) -> lldb.SBType:
    if dense_vector_type.IsPointerType():
        return dense_vector_type.GetPointeeType()

    if dense_vector_type.IsReferenceType():
        return dense_vector_type.GetDereferencedType()

    return dense_vector_type

def dense_vector_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    dense_vector_type: lldb.SBType = valobj.GetType()

    if not dense_vector_type.IsValid():
        raise RuntimeError("dense_vector_type is invalid")

    dense_vector_type = get_real_type(dense_vector_type)

    t_type = dense_vector_type.GetTemplateArgumentType(0)

    if not t_type.IsValid():
        raise RuntimeError("t_type is invalid")

    scalar_type = scalar_type_from_type(t_type)

    n: lldb.SBValue = valobj.GetChildMemberWithName("n")

    if not n.IsValid():
        raise RuntimeError("n is invalid")

    n_int = n.GetValueAsUnsigned()

    if n_int == 0:
        raise RuntimeError("empty dense vector")

    if n_int > 7:
        return ""

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if not data.IsValid():
        raise RuntimeError("data member is not valid")

    if data.GetValueAsSigned() == 0:
        raise RuntimeError("data member is nullptr")

    summary: str = "{"

    for i in range(0, n_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i)

        if not cur_element_data.IsValid():
            raise RuntimeError(f"cur_element at index = {i}) is not valid")

        cur_element = get_str_from_value(cur_element_data, scalar_type)

        if i != n_int - 1:
            summary += f"{cur_element}, "
        else:
            summary += cur_element

    summary += "}"

    return summary

class DenseVectorSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.n = valobj.GetChildMemberWithName("n")

        if not self.n.IsValid():
            raise RuntimeError("n is invalid")

        self.n_int = self.n.GetValueAsUnsigned()

        self.valobj = valobj

        data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        if not data.IsValid():
            raise RuntimeError("data member is not valid")

        self.data = data

        self.element_type = self.data.GetType().GetPointeeType()
        self.array_type = self.element_type.GetArrayType(self.n_int)

    def num_children(self, max_children: int) -> int:
        return 2

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "data":
            return 1

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            return self.data.CreateValueFromAddress(
                "data",
                self.data.GetValueAsUnsigned(),
                self.array_type
            )

        return None

def to_string_dv(debugger: lldb.SBDebugger, command: str, result: lldb.SBCommandReturnObject, internal_dict):
    target: lldb.SBTarget = debugger.GetSelectedTarget()

    if not target.IsValid():
        result.PutError("target was invalid")
        return "target was invalid"

    frame: lldb.SBFrame = target.GetProcess().GetSelectedThread().GetSelectedFrame()

    if not frame.IsValid():
        result.PutError("frame was invalid")
        return "frame was invalid"

    valobj: lldb.SBValue = frame.FindVariable(command)

    if not valobj.IsValid():
        result.PutError("valobj was invalid")
        return "valobj was invalid"

    valobj = valobj.GetNonSyntheticValue()

    summary = dense_vector_summary(valobj, internal_dict)

    if to_string_orientation == "vertical":
        summary = summary.replace("{", "{\n ")
        summary = summary.replace("}", "\n}")
        summary = summary.replace(",", "\n")

    result.PutCString(summary)