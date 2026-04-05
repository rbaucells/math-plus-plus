import lldb
from matrix_lldb_formatter import _MAX_VIEW_DIM, format_matrix_display, format_matrix_summary
from utils import ScalarType, get_real_type, get_str_from_value, iterate_data_array, scalar_type_from_type


def custom_sparse_matrix_summary(valobj: lldb.SBValue, internal_dict):
    # get non-synthetic value to access actual CustomSparseMatrix members
    valobj = valobj.GetNonSyntheticValue()
    # get matrix type and scalar type
    custom_sparse_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_sparse_matrix_type.GetTemplateArgumentType(0))
    # rows
    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows_")
    rows_int: int = rows.GetValueAsUnsigned()
    if rows_int == 0:
        return "Empty Matrix (rows = 0)"
    # columns
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns_")
    columns_int: int = columns.GetValueAsUnsigned()
    if columns_int == 0:
        return "Empty Matrix (columns = 0)"
    # nnz — pointer-to-pointer field: dereference to get inner pointer, then read value
    nnz_int: int = valobj.GetChildMemberWithName("nnz_").Dereference().GetValueAsUnsigned()
    # colOffsets, rowIndices, values — pointer-to-pointer fields
    col_offsets: lldb.SBValue = valobj.GetChildMemberWithName("colOffsets_").Dereference()
    row_indices: lldb.SBValue = valobj.GetChildMemberWithName("rowIndices_").Dereference()
    values: lldb.SBValue = valobj.GetChildMemberWithName("values_").Dereference()
    # null colOffsets pointer indicates moved-from state
    if col_offsets.GetValueAsSigned() == 0:
        return "Moved-from Matrix (colOffsets_ = nullptr)"
    # don't attempt to build view for very large matrices to avoid expensive data retrieval and string construction in the formatter
    if rows_int > _MAX_VIEW_DIM or columns_int > _MAX_VIEW_DIM:
        return f"CustomSparseMatrix<{rows_int}x{columns_int}> nnz={nnz_int}"

    def get_element(r: int, c: int) -> str:
        # get column range from colOffsets_
        col_start: lldb.SBValue = iterate_data_array(col_offsets, c)
        col_end: lldb.SBValue = iterate_data_array(col_offsets, c + 1)
        if not col_start.IsValid() or not col_end.IsValid():
            return "N/A"
        col_start_int: int = col_start.GetValueAsUnsigned()
        col_end_int: int = col_end.GetValueAsUnsigned()
        # search rowIndices_ for row r within the column's range
        for idx in range(col_start_int, col_end_int):
            row_idx: lldb.SBValue = iterate_data_array(row_indices, idx)
            if row_idx.IsValid() and row_idx.GetValueAsUnsigned() == r:
                # found: return formatted value
                val: lldb.SBValue = iterate_data_array(values, idx)
                return get_str_from_value(val, scalar_type) if val.IsValid() else "N/A"
        # not found: implicit sparse zero
        return "0"

    # call generic matrix summary formatter to build single-line summary string
    return format_matrix_summary(rows_int, columns_int, get_element)


class CustomSparseMatrixSyntheticChildrenProvider:

    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj
        self._refresh()

    def _refresh(self):
        # rows
        self.rows: lldb.SBValue = self.valobj.GetChildMemberWithName("rows_")
        self.rows_int: int = self.rows.GetValueAsUnsigned()
        # columns
        self.columns: lldb.SBValue = self.valobj.GetChildMemberWithName("columns_")
        self.columns_int: int = self.columns.GetValueAsUnsigned()
        # nnz — pointer-to-pointer field: dereference to read value and cache type
        nnz_deref: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_").Dereference()
        self.nnz_int: int = nnz_deref.GetValueAsUnsigned()
        self.nnz_type: lldb.SBType = nnz_deref.GetType()
        # colOffsets, rowIndices, values — pointer-to-pointer fields
        col_offsets_deref: lldb.SBValue = self.valobj.GetChildMemberWithName("colOffsets_").Dereference()
        row_indices_deref: lldb.SBValue = self.valobj.GetChildMemberWithName("rowIndices_").Dereference()
        values_deref: lldb.SBValue = self.valobj.GetChildMemberWithName("values_").Dereference()
        # element types for array view children
        self.col_offsets_element_type: lldb.SBType = col_offsets_deref.GetType().GetPointeeType()
        self.row_indices_element_type: lldb.SBType = row_indices_deref.GetType().GetPointeeType()
        self.values_element_type: lldb.SBType = values_deref.GetType().GetPointeeType()
        # array types: colOffsets has columns+1 elements; rowIndices and values have nnz elements
        self.col_offsets_array_type: lldb.SBType = self.col_offsets_element_type.GetArrayType(self.columns_int + 1)
        self.row_indices_array_type: lldb.SBType = self.row_indices_element_type.GetArrayType(self.nnz_int)
        self.values_array_type: lldb.SBType = self.values_element_type.GetArrayType(self.nnz_int)

    def update(self):
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 6

    def get_child_index(self, name: str) -> int:
        # map child name to index for rows, columns, nnz_, colOffsets_, rowIndices_, and values_ children
        if name == "rows_":
            return 0
        if name == "columns_":
            return 1
        if name == "nnz_":
            return 2
        if name == "colOffsets_":
            return 3
        if name == "rowIndices_":
            return 4
        if name == "values_":
            return 5
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int):
        # map index to child for rows, columns, nnz_, colOffsets_, rowIndices_, and values_ children
        if index == 0:
            return self.rows
        if index == 1:
            return self.columns
        if index == 2:
            # build nnz_ scalar value from cached int — direct Dereference() yields an awkward display name
            data: lldb.SBData = lldb.SBData.CreateDataFromInt(self.nnz_int)
            return self.valobj.CreateValueFromData("nnz_", data, self.nnz_type)
        if index == 3:
            col_offsets: lldb.SBValue = self.valobj.GetChildMemberWithName("colOffsets_").Dereference()
            return self.valobj.CreateValueFromAddress("colOffsets_", col_offsets.GetValueAsUnsigned(), self.col_offsets_array_type)
        if index == 4:
            row_indices: lldb.SBValue = self.valobj.GetChildMemberWithName("rowIndices_").Dereference()
            return self.valobj.CreateValueFromAddress("rowIndices_", row_indices.GetValueAsUnsigned(), self.row_indices_array_type)
        if index == 5:
            values: lldb.SBValue = self.valobj.GetChildMemberWithName("values_").Dereference()
            return self.valobj.CreateValueFromAddress("values_", values.GetValueAsUnsigned(), self.values_array_type)
        # exit
        return None


