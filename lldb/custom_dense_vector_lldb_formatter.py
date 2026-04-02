import lldb
from utils import ScalarType, get_real_type, get_str_from_value, iterate_data_array, scalar_type_from_type


def custom_dense_vector_summary(valobj: lldb.SBValue, internal_dict):
    # get non-synthetic value to access actual CustomDenseVector members
    valobj = valobj.GetNonSyntheticValue()
    # get vector type and scalar type
    custom_dense_vector_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()
    if n_int == 0:
        return "Empty Vector (n = 0)"
    if n_int > 7:
        return f"Big vector (n > 7)"
    # stride
    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")
    # null data pointer indicates moved-from state
    if data.GetValueAsSigned() == 0:
        return "Moved-from Vector (data_ = nullptr)"
    # build compact summary string
    summary: str = "{"
    for i in range(n_int):
        cur_element: lldb.SBValue = iterate_data_array(data, i * stride_int)
        element_str = get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"
        # add element string to summary
        summary += element_str if i == n_int - 1 else f"{element_str}, "
    summary += "}"
    # exit
    return summary


class CustomDenseVectorSyntheticChildrenProvider:

    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj
        self._refresh()

    def _refresh(self):
        # n
        self.n: lldb.SBValue = self.valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()
        # stride
        self.stride: lldb.SBValue = self.valobj.GetChildMemberWithName("stride_")
        self.stride_int: int = self.stride.GetValueAsUnsigned()
        # data
        self.data: lldb.SBValue = self.valobj.GetChildMemberWithName("data_")
        # element type and array types
        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.view_array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int)
        self.data_array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int * self.stride_int)

    def update(self):
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        # map child name to index for n, stride_, view, and data_ children
        if name == "n":
            return 0
        if name == "stride_":
            return 1
        if name == "view":
            return 2
        if name == "data_":
            return 3
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int):
        # map index to child for n, stride_, view, and data_ children
        if index == 0:
            return self.n
        if index == 1:
            return self.stride
        if index == 2:
            # reorder stride-spaced elements into a contiguous view array for readable display
            view_data: lldb.SBData = lldb.SBData()
            for i in range(self.n_int):
                # get element at stride-spaced position
                cur_element: lldb.SBValue = iterate_data_array(self.data, i * self.stride_int)
                # append element to view
                view_data.Append(cur_element.GetData())
            return self.valobj.CreateValueFromData("view", view_data, self.view_array_type)
        # data_ child is the original data pointer with the full strided physical layout
        if index == 3:
            return self.valobj.CreateValueFromAddress("data_", self.data.GetValueAsUnsigned(), self.data_array_type)
        # exit
        return None

def to_string(valobj: lldb.SBValue) -> str:
    # get vector type and scalar type
    custom_dense_vector_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()
    # stride
    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
    stride_int: int = stride.GetValueAsUnsigned()
    # data
    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")
    data_int: int = data.GetValueAsUnsigned()
    # guard: empty or null vector
    if n_int == 0 and data_int == 0:
        return f"n = 0\nstride_ = {stride_int}\nview = {{nullptr}}\ndata_ = {{nullptr}}"
    if data_int == 0:
        return f"n = {n_int}\nstride_ = {stride_int}\nview = nullptr\ndata_ = nullptr"
    # build view summary (stride-spaced elements)
    view_summary: str = "{"
    for i in range(n_int):
        cur_element: lldb.SBValue = iterate_data_array(data, i * stride_int)
        element_str = get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"
        # add element string to view summary
        view_summary += element_str if i == n_int - 1 else f"{element_str}, "
    view_summary += "}"
    # build raw data summary (physical storage, first n elements)
    data_summary: str = "{"
    for i in range(n_int):
        cur_element: lldb.SBValue = iterate_data_array(data, i)
        element_str = get_str_from_value(cur_element, scalar_type) if cur_element.IsValid() else "N/A"
        # add element string to data summary
        data_summary += element_str if i == n_int - 1 else f"{element_str}, "
    data_summary += "}"
    # exit
    return f"n = {n_int}\nstride_ = {stride_int}\nview = {view_summary}\ndata_ = {data_summary}"
