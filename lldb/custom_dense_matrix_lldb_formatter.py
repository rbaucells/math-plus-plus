from utils import *
import lldb

def custom_dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    custom_dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_matrix_type.GetTemplateArgumentType(0))

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

    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "{"

        for c in range(0, columns_int):
            cur_element_data: lldb.SBValue = iterate_data_array(data, c * stride_int + r)

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

class CustomDenseMatrixSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
        self.columns_int: int = self.columns.GetValueAsUnsigned()

        self.rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
        self.rows_int: int = self.rows.GetValueAsUnsigned()

        self.stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
        self.stride_int: int = self.stride.GetValueAsUnsigned()

        self.data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.data_array_type: lldb.SBType = self.element_type.GetArrayType(self.stride_int * (self.columns_int - 1) + self.rows_int)
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.columns_int * self.rows_int)

    def num_children(self, max_children: int) -> int:
        return 5

    def get_child_index(self, name: str) -> int:
        if name == "rows":
            return 0

        if name == "columns":
            return 1

        if name == "stride_":
            return 2

        if name == "view":
            return 3

        if name == "data_":
            return 4

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.rows

        if index == 1:
            return self.columns

        if index == 2:
            return self.stride

        if index == 3:
            data: lldb.SBData = lldb.SBData()

            for c in range(0, self.columns_int):
                for r in range(0, self.rows_int):
                    cur_value: lldb.SBValue = iterate_data_array(self.data, c * self.stride_int + r)
                    data.Append(cur_value.GetData())

            return self.valobj.CreateValueFromData(
                "view",
                data,
                self.view_array_type
            )

        if index == 4:
            return self.valobj.CreateValueFromAddress(
                "data_",
                self.data.GetValueAsUnsigned(),
                self.data_array_type
            )

        return None

def to_string(valobj: lldb.SBValue) -> str:
    custom_dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_matrix_type.GetTemplateArgumentType(0))

    rows: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    rows_int: int = rows.GetValueAsUnsigned()
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()
    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    view_summary: str = "{"

    for r in range(0, rows_int):
        view_summary += "\n    {"

        for c in range(0, columns_int):
            cur_element_data: lldb.SBValue = iterate_data_array(data, c * stride_int + r)

            if cur_element_data.IsValid():
                cur_element = get_str_from_value(cur_element_data, scalar_type)
            else:
                cur_element = "N/A"


            if c != columns_int - 1:
                view_summary += f"{cur_element}, "
            else:
                view_summary += cur_element

        if r != rows_int - 1:
            view_summary += "},"
        else:
            view_summary += "}"

    view_summary += "\n}"

    data_summary = "{"

    for i in range(0, stride_int * (columns_int - 1) + rows_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i)

        if cur_element_data.IsValid():
            cur_element = get_str_from_value(cur_element_data, scalar_type)
        else:
            cur_element = "N/A"


        if i != (stride_int * (columns_int - 1) + rows_int) - 1:
            data_summary += f"{cur_element}, "
        else:
            data_summary += cur_element

    data_summary += "}"

    return f"rows = {rows_int}\ncolumns = {columns_int}\nstride_ = {stride_int}\nview = {view_summary}\ndata_ = {data_summary}"