def to_string(valobj: lldb.SBValue) -> str:
    # get matrix type and scalar type
    custom_sparse_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_sparse_matrix_type.GetTemplateArgumentType(0))
    # rows
    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows_")
    rows_int: int = rows.GetValueAsUnsigned()
    # columns
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns_")
    columns_int: int = columns.GetValueAsUnsigned()
    # nnz — pointer-to-pointer field
    nnz_int: int = valobj.GetChildMemberWithName("nnz_").Dereference().GetValueAsUnsigned()
    # colOffsets, rowIndices, values — pointer-to-pointer fields
    col_offsets: lldb.SBValue = valobj.GetChildMemberWithName("colOffsets_").Dereference()
    row_indices: lldb.SBValue = valobj.GetChildMemberWithName("rowIndices_").Dereference()
    values: lldb.SBValue = valobj.GetChildMemberWithName("values_").Dereference()
    # check dimensions
    if rows_int <= _MAX_VIEW_DIM and columns_int <= _MAX_VIEW_DIM:

        def get_element(r: int, c: int) -> str:
            # get column range from colOffsets_
            col_start: lldb.SBValue = iterate_data_array(col_offsets, c)
            col_end: lldb.SBValue = iterate_data_array(col_offsets, c + 1)
            if not col_start.IsValid() or not col_end.IsValid():
                return "N/A"
            col_start_int: int = col_start.GetValueAsUnsigned()
            col_end_int: int = col_end.GetValueAsUnsigned()
            # search rowIndices_ for row r within the column's range
            for idx in range(col_start_int, col_end_int):
                row_idx: lldb.SBValue = iterate_data_array(row_indices, idx)
                if row_idx.IsValid() and row_idx.GetValueAsUnsigned() == r:
                    # found: return formatted value
                    val: lldb.SBValue = iterate_data_array(values, idx)
                    return get_str_from_value(val, scalar_type) if val.IsValid() else "N/A"
            # not found: implicit sparse zero
            return "0"

        # call generic matrix display formatter to build multi-line view string
        view_line = "view =\n" + format_matrix_display(rows_int, columns_int, get_element) + "\n"
    else:
        view_line = ""
    # build colOffsets_ summary
    col_offsets_summary: str = "{"
    for i in range(columns_int + 1):
        cur_offset: lldb.SBValue = iterate_data_array(col_offsets, i)
        element_str = get_str_from_value(cur_offset, ScalarType.Integer) if cur_offset.IsValid() else "N/A"
        # add element string to summary
        col_offsets_summary += element_str if i == columns_int else f"{element_str}, "
    col_offsets_summary += "}"
    # build rowIndices_ and values_ summaries
    row_indices_summary: str = "{"
    values_summary: str = "{"
    for i in range(nnz_int):
        cur_index: lldb.SBValue = iterate_data_array(row_indices, i)
        index_str = get_str_from_value(cur_index, ScalarType.Integer) if cur_index.IsValid() else "N/A"
        cur_value: lldb.SBValue = iterate_data_array(values, i)
        value_str = get_str_from_value(cur_value, scalar_type) if cur_value.IsValid() else "N/A"
        # add element strings to summaries
        row_indices_summary += index_str if i == nnz_int - 1 else f"{index_str}, "
        values_summary += value_str if i == nnz_int - 1 else f"{value_str}, "
    row_indices_summary += "}"
    values_summary += "}"
    # exit
    return f"rows = {rows_int}\ncolumns = {columns_int}\nnnz_ = {nnz_int}\n{view_line}colOffsets_ = {col_offsets_summary}\nrowIndices_ = {row_indices_summary}\nvalues_ = {values_summary}"
