import lldb
from dense_vector_lldb_formatter import _MAX_VIEW_DIM, to_string as dense_vector_to_string
from utils import ScalarType, get_real_type, get_str_from_value, indent_lines, iterate_data_array, scalar_type_from_type


def dense_vector_view_summary(view: lldb.SBValue, internal_dict: dict[str, object]) -> str:
    # get non-synthetic value to access actual DenseVectorView members
    view = view.GetNonSyntheticValue()

    # get vector type and scalar type
    dense_vector_view_type: lldb.SBType = get_real_type(view.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_vector_view_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = view.GetChildMemberWithName("n_")
    n_int: int = n.GetValueAsUnsigned()
    if n_int == 0:
        return "Empty Vector (n = 0)"
    # offset
    offset: lldb.SBValue = view.GetChildMemberWithName("offset_")
    offset_int: int = offset.GetValueAsUnsigned()
    # owner
    owner: lldb.SBValue = view.GetChildMemberWithName("owner_")
    # data
    data: lldb.SBValue = owner.GetChildMemberWithName("data_")

    def get_element(i: int) -> str:
        # value at [i]
        cur_element: lldb.SBValue = iterate_data_array(data, i + offset_int)
        # format value
        return get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"

    # build compact summary string
    summary: str = "{"
    # loop over vector elements in storage order
    for i in range(n_int):
        # element at i
        element_str: str = get_element(i)
        # add element string to summary
        summary += element_str if i == n_int - 1 else f"{element_str}, "
    # close summary with brace
    summary += "}"
    # exit
    return summary


class DenseVectorViewSyntheticChildrenProvider:

    def __init__(self, view: lldb.SBValue, internal_dict: dict[str, object]) -> None:
        self.view: lldb.SBValue = view
        self._refresh()

    def _refresh(self) -> None:
        # n
        self.n: lldb.SBValue = self.view.GetChildMemberWithName("n_")
        self.n_int: int = self.n.GetValueAsUnsigned()
        # offset
        self.offset: lldb.SBValue = self.view.GetChildMemberWithName("offset_")
        self.offset_int: int = self.offset.GetValueAsUnsigned()
        # owner
        self.owner: lldb.SBValue = self.view.GetChildMemberWithName("owner_")
        # data
        self.owner_data: lldb.SBValue = self.owner.GetChildMemberWithName("data_")
        # element type and view array type
        self.element_type: lldb.SBType = self.owner_data.GetType().GetPointeeType()
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int)
        # element size in bytes
        self.element_size: int = self.element_type.GetByteSize()

    def update(self) -> None:
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        # map child name to index for n, offset_, view, and owner_ children
        if name == "n_":
            return 0
        if name == "offset_":
            return 1
        if name == "view":
            return 2
        if name == "owner_":
            return 3
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int) -> lldb.SBValue | None:
        # map index to child for n, offset_, view, and owner_ children
        if index == 0:
            return self.n
        if index == 1:
            return self.offset
        if index == 2:
            # do not display large vectors
            if self.n_int > _MAX_VIEW_DIM:
                return None
            # create synthetic "view" child with contiguous view data and appropriate array type
            return self.view.CreateValueFromAddress("view", self.owner_data.GetValueAsUnsigned() + (self.offset_int * self.element_size), self.view_array_type)
        if index == 3:
            return self.owner
        # exit
        return None


def to_string(view: lldb.SBValue) -> str:
    # get non-synthetic value to access actual DenseVectorView members
    dense_vector_view_type: lldb.SBType = get_real_type(view.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_vector_view_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = view.GetChildMemberWithName("n_")
    n_int: int = n.GetValueAsUnsigned()
    # offset
    offset: lldb.SBValue = view.GetChildMemberWithName("offset_")
    offset_int: int = offset.GetValueAsUnsigned()
    # owner
    owner: lldb.SBValue = view.GetChildMemberWithName("owner_")
    # data
    data: lldb.SBValue = owner.GetChildMemberWithName("data_")
    # check dimensions
    if n_int <= _MAX_VIEW_DIM:

        def get_element(i: int) -> str:
            # value at [i]
            cur_element: lldb.SBValue = iterate_data_array(data, i + offset_int)
            # format value
            return get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"

        # build compact view string
        view_summary: str = "{"
        for i in range(n_int):
            element_str: str = get_element(i)
            # add element string to view summary
            view_summary += element_str if i == n_int - 1 else f"{element_str}, "
        view_summary += "}"
        view_line: str = f"view = {view_summary}\n"
    else:
        view_line = ""
    # formatted string
    owner_str: str = indent_lines(dense_vector_to_string(owner), 3)
    # exit
    return f"n = {n_int}\noffset = {offset_int}\n{view_line}owner = \n{owner_str}"
