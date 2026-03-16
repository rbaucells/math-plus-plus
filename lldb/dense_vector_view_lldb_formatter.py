from utils import *
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
        return f"Vector too big for summary (n = {n}"

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
        self.valobj = valobj

        self.n = valobj.GetChildMemberWithName("n")
        self.n_int = self.n.GetValueAsUnsigned()

        self.offset = valobj.GetChildMemberWithName("offset_")
        self.offset_int = self.offset.GetValueAsUnsigned()

        self.owner = valobj.GetChildMemberWithName("owner_")

        self.data = self.owner.GetChildMemberWithName("data_")

        self.element_type = self.data.GetType().GetPointeeType()
        self.array_type = self.element_type.GetArrayType(self.n_int)

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

def to_string_dvv(debugger: lldb.SBDebugger, command: str, result: lldb.SBCommandReturnObject, internal_dict):
    frame: lldb.SBFrame = debugger.GetSelectedTarget().GetProcess().GetSelectedThread().GetSelectedFrame()
    valobj: lldb.SBValue = frame.FindVariable(command).GetNonSyntheticValue()

    summary = dense_vector_view_summary(valobj, internal_dict)
    if vector_to_string_orientation == "vertical":
        summary = summary.replace("{", "{\n ")
        summary = summary.replace("}", "\n}")
        summary = summary.replace(",", "\n")

    result.PutCString(summary)