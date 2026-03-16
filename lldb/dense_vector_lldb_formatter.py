import lldb
from enum import Enum

from utils import *

def dense_vector_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    dense_vector_type: lldb.SBType = valobj.GetType()

    if not dense_vector_type.IsValid():
        raise RuntimeError("dense_vector_type is invalid")

    dense_vector_type = get_real_type(dense_vector_type)

    t_type = dense_vector_type.GetTemplateArgumentType(0)

    if not t_type.IsValid():
        raise RuntimeError("t_type is invalid")

    scalar_type = scalar_type_from_type(t_type)

    n: lldb.SBValue = valobj.GetChildMemberWithName("n")

    if not n.IsValid():
        raise RuntimeError("n is invalid")

    n_int = n.GetValueAsUnsigned()

    if n_int == 0:
        raise RuntimeError("empty dense vector")

    if n_int > 7:
        return ""

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if not data.IsValid():
        raise RuntimeError("data member is not valid")

    if data.GetValueAsSigned() == 0:
        raise RuntimeError("data member is nullptr")

    summary: str = "{"

    for i in range(0, n_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i)

        if not cur_element_data.IsValid():
            raise RuntimeError(f"cur_element at index = {i}) is not valid")

        cur_element = get_str_from_value(cur_element_data, scalar_type)

        if i != n_int - 1:
            summary += f"{cur_element}, "
        else:
            summary += cur_element

    summary += "}"

    return summary

class DenseVectorSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.n = valobj.GetChildMemberWithName("n")

        if not self.n.IsValid():
            raise RuntimeError("n is invalid")

        self.n_int = self.n.GetValueAsUnsigned()

        self.valobj = valobj

        data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        if not data.IsValid():
            raise RuntimeError("data member is not valid")

        self.data = data

        self.element_type = self.data.GetType().GetPointeeType()
        self.array_type = self.element_type.GetArrayType(self.n_int)

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
    target: lldb.SBTarget = debugger.GetSelectedTarget()

    if not target.IsValid():
        result.PutError("target was invalid")
        return "target was invalid"

    frame: lldb.SBFrame = target.GetProcess().GetSelectedThread().GetSelectedFrame()

    if not frame.IsValid():
        result.PutError("frame was invalid")
        return "frame was invalid"

    valobj: lldb.SBValue = frame.FindVariable(command)

    if not valobj.IsValid():
        result.PutError("valobj was invalid")
        return "valobj was invalid"

    valobj = valobj.GetNonSyntheticValue()

    summary = dense_vector_summary(valobj, internal_dict)

    if vector_to_string_orientation == "vertical":
        summary = summary.replace("{", "{\n ")
        summary = summary.replace("}", "\n}")
        summary = summary.replace(",", "\n")

    result.PutCString(summary)