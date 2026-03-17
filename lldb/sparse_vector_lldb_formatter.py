from utils import *
import lldb

class SparseVectorSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.n: lldb.SBValue = valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()

        values: lldb.SBValue = valobj.GetChildMemberWithName("values_")
        indices: lldb.SBValue = valobj.GetChildMemberWithName("indices_")

        self.values_element_type: lldb.SBType = values.GetType().GetPointeeType()
        self.indices_element_type: lldb.SBType = indices.GetType().GetPointeeType()


    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "nnz_":
            return 1

        if name == "values_":
            return 2

        if name == "indices_":
            return 3

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_")
            return nnz

        if index == 2:
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_")
            nnz_int: int = nnz.GetValueAsUnsigned()

            values_array_type: lldb.SBType = self.values_element_type.GetArrayType(nnz_int)

            values: lldb.SBValue = self.valobj.GetChildMemberWithName("values_")

            return values.CreateValueFromAddress(
                "values_",
                values.GetValueAsUnsigned(),
                values_array_type
            )

        if index == 3:
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_")
            nnz_int: int = nnz.GetValueAsUnsigned()

            indices_array_type: lldb.SBType = self.indices_element_type.GetArrayType(nnz_int)

            indices: lldb.SBValue = self.valobj.GetChildMemberWithName("indices_")

            return indices.CreateValueFromAddress(
                "indices_",
                indices.GetValueAsUnsigned(),
                indices_array_type
            )

        return None

def to_string_sv(debugger: lldb.SBDebugger, command: str, result: lldb.SBCommandReturnObject, internal_dict):
    frame: lldb.SBFrame = debugger.GetSelectedTarget().GetProcess().GetSelectedThread().GetSelectedFrame()
    valobj: lldb.SBValue = frame.FindVariable(command).GetNonSyntheticValue()

    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()

    nnz: lldb.SBValue = valobj.GetChildMemberWithName("nnz_")
    nnz_int: int = nnz.GetValueAsUnsigned()

    values: lldb.SBValue = valobj.GetChildMemberWithName("values_")
    indices: lldb.SBValue = valobj.GetChildMemberWithName("indices_")

    values_element_type: lldb.SBType = values.GetType().GetPointeeType()
    values_scalar_type: ScalarType = scalar_type_from_type(values_element_type)

    values_summary: str = "{"
    indices_summary: str = "{"

    for i in range(0, nnz_int):
        cur_values_element_data: lldb.SBValue = iterate_data_array(values, i)

        if cur_values_element_data.IsValid():
            cur_element = get_str_from_value(cur_values_element_data, values_scalar_type)
        else:
            cur_element = "N/A"

        if i != nnz_int - 1:
            values_summary += f"{cur_element}, "
        else:
            values_summary += cur_element

        cur_indices_element_data: lldb.SBValue = iterate_data_array(indices, i)

        if cur_indices_element_data.IsValid():
            cur_element = get_str_from_value(cur_indices_element_data, ScalarType.Integer)
        else:
            cur_element = "N/A"

        if i != nnz_int - 1:
            indices_summary += f"{cur_element}, "
        else:
            indices_summary += cur_element

    values_summary += "}"
    indices_summary += "}"

    if vector_to_string_orientation == "vertical":
        values_summary = values_summary.replace("{", "{\n    ")
        values_summary = values_summary.replace("}", "\n}")
        values_summary = values_summary.replace(", ", "\n    ")

        indices_summary = indices_summary.replace("{", "{\n    ")
        indices_summary = indices_summary.replace("}", "\n}")
        indices_summary = indices_summary.replace(", ", "\n    ")

    result.PutCString(f"n = {n_int}\nnnz_ = {nnz_int}\nvalues_ = {values_summary}\nindices_ = {indices_summary}")

