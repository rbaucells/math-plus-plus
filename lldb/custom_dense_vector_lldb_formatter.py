import lldb
from utils import ScalarType, get_real_type, get_str_from_value, iterate_data_array, scalar_type_from_type

# maximum size for which a full vector view is rendered
_MAX_VIEW_DIM: int = 7


def custom_dense_vector_summary(vector: lldb.SBValue, internal_dict: dict[str, object]) -> str:
    # get non-synthetic value to access actual CustomDenseVector members
    vector = vector.GetNonSyntheticValue()
    # get vector type and scalar type
    custom_dense_vector_type: lldb.SBType = get_real_type(vector.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = vector.GetChildMemberWithName("n_")
    n_int: int = n.GetValueAsUnsigned()
    if n_int == 0:
        return "Empty Vector (n = 0)"
    # stride
    stride: lldb.SBValue = vector.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = vector.GetChildMemberWithName("data_")
    # null data pointer indicates moved-from state
    if data.GetValueAsSigned() == 0:
        return "Moved-from Vector (data_ = nullptr)"
    # don't attempt to build view for very large vectors to avoid expensive data retrieval and string construction in the formatter
    if n_int > _MAX_VIEW_DIM:
        return f"CustomDenseVector<{n_int}>"

    def get_element(i: int) -> str:
        # value at [i]
        cur_element: lldb.SBValue = iterate_data_array(data, i * stride_int)
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


class CustomDenseVectorSyntheticChildrenProvider:

    def __init__(self, vector: lldb.SBValue, internal_dict: dict[str, object]) -> None:
        self.vector: lldb.SBValue = vector
        self._refresh()

    def _refresh(self) -> None:
        # n
        self.n: lldb.SBValue = self.vector.GetChildMemberWithName("n_")
        self.n_int: int = self.n.GetValueAsUnsigned()
        # stride
        self.stride: lldb.SBValue = self.vector.GetChildMemberWithName("stride_")
        self.stride_int: int = self.stride.GetValueAsUnsigned()
        # data
        self.data: lldb.SBValue = self.vector.GetChildMemberWithName("data_")
        # element type and array types
        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int)
        self.data_array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int * self.stride_int)

    def update(self) -> None:
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        # map child name to index for n, stride_, view, and data_ children
        if name == "n_":
            return 0
        if name == "stride_":
            return 1
        if name == "view":
            return 2
        if name == "data_":
            return 3
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int) -> lldb.SBValue | None:
        # map index to child for n, stride_, view, and data_ children
        if index == 0:
            return self.n
        if index == 1:
            return self.stride
        if index == 2:
            # do not display large vectors
            if self.n_int > _MAX_VIEW_DIM:
                return None
            # reorder stride-spaced elements into a contiguous view array for readable display
            view_data: lldb.SBData = lldb.SBData()
            for i in range(self.n_int):
                # get element at stride-spaced position
                cur_element: lldb.SBValue = iterate_data_array(self.data, i * self.stride_int)
                # append element to view
                view_data.Append(cur_element.GetData())
            return self.vector.CreateValueFromData("view", view_data, self.view_array_type)
        # data_ child is the original data pointer with the full strided physical layout
        if index == 3:
            return self.vector.CreateValueFromAddress("data_", self.data.GetValueAsUnsigned(), self.data_array_type)
        # exit
        return None


def to_string(vector: lldb.SBValue) -> str:
    # get vector type and scalar type
    custom_dense_vector_type: lldb.SBType = get_real_type(vector.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = vector.GetChildMemberWithName("n_")
    n_int: int = n.GetValueAsUnsigned()
    # stride
    stride: lldb.SBValue = vector.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = vector.GetChildMemberWithName("data_")
    # check dimensions
    if n_int <= _MAX_VIEW_DIM:

        def get_element(i: int) -> str:
            # value at [i]
            cur_element: lldb.SBValue = iterate_data_array(data, i * stride_int)
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
    total: int = stride_int * (n_int - 1) + 1 if n_int > 0 else 0
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
    return f"n = {n_int}\nstride_ = {stride_int}\n{view_line}data_ = {data_summary}"
