import textwrap

from utils import *
import dense_vector_lldb_formatter
import lldb

def dense_vector_view_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    dense_vector_view_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_vector_view_type.GetTemplateArgumentType(0))
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()

    if n_int == 0:
        return "Empty Vector (n = 0)"

    if n_int > 7:
        return f"Big vector (n > 7)"

    offset: lldb.SBValue = valobj.GetChildMemberWithName("offset_")
    offset_int = offset.GetValueAsUnsigned()

    owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")
    data: lldb.SBValue = owner.GetChildMemberWithName("data_")

    if data.GetValueAsSigned() == 0:
        return "View on null Vector (owner.data_ = nullptr)"

    summary: str = "{"

    for i in range(0, n_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i + offset_int)

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

class DenseVectorViewSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.n: lldb.SBValue = valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()

        self.offset: lldb.SBValue = valobj.GetChildMemberWithName("offset_")
        self.offset_int: int = self.offset.GetValueAsUnsigned()

        self.owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

        self.data: lldb.SBValue = self.owner.GetChildMemberWithName("data_")

        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int)

    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "offset_":
            return 1

        if name == "view":
            return 2

        if name == "owner_":
            return 3

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            return self.offset

        if index == 2:
            return self.data.CreateValueFromAddress(
                "view",
                self.data.GetValueAsUnsigned() + (self.offset_int * self.element_type.GetByteSize()),
                self.array_type
            )

        if index == 3:
            return self.owner

        return None

def to_string(valobj: lldb.SBValue) -> str:
    dense_vector_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_vector_type.GetTemplateArgumentType(0))
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    offset: lldb.SBValue = valobj.GetChildMemberWithName("offset_")
    owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")
    data: lldb.SBValue = owner.GetChildMemberWithName("data_")

    n_int: int = n.GetValueAsUnsigned()
    offset_int: int = offset.GetValueAsUnsigned()
    owner_str: str = dense_vector_lldb_formatter.to_string(owner)
    owner_str = textwrap.indent(owner_str, "    ")

    if n_int == 0:
        return f"n = 0\noffset_ = {offset_int}\nview = {{}}\nowner_ = {{\n{owner_str}\n}}"

    summary: str = "{"

    for i in range(0, n_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i + offset_int)

        if cur_element_data.IsValid():
            cur_element = get_str_from_value(cur_element_data, scalar_type)
        else:
            cur_element = "N/A"


        if i != n_int - 1:
            summary += f"{cur_element}, "
        else:
            summary += cur_element

    summary += "}"

    return f"n = {n_int}\noffset_ = {offset_int}\nview = {summary}\nowner_ = {{\n{owner_str}\n}}"
