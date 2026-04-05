import lldb
from matrix_lldb_formatter import _MAX_VIEW_DIM, format_matrix_display, format_matrix_summary
from utils import ScalarType, get_real_type, get_str_from_value, iterate_data_array, scalar_type_from_type


def custom_dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    # get non-synthetic value to access actual CustomDenseMatrix members
    valobj = valobj.GetNonSyntheticValue()
    # get matrix type and scalar type
    custom_dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_matrix_type.GetTemplateArgumentType(0))
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
    # stride
    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")
    # null data pointer indicates moved-from state
    if data.GetValueAsSigned() == 0:
        return "Moved-from Matrix (data_ = nullptr)"
    # don't attempt to build view for very large matrices to avoid expensive data retrieval and string construction in the formatter
    if rows_int > _MAX_VIEW_DIM or columns_int > _MAX_VIEW_DIM:
        return f"CustomDenseMatrix<{rows_int}x{columns_int}>"

    def get_element(r: int, c: int) -> str:
        # value at [r, c] using column-major storage with stride
        cur_element: lldb.SBValue = iterate_data_array(data, c * stride_int + r)
        # format value
        return get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"

    # call generic matrix summary formatter to build single-line summary string
    return format_matrix_summary(rows_int, columns_int, get_element)

class CustomDenseMatrixSyntheticChildrenProvider:

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
        # stride
        self.stride: lldb.SBValue = self.valobj.GetChildMemberWithName("stride_")
        self.stride_int: int = self.stride.GetValueAsUnsigned()
        # data
        self.data: lldb.SBValue = self.valobj.GetChildMemberWithName("data_")
        # element type and view array types
        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.data_array_type: lldb.SBType = self.element_type.GetArrayType(self.stride_int * (self.columns_int - 1) + self.rows_int)
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.columns_int * self.rows_int)

    def update(self):
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 5

    def get_child_index(self, name: str) -> int:
        # map child name to index for rows, columns, stride_, view, and data_ children
        if name == "rows_":
            return 0
        if name == "columns_":
            return 1
        if name == "stride_":
            return 2
        if name == "view":
            return 3
        if name == "data_":
            return 4
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int):
        # map index to child for rows, columns, stride_, view, and data_ children
        if index == 0:
            return self.rows
        if index == 1:
            return self.columns
        if index == 2:
            return self.stride
        if index == 3:
            if self.rows_int > _MAX_VIEW_DIM or self.columns_int > _MAX_VIEW_DIM:
                return None
            # reorder from column-major storage (with stride) into row-major for readable display
            view_data: lldb.SBData = lldb.SBData()
            # loop over rows
            for r in range(self.rows_int):
                # loop over columns in inner loop
                for c in range(self.columns_int):
                    # get the current element using stride-based column-major indexing and append to view data
                    element: lldb.SBValue = iterate_data_array(self.data, c * self.stride_int + r)
                    # append element to view
                    view_data.Append(element.GetData())
            # create synthetic "view" child with row-major view data and appropriate array type
            return self.valobj.CreateValueFromData("view", view_data, self.view_array_type)
        # data_ child is the original data pointer with the column-major strided layout
        if index == 4:
            return self.valobj.CreateValueFromAddress("data_", self.data.GetValueAsUnsigned(), self.data_array_type)
        # exit
        return None

def to_string(valobj: lldb.SBValue) -> str:
    # get matrix type and scalar type
    custom_dense_matrix_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_matrix_type.GetTemplateArgumentType(0))
    # rows
    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows_")
    rows_int: int = rows.GetValueAsUnsigned()
    # columns
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns_")
    columns_int: int = columns.GetValueAsUnsigned()
    # stride
    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")
    # check dimensions
    if rows_int <= _MAX_VIEW_DIM and columns_int <= _MAX_VIEW_DIM:

        def get_element(r: int, c: int) -> str:
            # value at [r, c] using column-major storage with stride
            cur_element: lldb.SBValue = iterate_data_array(data, c * stride_int + r)
            # format value
            return get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"

        # call generic matrix display formatter to build multi-line view string
        view_line = "view =\n" + format_matrix_display(rows_int, columns_int, get_element) + "\n"
    else:
        view_line = ""
    # build raw column-major data array (physical size accounts for stride padding)
    total: int = stride_int * (columns_int - 1) + rows_int
    # initialize data summary
    data_summary: str = "{"
    # loop over the physical data array in storage order
    for i in range(total):
        # get the current element in physical storage order
        cur_element: lldb.SBValue = iterate_data_array(data, i)
        element_str = get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"
        # add element string to summary
        data_summary += element_str if i == total - 1 else f"{element_str}, "
    # add closing brace for entire data array
    data_summary += "}"
    # exit
    return f"rows = {rows_int}\ncolumns = {columns_int}\nstride_ = {stride_int}\n{view_line}data_ = {data_summary}"
