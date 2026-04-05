import lldb
from dense_matrix_lldb_formatter import to_string as dense_matrix_to_string
from matrix_lldb_formatter import _MAX_VIEW_DIM, format_matrix_display, format_matrix_summary
from utils import ScalarType, get_real_type, get_str_from_value, indent_lines, iterate_data_array, scalar_type_from_type


def dense_matrix_view_summary(view: lldb.SBValue, internal_dict):
    # get non-synthetic value to access actual DenseMatrix members
    view = view.GetNonSyntheticValue()
    # get matrix type and scalar type
    matrix_type: lldb.SBType = get_real_type(view.GetType())
    scalar_type: ScalarType = scalar_type_from_type(matrix_type.GetTemplateArgumentType(0))
    # rows
    rows: lldb.SBValue = view.GetChildMemberWithName("rows_")
    rows_int: int = rows.GetValueAsUnsigned()
    if rows_int == 0:
        return "Empty Matrix (rows = 0)"
    # columns
    columns: lldb.SBValue = view.GetChildMemberWithName("columns_")
    columns_int: int = columns.GetValueAsUnsigned()
    if columns_int == 0:
        return "Empty Matrix (columns = 0)"
    # colOffset
    col_offset: lldb.SBValue = view.GetChildMemberWithName("colOffset_")
    col_offset_int: int = col_offset.GetValueAsUnsigned()
    # rowOffset
    row_offset: lldb.SBValue = view.GetChildMemberWithName("rowOffset_")
    row_offset_int: int = row_offset.GetValueAsUnsigned()
    # owner
    owner: lldb.SBValue = view.GetChildMemberWithName("owner_")
    # data
    data: lldb.SBValue = owner.GetChildMemberWithName("data_")
    # array element type
    element_type = data.GetType().GetPointeeType()
    # element size in bytes
    element_size = element_type.GetByteSize()
    # owner matrix rows
    owner_rows = owner.GetChildMemberWithName("rows_")
    owner_rows_int = owner_rows.GetValueAsUnsigned()

    def get_element(r: int, c: int) -> str:
        # index in column-major order
        index = (c + col_offset_int) * owner_rows_int + (r + row_offset_int)
        # element at [r, c]
        element = data.CreateChildAtOffset(f"[{index}]", index * element_size, element_type)
        # format value
        return get_str_from_value(element, scalar_type) if element.IsValid() else "N/A"

    # call generic matrix summary formatter to build single-line summary string
    return format_matrix_summary(rows_int, columns_int, get_element)


