from utils import *
import lldb

def dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_matrix_type.GetTemplateArgumentType(0))

    rows: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    rows_int: int = rows.GetValueAsUnsigned()

    if rows_int == 0:
        return "Empty Matrix (rows_ = 0)"

    if rows_int > 5:
        return "Big Matrix (rows_ > 5)"

    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()

    if columns_int == 0:
        return "Empty Matrix (columns_ = 0)"

    if columns_int > 5:
        return "Big Matrix (columns_ > 5)"

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "{"

        for c in range(0, columns_int):
            cur_element_data: lldb.SBValue = iterate_data_array(data, c * rows_int + r)

            if cur_element_data.IsValid():
                cur_element = get_str_from_value(cur_element_data, scalar_type)
            else:
                cur_element = "N/A"


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
        self.valobj: lldb.SBValue = valobj

        self.columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
        self.columns_int: int = self.columns.GetValueAsUnsigned()

        self.rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
        self.rows_int: int = self.rows.GetValueAsUnsigned()

        self.data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.array_type: lldb.SBType = self.element_type.GetArrayType(self.columns_int * self.rows_int)

    def num_children(self, max_children: int) -> int:
        return 3

    def get_child_index(self, name: str) -> int:
        if name == "rows":
            return 0

        if name == "columns":
            return 1

        if name == "data_":
            return 2

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.rows

        if index == 1:
            return self.columns

        if index == 2:
            return self.valobj.CreateValueFromAddress(
                "data_",
                self.data.GetValueAsUnsigned(),
                self.array_type
            )

        return None

def to_string(valobj: lldb.SBValue) -> str:
    dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_matrix_type.GetTemplateArgumentType(0))

    rows: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    rows_int: int = rows.GetValueAsUnsigned()
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "\n    {"

        for c in range(0, columns_int):
            cur_element_data: lldb.SBValue = iterate_data_array(data, c * rows_int + r)

            if cur_element_data.IsValid():
                cur_element = get_str_from_value(cur_element_data, scalar_type)
            else:
                cur_element = "N/A"


            if c != columns_int - 1:
                summary += f"{cur_element}, "
            else:
                summary += cur_element

        if r != rows_int - 1:
            summary += "},"
        else:
            summary += "}"

    summary += "\n}"

    return f"rows = {rows_int}\ncolumns = {columns_int}\ndata_ = {summary}"