import lldb
from enum import Enum

precision: int = 2


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


def get_str_from_value(value: lldb.SBValue, scalar_type: ScalarType) -> str:
    if scalar_type == ScalarType.Floating:
        value_as_float: float = float(value.value)

        print(f"Got value_as_float = {value_as_float}")

        value_as_float_rounded: float = round(value_as_float, precision)

        print(f"Got value_as_float_rounded = {value_as_float_rounded}")

        value_as_str: str = str(value_as_float_rounded)

        print(f"Got value_as_str = {value_as_str}")

        return value_as_str

    if scalar_type == ScalarType.Integer:
        value_as_str: str = value.value

        print(f"Got value_as_str = {value_as_str}")

        return value_as_str

    if scalar_type == ScalarType.ComplexFloating:
        print(f"get_str_from_value value ={value} ")

        real: lldb.SBValue = value.GetChildMemberWithName("__re_")

        if real is None or not real.IsValid():
            return "N/A real invalid"

        print(f"Got real as {real}")

        imag: lldb.SBValue = value.GetChildMemberWithName("__im_")

        if imag is None or not imag.IsValid():
            return "N/A imag invalid"

        print(f"Got imag as {imag}")

        real_str = get_str_from_value(real, ScalarType.Floating)

        print(f"Got real_str as {real_str}")

        imag_str = get_str_from_value(imag, ScalarType.Floating)

        print(f"Got imag_str as {imag_str}")

        if imag_str.startswith('-'):
            return real_str + " - " + imag_str.removeprefix('-') + "i"
        else:
            return real_str + " + " + imag_str + "i"

    if scalar_type == ScalarType.ComplexInteger:
        print(f"get_str_from_value value ={value} ")

        real: lldb.SBValue = value.GetChildMemberWithName("__re_")

        if real is None or not real.IsValid():
            return "N/A real invalid"

        print(f"Got real as {real}")

        imag: lldb.SBValue = value.GetChildMemberWithName("__im_")

        if imag is None or not imag.IsValid():
            return "N/A imag invalid"

        print(f"Got imag as {imag}")

        real_str = get_str_from_value(real, ScalarType.Integer)

        print(f"Got real_str as {real_str}")

        imag_str = get_str_from_value(imag, ScalarType.Integer)

        print(f"Got imag_str as {imag_str}")

        if imag_str.startswith('-'):
            return real_str + " - " + imag_str.removeprefix('-') + "i"
        else:
            return real_str + " + " + imag_str + "i"

    return "N/A"


def iterate_data_array(data_ptr: lldb.SBValue, index: int) -> lldb.SBValue:
    element_type = data_ptr.GetType().GetPointeeType()
    offset = index * element_type.GetByteSize()

    return data_ptr.CreateChildAtOffset(f"[{index}]", offset, element_type)


def dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    dense_matrix_type: lldb.SBType = valobj.GetType()

    if not dense_matrix_type.IsValid():
        raise RuntimeError("dense_matrix_type is invalid")

    print(f"Got dense_matrix_type = {dense_matrix_type}")

    t_type = dense_matrix_type.GetTemplateArgumentType(0)

    if not t_type.IsValid():
        raise RuntimeError("t_type is invalid")

    print(f"Got t_type = {t_type}")

    scalar_type = scalar_type_from_type(t_type)

    print(f"Got scalar_type = {scalar_type}")

    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")

    if not columns.IsValid():
        raise RuntimeError("columns member is not valid")

    columns_int: int = columns.GetValueAsSigned()

    print(f"Got columns_int = {columns_int}")

    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")

    if not rows.IsValid():
        raise RuntimeError("rows member is not valid")

    rows_int: int = rows.GetValueAsSigned()

    print(f"Got rows_int = {rows_int}")

    if columns_int == 0 or rows_int == 0:
        raise RuntimeError("empty dense matrix")

    if columns_int > 5 or rows_int > 5:
        print("matrix was too big")
        return ""

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if not data.IsValid():
        raise RuntimeError("data member is not valid")

    if data.GetValueAsSigned() == 0:
        raise RuntimeError("data member is nullptr")

    print(f"Got data = {data}")

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "{"
        for c in range(0, columns_int):
            index: int = c * rows_int + r

            print(f"Got index = {index}")

            cur_element_data: lldb.SBValue = iterate_data_array(data, index)

            if not cur_element_data.IsValid():
                raise RuntimeError(f"cur_element at (c = {c}, r = {r}, index = {index}) is not valid")

            print(f"Got cur_element_data = {cur_element_data}")

            cur_element = get_str_from_value(cur_element_data, scalar_type)

            print(f"Got cur_element = {cur_element}")

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
