import lldb

from utils import *

precision: int = 2
imag_char: str = 'i'

def dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    dense_matrix_type: lldb.SBType = valobj.GetType()

    if not dense_matrix_type.IsValid():
        raise RuntimeError("dense_matrix_type is invalid")

    dense_matrix_type = get_real_type(dense_matrix_type)

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

class DenseMatrixSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")

        if not columns.IsValid():
            raise RuntimeError("columns member is not valid")

        rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")

        if not rows.IsValid():
            raise RuntimeError("rows member is not valid")

        self.columns = columns
        self.rows = rows

        self.columns_int = columns.GetValueAsSigned()
        self.rows_int = rows.GetValueAsSigned()

        self.valobj = valobj

        data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        if not data.IsValid():
            raise RuntimeError("data member is not valid")

        self.data = data
        self.element_type = self.data.GetType().GetPointeeType()

        self.total_elements = self.rows_int * self.columns_int
        self.array_type = self.element_type.GetArrayType(self.total_elements)

    def num_children(self, max_children: int) -> int:
        return 3

    def get_child_index(self, name: str) -> int:
        if name == "columns":
            return 0

        if name == "rows":
            return 1

        if name == "data":
            return 2

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.columns

        if index == 1:
            return self.rows

        if index == 2:
            return self.data.CreateValueFromAddress(
                "data",
                self.data.GetValueAsUnsigned(),
                self.array_type
            )

        return None

def to_string_dm(debugger: lldb.SBDebugger, command: str, result: lldb.SBCommandReturnObject, internal_dict):
    target: lldb.SBTarget = debugger.GetSelectedTarget()

    if not target.IsValid():
        result.PutError("target was invalid")
        return

    frame: lldb.SBFrame = target.GetProcess().GetSelectedThread().GetSelectedFrame()

    if not frame.IsValid():
        result.PutError("frame was invalid")
        return

    valobj: lldb.SBValue = frame.FindVariable(command)

    if not valobj.IsValid():
        result.PutError("valobj was invalid")
        return

    valobj = valobj.GetNonSyntheticValue()

    summary = dense_matrix_summary(valobj, internal_dict)

    summary = summary.replace("}, {", "},\n     {")

    summary = summary[1:-1]

    result.PutCString("{\n     " + summary + "\n}")