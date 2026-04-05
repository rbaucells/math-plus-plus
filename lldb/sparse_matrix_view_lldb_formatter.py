import textwrap

from utils import *
import lldb
import sparse_matrix_lldb_formatter


class SparseMatrixViewSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.columns: lldb.SBValue = valobj.GetChildMemberWithName("columns_")
        self.columns_int: int = self.columns.GetValueAsUnsigned()

        self.rows: lldb.SBValue = valobj.GetChildMemberWithName("rows_")
        self.rows_int: int = self.rows.GetValueAsUnsigned()

        self.col_offset: lldb.SBValue = valobj.GetChildMemberWithName("colOffset_")
        self.col_offset_int: int = self.col_offset.GetValueAsUnsigned()

        self.row_offset: lldb.SBValue = valobj.GetChildMemberWithName("rowOffset_")
        self.row_offset_int: int = self.row_offset.GetValueAsUnsigned()

        self.owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

        owner_columns: lldb.SBValue = self.owner.GetChildMemberWithName("columns_")
        self.owner_columns_int: int = owner_columns.GetValueAsUnsigned()

        owner_rows: lldb.SBValue = self.owner.GetChildMemberWithName("rows_")
        self.owner_rows_int: int = owner_rows.GetValueAsUnsigned()

        owner_nnz: lldb.SBValue = self.owner.GetChildMemberWithName("nnz_")
        self.owner_nnz_type: lldb.SBType = owner_nnz.GetType()

        self.owner_col_offsets: lldb.SBValue = self.owner.GetChildMemberWithName("colOffsets_")
        owner_row_indices: lldb.SBValue = self.owner.GetChildMemberWithName("rowIndices_")
        owner_values: lldb.SBValue = self.owner.GetChildMemberWithName("values_")

        self.owner_values_element_type: lldb.SBType = owner_values.GetType().GetPointeeType()
        self.owner_row_indices_element_type: lldb.SBType = owner_row_indices.GetType().GetPointeeType()
        self.owner_col_offsets_element_type: lldb.SBType = self.owner_col_offsets.GetType().GetPointeeType()

        self.owner_col_offsets_array_type: lldb.SBType = self.owner_col_offsets_element_type.GetArrayType(self.columns_int + 1)

    def num_children(self, max_children: int) -> int:
        return 7

    def get_child_index(self, name: str) -> int:
        if name == "rows_":
            return 0

        if name == "columns_":
            return 1

        if name == "nnz_view":
            return 2

        if name == "colOffsets_view":
            return 3

        if name == "rowIndices_view":
            return 4

        if name == "values_view":
            return 5

        if name == "owner":
            return 6

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.rows

        if index == 1:
            return self.columns

        if index == 2:
            owner_row_indices: lldb.SBValue = self.owner.GetChildMemberWithName("rowIndices_")

            nnz_int: int = calculate_nnz(
                self.col_offset_int,
                self.row_offset_int,
                self.columns_int,
                self.rows_int,
                self.owner_col_offsets,
                owner_row_indices
            )

            nnz_data: lldb.SBData = lldb.SBData.CreateDataFromInt(nnz_int)

            return self.valobj.CreateValueFromData(
                "nnz_view",
                nnz_data,
                self.owner_nnz_type
            )

        if index == 3:
            data: lldb.SBData = lldb.SBData()
            owner_row_indices: lldb.SBValue = self.owner.GetChildMemberWithName("rowIndices_")

            current_view_nnz: int = 0
            data.Append(lldb.SBData.CreateDataFromInt(0))

            for c in range(self.col_offset_int, self.col_offset_int + self.columns_int):
                start: lldb.SBValue = iterate_data_array(self.owner_col_offsets, c)
                start_int: int = start.GetValueAsUnsigned()
                end: lldb.SBValue = iterate_data_array(self.owner_col_offsets, c + 1)
                end_int: int = end.GetValueAsUnsigned()

                for r in range(start_int, end_int):
                    cur_row_idx: lldb.SBValue = iterate_data_array(owner_row_indices, r)
                    cur_row_idx_int: int = cur_row_idx.GetValueAsUnsigned()

                    if self.row_offset_int <= cur_row_idx_int < self.row_offset_int + self.rows_int:
                        current_view_nnz += 1

                data.Append(lldb.SBData.CreateDataFromInt(current_view_nnz))

            return self.valobj.CreateValueFromData(
                "colOffsets_view",
                data,
                self.owner_col_offsets_element_type.GetArrayType(self.columns_int + 1)
            )

        if index == 4:
            data: lldb.SBData = lldb.SBData()
            owner_row_indices: lldb.SBValue = self.owner.GetChildMemberWithName("rowIndices_")
            nnz_count: int = 0

            for c in range(self.col_offset_int, self.col_offset_int + self.columns_int):
                start_int: int = iterate_data_array(self.owner_col_offsets, c).GetValueAsUnsigned()
                end_int: int = iterate_data_array(self.owner_col_offsets, c + 1).GetValueAsUnsigned()

                for r in range(start_int, end_int):
                    cur_row_idx: lldb.SBValue = iterate_data_array(owner_row_indices, r)
                    cur_row_idx_int: int = cur_row_idx.GetValueAsUnsigned()

                    if self.row_offset_int <= cur_row_idx_int < self.row_offset_int + self.rows_int:
                        relative_row_int: int = cur_row_idx_int - self.row_offset_int
                        relative_row_data: lldb.SBData = lldb.SBData.CreateDataFromInt(relative_row_int)
                        data.Append(relative_row_data)
                        nnz_count += 1

            return self.valobj.CreateValueFromData(
                "rowIndices_view",
                data,
                self.owner_row_indices_element_type.GetArrayType(nnz_count)
            )

        if index == 5:
            data: lldb.SBData = lldb.SBData()
            owner_row_indices: lldb.SBValue = self.owner.GetChildMemberWithName("rowIndices_")
            owner_values: lldb.SBValue = self.owner.GetChildMemberWithName("values_")
            nnz_count: int = 0

            for c in range(self.col_offset_int, self.col_offset_int + self.columns_int):
                start_int: int = iterate_data_array(self.owner_col_offsets, c).GetValueAsUnsigned()
                end_int: int = iterate_data_array(self.owner_col_offsets, c + 1).GetValueAsUnsigned()

                for r in range(start_int, end_int):
                    cur_row_idx_int: int = iterate_data_array(owner_row_indices, r).GetValueAsUnsigned()

                    if self.row_offset_int <= cur_row_idx_int < self.row_offset_int + self.rows_int:
                        cur_val: lldb.SBValue = iterate_data_array(owner_values, r)
                        data.Append(cur_val.GetData())
                        nnz_count += 1

            return self.valobj.CreateValueFromData(
                "values_view",
                data,
                self.owner_values_element_type.GetArrayType(nnz_count)
            )

        if index == 6:
            return self.owner

        return None


