import lldb
from matrix_lldb_formatter import _MAX_VIEW_DIM, format_matrix_display, format_matrix_summary
from utils import ScalarType, get_real_type, get_str_from_value, iterate_data_array, scalar_type_from_type


def dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    # get non-synthetic value to access actual DenseMatrix members
    valobj = valobj.GetNonSyntheticValue()
    # get matrix type and scalar type
    dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_matrix_type.GetTemplateArgumentType(0))
    # rows
    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
    rows_int: int = rows.GetValueAsUnsigned()
    if rows_int == 0:
        return "Empty Matrix (rows = 0)"
    # columns
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()
    if columns_int == 0:
        return "Empty Matrix (columns = 0)"
    # data
    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")
    # null data pointer indicates moved-from state
    if data.GetValueAsSigned() == 0:
        return "Moved-from Matrix (data_ = nullptr)"
    # don't attempt to build view for very large matrices to avoid expensive data retrieval and string construction in the formatter
    if rows_int > _MAX_VIEW_DIM or columns_int > _MAX_VIEW_DIM:
        return f"DenseMatrix<{rows_int}x{columns_int}>"

    def get_element(r: int, c: int) -> str:
        # value at [r, c]
        cur_element: lldb.SBValue = iterate_data_array(data, c * rows_int + r)
        # format value
        return get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"

    # call generic matrix summary formatter to build single-line summary string
    return format_matrix_summary(rows_int, columns_int, get_element)


class DenseMatrixSyntheticChildrenProvider:

    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj
        self._refresh()

    def _refresh(self):
        # rows
        self.rows: lldb.SBValue = self.valobj.GetChildMemberWithName("rows")
        self.rows_int: int = self.rows.GetValueAsUnsigned()
        # columns
        self.columns: lldb.SBValue = self.valobj.GetChildMemberWithName("columns")
        self.columns_int: int = self.columns.GetValueAsUnsigned()
        # data
        self.data: lldb.SBValue = self.valobj.GetChildMemberWithName("data_")
        # element type and view array type
        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.columns_int * self.rows_int)

    def update(self):
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        # map child name to index for rows, columns, view, and data_ children
        if name == "rows":
            return 0
        if name == "columns":
            return 1
        if name == "view":
            return 2
        if name == "data_":
            return 3
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int):
        # map index to child for rows, columns, view, and data_ children
        if index == 0:
            return self.rows
        if index == 1:
            return self.columns
        if index == 2:
            if self.rows_int > _MAX_VIEW_DIM or self.columns_int > _MAX_VIEW_DIM:
                return None
            # reorder from column-major storage into row-major for readable display
            view_data: lldb.SBData = lldb.SBData()
            # loop over rows
            for r in range(self.rows_int):
                # loop over columns in inner loop
                for c in range(self.columns_int):
                    # get the current element in column-major order and append to view data
                    element: lldb.SBValue = iterate_data_array(self.data, c * self.rows_int + r)
                    # append element to view
                    view_data.Append(element.GetData())
            # create synthetic "view" child with row-major view data and appropriate array type
            return self.valobj.CreateValueFromData("view", view_data, self.view_array_type)
        # data_ child is just the original data pointer with the original column-major layout
        if index == 3:
            return self.valobj.CreateValueFromAddress("data_", self.data.GetValueAsUnsigned(), self.view_array_type)
        # exit
        return None


def to_string(valobj: lldb.SBValue) -> str:
    # get non-synthetic value to access actual DenseMatrix members
    dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_matrix_type.GetTemplateArgumentType(0))
    # rows
    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")
    rows_int: int = rows.GetValueAsUnsigned()
    # columns
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")
    columns_int: int = columns.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")
    # check dimensions
    if rows_int <= _MAX_VIEW_DIM and columns_int <= _MAX_VIEW_DIM:

        def get_element(r: int, c: int) -> str:
            # value at [r, c]
            cur_element: lldb.SBValue = iterate_data_array(data, c * rows_int + r)
            # format value
            return get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"
        
        # call generic matrix display formatter to build multi-line view string
        view_line = "view =\n" + format_matrix_display(rows_int, columns_int, get_element) + "\n"
    else:
        view_line = ""
    # build raw column-major data array
    total = columns_int * rows_int
    # initialize data summary
    data_summary: str = "{"
    # loop over columns in outer loop and rows in inner loop to match column-major storage order
    for i in range(total):
        # get the current element in column-major order
        cur_element: lldb.SBValue = iterate_data_array(data, i)
        element_str = get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"
        # add element string to summary
        data_summary += element_str if i == total - 1 else f"{element_str}, "
    # add closing brace for entire data array
    data_summary += "}"
    # exit
    return f"rows = {rows_int}\ncolumns = {columns_int}\n{view_line}data_ = {data_summary}"
