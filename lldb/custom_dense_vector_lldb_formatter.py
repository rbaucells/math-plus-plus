from utils import *
import lldb

def custom_dense_vector_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    custom_dense_vector_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_dense_vector_type.GetTemplateArgumentType(0))
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()

    if n_int == 0:
        return "Empty Vector (n = 0)"

    if n_int > 7:
        return f"Big vector (n > 7)"

    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
    stride_int = stride.GetValueAsUnsigned()

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if data.GetValueAsSigned() == 0:
        return "Null Vector (data_ = nullptr)"

    summary: str = "{"

    for i in range(0, n_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i * stride_int)

        if cur_element_data.IsValid():
            cur_element = get_str_from_value(cur_element_data, scalar_type)
        else:
            cur_element = "N/A"


        if i != n_int - 1:
            summary += f"{cur_element}, "
        else:
            summary += cur_element

    summary += "}"

    return summary

class CustomDenseVectorSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.n: lldb.SBValue = valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()

        self.stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")
        self.stride_int: int = self.stride.GetValueAsUnsigned()

        self.data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()

        self.fake_array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int)
        self.array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int * self.stride_int)

    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "stride_":
            return 1

        if name == "view":
            return 2

        if name == "data_":
            return 3

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            return self.stride

        if index == 2:
            data: lldb.SBData = lldb.SBData()

            for i in range(0, self.n_int):
                cur_element = lldb.SBValue = iterate_data_array(self.data, i * self.stride_int)
                data.Append(cur_element.GetData())

            return self.data.CreateValueFromData(
                "view",
                data,
                self.fake_array_type
            )

        if index == 3:
            return self.data.CreateValueFromAddress(
                "data_",
                self.data.GetValueAsUnsigned(),
                self.array_type
            )

        return None

def to_string(valobj: lldb.SBValue) -> str:
    ...