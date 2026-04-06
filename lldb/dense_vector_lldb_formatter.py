import lldb
from utils import ScalarType, get_real_type, get_str_from_value, iterate_data_array, scalar_type_from_type

# maximum size for which a full vector view is rendered
_MAX_VIEW_DIM: int = 7


def dense_vector_summary(vector: lldb.SBValue, internal_dict: dict[str, object]) -> str:
    # get non-synthetic value to access actual DenseVector members
    vector = vector.GetNonSyntheticValue()
    # get vector type and scalar type
    vector_type: lldb.SBType = get_real_type(vector.GetType())
    scalar_type: ScalarType = scalar_type_from_type(vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = vector.GetChildMemberWithName("n_")
    n_int: int = n.GetValueAsUnsigned()
    if n_int == 0:
        return "Empty Vector (n = 0)"
    # data
    data: lldb.SBValue = vector.GetChildMemberWithName("data_")
    # null data pointer indicates moved-from state
    if data.GetValueAsSigned() == 0:
        return "Moved-from Vector (data_ = nullptr)"
    # don't attempt to build view for very large vectors to avoid expensive data retrieval and string construction in the formatter
    if n_int > _MAX_VIEW_DIM:
        return f"DenseVector<{n_int}>"

    def get_element(i: int) -> str:
        # value at [i]
        cur_element: lldb.SBValue = iterate_data_array(data, i)
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


class DenseVectorSyntheticChildrenProvider:

    def __init__(self, vector: lldb.SBValue, internal_dict: dict[str, object]) -> None:
        self.vector: lldb.SBValue = vector
        self._refresh()

    def _refresh(self) -> None:
        # n
        self.n: lldb.SBValue = self.vector.GetChildMemberWithName("n_")
        self.n_int: int = self.n.GetValueAsUnsigned()
        # data
        self.data: lldb.SBValue = self.vector.GetChildMemberWithName("data_")
        # element type and view array type
        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int)

    def update(self) -> None:
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 3

    def get_child_index(self, name: str) -> int:
        # map child name to index for n, view, and data_ children
        if name == "n_":
            return 0
        if name == "view":
            return 1
        if name == "data_":
            return 2
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int) -> lldb.SBValue | None:
        # map index to child for n, view, and data_ children
        if index == 0:
            return self.n
        if index == 1:
            # do not display large vectors
            if self.n_int > _MAX_VIEW_DIM:
                return None
            # create synthetic "view" child with contiguous view data and appropriate array type
            return self.vector.CreateValueFromAddress("view", self.data.GetValueAsUnsigned(), self.view_array_type)
        # data_ child is just the original data pointer with the original contiguous layout
        if index == 2:
            return self.vector.CreateValueFromAddress("data_", self.data.GetValueAsUnsigned(), self.view_array_type)
        # exit
        return None


def to_string(vector: lldb.SBValue) -> str:
    # get vector type and scalar type
    vector_type: lldb.SBType = get_real_type(vector.GetType())
    scalar_type: ScalarType = scalar_type_from_type(vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = vector.GetChildMemberWithName("n_")
    n_int: int = n.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = vector.GetChildMemberWithName("data_")
    # check dimensions
    if n_int <= _MAX_VIEW_DIM:

        def get_element(i: int) -> str:
            # value at [i]
            cur_element: lldb.SBValue = iterate_data_array(data, i)
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
    # build raw data array
    total: int = n_int
    # initialize data summary
    data_summary: str = "{"
    # loop over vector elements in storage order
    for i in range(total):
        # get the current element in contiguous order
        cur_element: lldb.SBValue = iterate_data_array(data, i)
        element_str: str = get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"
        # add element string to summary
        data_summary += element_str if i == total - 1 else f"{element_str}, "
    # add closing brace for entire data array
    data_summary += "}"
    # exit
    return f"n = {n_int}\n{view_line}data_ = {data_summary}"