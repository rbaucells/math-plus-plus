import textwrap

from utils import *
import lldb
import dense_matrix_lldb_formatter

def dense_matrix_view_summary(valobj: lldb.SBValue, internal_dict):
    valobj: lldb.SBValue = valobj.GetNonSyntheticValue()

    dense_matrix_view_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_matrix_view_type.GetTemplateArgumentType(0))

    rows: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    rows_int: int = rows.GetValueAsUnsigned()

    if rows_int == 0:
        return "Empty Matrix View (rows_ = 0)"

    if rows_int > 5:
        return "Big Matrix View (rows_ > 5)"

    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()

    if columns_int == 0:
        return "Empty Matrix View (columns_ = 0)"

    if columns_int > 5:
        return "Big Matrix View (columns_ > 5)"

    row_offset: lldb.SBValue = valobj.GetChildMemberWithName("rowOffset_")
    row_offset_int: int = row_offset.GetValueAsUnsigned()
    col_offset: lldb.SBValue = valobj.GetChildMemberWithName("colOffset_")
    col_offset_int: int = col_offset.GetValueAsUnsigned()

    owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

    owner_data: lldb.SBValue = owner.GetChildMemberWithName("data_")
    owner_rows: lldb.SBValue = owner.GetChildMemberWithName("rows")
    owner_rows_int: int = owner_rows.GetValueAsUnsigned()

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "{"

        for c in range(0, columns_int):
            cur_element_data: lldb.SBValue = iterate_data_array(owner_data, (c + col_offset_int) * owner_rows_int + (r + row_offset_int))

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

class DenseMatrixViewSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
        self.rows_int: int = self.rows.GetValueAsUnsigned()

        self.columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
        self.columns_int: int = self.columns.GetValueAsUnsigned()

        self.row_offset: lldb.SBValue = valobj.GetChildMemberWithName("rowOffset_")
        self.row_offset_int: int = self.row_offset.GetValueAsUnsigned()

        self.col_offset: lldb.SBValue = valobj.GetChildMemberWithName("colOffset_")
        self.col_offset_int: int = self.col_offset.GetValueAsUnsigned()

        self.owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

        self.owner_data: lldb.SBValue = self.owner.GetChildMemberWithName("data_")
        owner_rows: lldb.SBValue = self.owner.GetChildMemberWithName("rows")
        self.owner_rows_int: int = owner_rows.GetValueAsUnsigned()
        owner_cols: lldb.SBValue = self.owner.GetChildMemberWithName("cols")
        self.owner_cols_int: int = owner_cols.GetValueAsUnsigned()

        self.element_type: lldb.SBType = self.owner_data.GetType().GetPointeeType()
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.columns_int * self.rows_int)

    def num_children(self, max_children: int) -> int:
        return 6

    def get_child_index(self, name: str) -> int:
        if name == "rows":
            return 0

        if name == "columns":
            return 1

        if name == "rowOffset_":
            return 2

        if name == "colOffset_":
            return 3

        if name == "view":
            return 4

        if name == "owner_":
            return 5

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.rows

        if index == 1:
            return self.columns

        if index == 2:
            return self.row_offset

        if index == 3:
            return self.col_offset

        if index == 4:
            data: lldb.SBData = lldb.SBData()

            for c in range(0, self.columns_int):
                for r in range(0, self.rows_int):
                    cur_value: lldb.SBValue = iterate_data_array(self.owner_data, (c + self.col_offset_int) * self.owner_rows_int + (r + self.row_offset_int))

                    data.Append(cur_value.GetData())

            return self.valobj.CreateValueFromData(
                "view",
                data,
                self.view_array_type
            )

        if index == 5:
            return self.owner

        return None

def to_string(valobj: lldb.SBValue) -> str:
    dense_matrix_view_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_matrix_view_type.GetTemplateArgumentType(0))

    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
    rows_int: int = rows.GetValueAsUnsigned()

    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()

    row_offset: lldb.SBValue = valobj.GetChildMemberWithName("rowOffset_")
    row_offset_int: int = row_offset.GetValueAsUnsigned()

    col_offset: lldb.SBValue = valobj.GetChildMemberWithName("colOffset_")
    col_offset_int: int = col_offset.GetValueAsUnsigned()

    owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

    owner_data: lldb.SBValue = owner.GetChildMemberWithName("data_")
    owner_rows: lldb.SBValue = owner.GetChildMemberWithName("rows")
    owner_rows_int: int = owner_rows.GetValueAsUnsigned()
    owner_cols: lldb.SBValue = owner.GetChildMemberWithName("cols")

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "\n    {"

        for c in range(0, columns_int):
            cur_element_data: lldb.SBValue = iterate_data_array(owner_data, (c + col_offset_int) * owner_rows_int + (r + row_offset_int))

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

    owner_summary: str = dense_matrix_lldb_formatter.to_string(owner)
    owner_summary: str = textwrap.indent(owner_summary, "    ")

    return f"rows = {rows_int}\ncolumns = {columns_int}\nrowOffset_ = {row_offset_int}\ncolOffset_ = {col_offset_int}\nview = {summary}\nowner_ = {{\n{owner_summary}\n}}"