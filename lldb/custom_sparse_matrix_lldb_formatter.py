from utils import *
import lldb


class CustomSparseMatrixSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
        self.columns_int: int = self.columns.GetValueAsUnsigned()

        self.rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
        self.rows_int: int = self.rows.GetValueAsUnsigned()

        nnz: lldb.SBValue = valobj.GetChildMemberWithName("nnz_").Dereference()
        self.nnz_type: lldb.SBType = nnz.GetType()

        self.col_offsets: lldb.SBValue = valobj.GetChildMemberWithName("colOffsets_").Dereference()
        row_indices: lldb.SBValue = valobj.GetChildMemberWithName("rowIndices_").Dereference()
        values: lldb.SBValue = valobj.GetChildMemberWithName("values_").Dereference()

        self.values_element_type: lldb.SBType = values.GetType().GetPointeeType()
        self.row_indices_element_type: lldb.SBType = row_indices.GetType().GetPointeeType()
        self.col_offsets_element_type: lldb.SBType = self.col_offsets.GetType().GetPointeeType()

        self.col_offsets_array_type: lldb.SBType = self.col_offsets_element_type.GetArrayType(self.columns_int + 1)

    def num_children(self, max_children: int) -> int:
        return 6

    def get_child_index(self, name: str) -> int:
        if name == "rows":
            return 0

        if name == "columns":
            return 1

        if name == "nnz_":
            return 2

        if name == "colOffsets_":
            return 3

        if name == "rowIndices_":
            return 4

        if name == "values_":
            return 5

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.rows

        if index == 1:
            return self.columns

        if index == 2:
            # we do it through data cuz it has a wierd name when i just Dereference() it
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_").Dereference()
            nnz_int: int = nnz.GetValueAsUnsigned()

            data: lldb.SBData = lldb.SBData.CreateDataFromInt(nnz_int)

            return self.valobj.CreateValueFromData(
                "nnz_",
                data,
                self.nnz_type
            )

        if index == 3:
            col_offsets: lldb.SBValue = self.valobj.GetChildMemberWithName("colOffsets_").Dereference()

            return self.valobj.CreateValueFromAddress(
                "colOffsets_",
                col_offsets.GetValueAsUnsigned(),
                self.col_offsets_array_type
            )

        if index == 4:
            row_indices: lldb.SBValue = self.valobj.GetChildMemberWithName("rowIndices_").Dereference()
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_").Dereference()
            nnz_int: int = nnz.GetValueAsUnsigned()

            row_indices_array_type: lldb.SBType = self.row_indices_element_type.GetArrayType(nnz_int)

            return self.valobj.CreateValueFromAddress(
                "rowIndices_",
                row_indices.GetValueAsUnsigned(),
                row_indices_array_type
            )

        if index == 5:
            values: lldb.SBValue = self.valobj.GetChildMemberWithName("values_").Dereference()
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_").Dereference()
            nnz_int: int = nnz.GetValueAsUnsigned()

            values_array_type: lldb.SBType = self.values_element_type.GetArrayType(nnz_int)

            return self.valobj.CreateValueFromAddress(
                "values_",
                values.GetValueAsUnsigned(),
                values_array_type
            )

        return None


def to_string(valobj: lldb.SBValue) -> str:
    custom_sparse_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_sparse_matrix_type.GetTemplateArgumentType(0))

    valobj: lldb.SBValue = valobj

    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()

    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
    rows_int: int = rows.GetValueAsUnsigned()

    nnz: lldb.SBValue = valobj.GetChildMemberWithName("nnz_").Dereference()
    nnz_int: int = nnz.GetValueAsUnsigned()

    col_offsets: lldb.SBValue = valobj.GetChildMemberWithName("colOffsets_").Dereference()
    row_indices: lldb.SBValue = valobj.GetChildMemberWithName("rowIndices_").Dereference()
    values: lldb.SBValue = valobj.GetChildMemberWithName("values_").Dereference()

    col_offsets_summary: str = "{"
    row_indices_summary: str = "{"
    values_summary: str = "{"

    for i in range(0, columns_int + 1):
        cur_offset: lldb.SBValue = iterate_data_array(col_offsets, i)

        if cur_offset.IsValid():
            cur_element = get_str_from_value(cur_offset, ScalarType.Integer)
        else:
            cur_element = "N/A"

        if i != columns_int:
            col_offsets_summary += f"{cur_element}, "
        else:
            col_offsets_summary += cur_element

    for i in range(0, nnz_int):
        cur_index: lldb.SBValue = iterate_data_array(row_indices, i)

        if cur_index.IsValid():
            cur_element = get_str_from_value(cur_index, ScalarType.Integer)
        else:
            cur_element = "N/A"

        if i != nnz_int - 1:
            row_indices_summary += f"{cur_element}, "
        else:
            row_indices_summary += cur_element

        cur_value: lldb.SBValue = iterate_data_array(values, i)

        if cur_index.IsValid():
            cur_element = get_str_from_value(cur_value, scalar_type)
        else:
            cur_element = "N/A"

        if i != nnz_int - 1:
            values_summary += f"{cur_element}, "
        else:
            values_summary += cur_element

    col_offsets_summary += "}"
    row_indices_summary += "}"
    values_summary += "}"

    return f"rows = {rows_int}\ncolumns = {columns_int}\nnnz_ = {nnz_int}\ncolOffsets_ = {col_offsets_summary}\nrowIndices_ = {row_indices_summary}\nvalues_ = {values_summary}"