class DenseMatrixViewSyntheticChildrenProvider:

    def __init__(self, view: lldb.SBValue, internal_dict):
        self.view = view
        self._refresh()

    def _refresh(self):
        # rows
        self.rows: lldb.SBValue = self.view.GetChildMemberWithName("rows_")
        self.rows_int: int = self.rows.GetValueAsUnsigned()
        # columns
        self.columns: lldb.SBValue = self.view.GetChildMemberWithName("columns_")
        self.columns_int: int = self.columns.GetValueAsUnsigned()
        # colOffset
        self.col_offset: lldb.SBValue = self.view.GetChildMemberWithName("colOffset_")
        self.col_offset_int: int = self.col_offset.GetValueAsUnsigned()
        # rowOffset
        self.row_offset: lldb.SBValue = self.view.GetChildMemberWithName("rowOffset_")
        self.row_offset_int: int = self.row_offset.GetValueAsUnsigned()
        # owner
        self.owner: lldb.SBValue = self.view.GetChildMemberWithName("owner_")
        # data
        self.owner_data: lldb.SBValue = self.owner.GetChildMemberWithName("data_")
        # element type and view array type
        self.element_type: lldb.SBType = self.owner_data.GetType().GetPointeeType()
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.columns_int * self.rows_int)
        # element size in bytes
        self.element_size: int = self.element_type.GetByteSize()

    def update(self):
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 6

    def get_child_index(self, name: str) -> int:
        # map child name to index for rows, columns, view, and data_ children
        if name == "rows_":
            return 0
        if name == "columns_":
            return 1
        if name == "rowOffset_":
            return 2
        if name == "colOffset_":
            return 3
        if name == "view":
            return 4
        if name == "owner_":
            return 5
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int):
        # map index to child for rows, columns, view, and data_ children
        if index == 0:
            return self.rows
        if index == 1:
            return self.columns
        if index == 2:
            return self.row_offset
        if index == 3:
            return self.col_offset
        if index == 4:
            # do not create view if dimensions are too large
            if self.rows_int > _MAX_VIEW_DIM or self.columns_int > _MAX_VIEW_DIM:
                return None
            # owner matrix rows
            owner_rows = self.owner.GetChildMemberWithName("rows_")
            owner_rows_int = owner_rows.GetValueAsUnsigned()
            # reorder from column-major storage into row-major for readable display
            view_data: lldb.SBData = lldb.SBData()
            # loop over rows
            for r in range(self.rows_int):
                # loop over columns in inner loop
                for c in range(self.columns_int):
                    # index in column-major order
                    index = (c + self.col_offset_int) * owner_rows_int + (r + self.row_offset_int)
                    # element at [r, c]
                    element = self.owner_data.CreateChildAtOffset(f"[{index}]", index * self.element_size, self.element_type)
                    # append element to view
                    view_data.Append(element.GetData())
            # create synthetic "view" child with row-major view data and appropriate array type
            return self.view.CreateValueFromData("view", view_data, self.view_array_type)
        if index == 5:
            return self.owner
        # exit
        return None


def to_string(view: lldb.SBValue) -> str:
    # get non-synthetic value to access actual DenseMatrix members
    matrix_type: lldb.SBType = get_real_type(view.GetType())
    scalar_type: ScalarType = scalar_type_from_type(matrix_type.GetTemplateArgumentType(0))
    # rows
    rows: lldb.SBValue = view.GetChildMemberWithName("rows_")
    rows_int: int = rows.GetValueAsUnsigned()
    # columns
    columns: lldb.SBValue = view.GetChildMemberWithName("columns_")
    columns_int: int = columns.GetValueAsUnsigned()
    # colOffset
    col_offset: lldb.SBValue = view.GetChildMemberWithName("colOffset_")
    col_offset_int: int = col_offset.GetValueAsUnsigned()
    # rowOffset
    row_offset: lldb.SBValue = view.GetChildMemberWithName("rowOffset_")
    row_offset_int: int = row_offset.GetValueAsUnsigned()
    # owner
    owner: lldb.SBValue = view.GetChildMemberWithName("owner_")
    # data
    data: lldb.SBValue = owner.GetChildMemberWithName("data_")
    # check dimensions
    if rows_int <= _MAX_VIEW_DIM and columns_int <= _MAX_VIEW_DIM:
        # array element type
        element_type = data.GetType().GetPointeeType()
        # element size in bytes
        element_size = element_type.GetByteSize()
        # owner matrix rows
        owner_rows = owner.GetChildMemberWithName("rows_")
        owner_rows_int = owner_rows.GetValueAsUnsigned()

        def get_element(r: int, c: int) -> str:
            # index in column-major order
            index = (c + col_offset_int) * owner_rows_int + (r + row_offset_int)
            # element at [r, c]
            element = data.CreateChildAtOffset(f"[{index}]", index * element_size, element_type)
            # format value
            return get_str_from_value(element, scalar_type) if element.IsValid() else "N/A"
        
        # call generic matrix display formatter to build multi-line view string
        view_line = "view =\n" + format_matrix_display(rows_int, columns_int, get_element) + "\n"
    else:
        view_line = ""
    # formatted string
    return f"rows = {rows_int}\ncolumns = {columns_int}\nrowOffset = {row_offset_int}\ncolOffset = {col_offset_int}\n{view_line}owner = \n{indent_lines(dense_matrix_to_string(owner), 3)}"
