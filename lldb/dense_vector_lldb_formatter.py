from utils import *
import lldb

def dense_vector_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    dense_vector_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(dense_vector_type.GetTemplateArgumentType(0))
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()

    if n_int == 0:
        return "Empty Vector (n = 0)"

    if n_int > 7:
        return f"Big vector (n > 7)"

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if data.GetValueAsSigned() == 0:
        return "Null Vector (data_ = nullptr)"

    summary: str = "{"

    for i in range(0, n_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i)

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

class DenseVectorSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.n: lldb.SBValue = valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()

        self.data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        self.element_type: lldb.SBType = self.data.GetType().GetPointeeType()
        self.array_type: lldb.SBType = self.element_type.GetArrayType(self.n_int)

    def num_children(self, max_children: int) -> int:
        return 2

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "data_":
            return 1

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            return self.data.CreateValueFromAddress(
                "data_",
                self.data.GetValueAsUnsigned(),
                self.array_type
            )

        return None

def to_string_dv(debugger: lldb.SBDebugger, command: str, result: lldb.SBCommandReturnObject, internal_dict):
    frame: lldb.SBFrame = debugger.GetSelectedTarget().GetProcess().GetSelectedThread().GetSelectedFrame()
    valobj: lldb.SBValue = frame.FindVariable(command).GetNonSyntheticValue()

    summary = dense_vector_summary(valobj, internal_dict)
    if vector_to_string_orientation == "vertical":
        summary = summary.replace("{", "{\n ")
        summary = summary.replace("}", "\n}")
        summary = summary.replace(",", "\n")

    result.PutCString(summary)