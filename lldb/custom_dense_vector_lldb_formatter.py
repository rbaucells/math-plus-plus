import lldb
from enum import Enum

from utils import *

def custom_dense_vector_summary(valobj: lldb.SBValue, internal_dict):
    valobj = valobj.GetNonSyntheticValue()

    custom_dense_vector_type: lldb.SBType = valobj.GetType()

    if not custom_dense_vector_type.IsValid():
        raise RuntimeError("custom_dense_vector_type is invalid")

    custom_dense_vector_type = get_real_type(custom_dense_vector_type)

    t_type = custom_dense_vector_type.GetTemplateArgumentType(0)

    if not t_type.IsValid():
        raise RuntimeError("t_type is invalid")

    scalar_type = scalar_type_from_type(t_type)

    n: lldb.SBValue = valobj.GetChildMemberWithName("n")

    if not n.IsValid():
        raise RuntimeError("n is invalid")

    n_int = n.GetValueAsUnsigned()

    if n_int == 0:
        raise RuntimeError("empty custom dense vector")

    if n_int > 7:
        return ""

    stride: lldb.SBValue = valobj.GetChildMemberWithName("stride_")

    if not stride.IsValid():
        raise RuntimeError("stride is invalid")

    stride_int = stride.GetValueAsUnsigned()

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if not data.IsValid():
        raise RuntimeError("data member is not valid")

    if data.GetValueAsSigned() == 0:
        raise RuntimeError("data member is nullptr")

    summary: str = "{"

    for i in range(0, n_int):
        cur_element_data: lldb.SBValue = iterate_data_array(data, i * stride_int)

        if not cur_element_data.IsValid():
            raise RuntimeError(f"cur_element at index = {i}) is not valid")

        cur_element = get_str_from_value(cur_element_data, scalar_type)

        if i != n_int - 1:
            summary += f"{cur_element}, "
        else:
            summary += cur_element

    summary += "}"

    return summary

class CustomDenseVectorSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.n = valobj.GetChildMemberWithName("n")

        if not self.n.IsValid():
            raise RuntimeError("n is invalid")

        self.n_int = self.n.GetValueAsUnsigned()

        self.stride = valobj.GetChildMemberWithName("stride_")

        if not self.stride.IsValid():
            raise RuntimeError("offset is invalid")

        self.stride_int = self.stride.GetValueAsUnsigned()

        self.valobj = valobj

        data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

        if not data.IsValid():
            raise RuntimeError("data member is not valid")

        self.data = data

        self.element_type = self.data.GetType().GetPointeeType()
        self.array_type = self.element_type.GetArrayType(self.n_int * self.stride_int)

    def num_children(self, max_children: int) -> int:
        return 3

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "stride_":
            return 1

        if name == "data_":
            return 2

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            return self.stride

        if index == 2:
            return self.data.CreateValueFromAddress(
                "data_",
                self.data.GetValueAsUnsigned(),
                self.array_type
            )

        return None

def to_string_cdv(debugger: lldb.SBDebugger, command: str, result: lldb.SBCommandReturnObject, internal_dict):
    target: lldb.SBTarget = debugger.GetSelectedTarget()

    if not target.IsValid():
        result.PutError("target was invalid")
        return

    frame: lldb.SBFrame = target.GetProcess().GetSelectedThread().GetSelectedFrame()

    if not frame.IsValid():
        result.PutError("frame was invalid")
        return

    valobj: lldb.SBValue = frame.FindVariable(command)

    if not valobj.IsValid():
        result.PutError("valobj was invalid")
        return

    valobj = valobj.GetNonSyntheticValue()

    summary = custom_dense_vector_summary(valobj, internal_dict)

    if vector_to_string_orientation == "vertical":
        summary = summary.replace("{", "{\n ")
        summary = summary.replace("}", "\n}")
        summary = summary.replace(",", "\n")

    result.PutCString(summary)