def calculate_nnz(col_offset_int: int, row_offset_int: int, columns_int: int, rows_int: int, owner_col_offsets: lldb.SBValue, owner_row_indices: lldb.SBValue) -> int:
    nnz: int = 0

    for c in range(col_offset_int, col_offset_int + columns_int):
        start: lldb.SBValue = iterate_data_array(owner_col_offsets, c)
        start_int: int = start.GetValueAsUnsigned()
        end: lldb.SBValue = iterate_data_array(owner_col_offsets, c + 1)
        end_int: int = end.GetValueAsUnsigned()

        for r in range(start_int, end_int):
            cur_index: lldb.SBValue = iterate_data_array(owner_row_indices, r)
            cur_index_int: int = cur_index.GetValueAsUnsigned()

            if row_offset_int <= cur_index_int < row_offset_int + rows_int:
                nnz += 1

    return nnz


def to_string(valobj: lldb.SBValue) -> str:
    sparse_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(sparse_matrix_type.GetTemplateArgumentType(0))

    valobj: lldb.SBValue = valobj

    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns_")
    columns_int: int = columns.GetValueAsUnsigned()

    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows_")
    rows_int: int = rows.GetValueAsUnsigned()

    col_offset: lldb.SBValue = valobj.GetChildMemberWithName("colOffset_")
    col_offset_int: int = col_offset.GetValueAsUnsigned()

    row_offset: lldb.SBValue = valobj.GetChildMemberWithName("rowOffset_")
    row_offset_int: int = row_offset.GetValueAsUnsigned()

    owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

    owner_col_offsets: lldb.SBValue = owner.GetChildMemberWithName("colOffsets_")
    owner_row_indices: lldb.SBValue = owner.GetChildMemberWithName("rowIndices_")
    owner_values: lldb.SBValue = owner.GetChildMemberWithName("values_")

    nnz_view_int: int = calculate_nnz(col_offset_int, row_offset_int, columns_int, rows_int, owner_col_offsets, owner_row_indices)

    col_offsets_view_summary: str = "{0"
    row_indices_view_summary: str = "{"
    values_view_summary: str = "{"

    current_nnz_int: int = 0
    for c in range(columns_int):
        actual_col_idx: int = c + col_offset_int

        start_val: lldb.SBValue = iterate_data_array(owner_col_offsets, actual_col_idx)
        start_int: int = start_val.GetValueAsUnsigned()

        end_val: lldb.SBValue = iterate_data_array(owner_col_offsets, actual_col_idx + 1)
        end_int: int = end_val.GetValueAsUnsigned()

        for r in range(start_int, end_int):
            cur_row_idx: lldb.SBValue = iterate_data_array(owner_row_indices, r)
            cur_row_idx_int: int = cur_row_idx.GetValueAsUnsigned()

            if row_offset_int <= cur_row_idx_int < row_offset_int + rows_int:
                relative_row_int: int = cur_row_idx_int - row_offset_int
                cur_element: str = str(relative_row_int)

                if current_nnz_int != nnz_view_int - 1:
                    row_indices_view_summary += f"{cur_element}, "
                else:
                    row_indices_view_summary += cur_element

                cur_value: lldb.SBValue = iterate_data_array(owner_values, r)

                if cur_value.IsValid():
                    cur_element = get_str_from_value(cur_value, scalar_type)
                else:
                    cur_element = "N/A"

                if current_nnz_int != nnz_view_int - 1:
                    values_view_summary += f"{cur_element}, "
                else:
                    values_view_summary += cur_element

                current_nnz_int += 1

        col_offsets_view_summary += f", {str(current_nnz_int)}"

    col_offsets_view_summary += "}"
    row_indices_view_summary += "}"
    values_view_summary += "}"

    owner_summary: str = sparse_matrix_lldb_formatter.to_string(owner)
    owner_summary: str = textwrap.indent(owner_summary, "    ")

    return f"rows = {rows_int}\ncolumns = {columns_int}\nrowOffset_ = {row_offset_int}\ncolOffset_ = {col_offset_int}\nnnz_view = {nnz_view_int}\ncolOffsets_view = {col_offsets_view_summary}\nrowIndices_view = {row_indices_view_summary}\nvalues_view = {values_view_summary}\nowner_ = {{\n{owner_summary}\n}}"
