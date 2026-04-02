import lldb
from utils import ScalarType, get_real_type, get_str_from_value, iterate_data_array, scalar_type_from_type


def custom_sparse_vector_summary(valobj: lldb.SBValue, internal_dict):
    # get non-synthetic value to access actual CustomSparseVector members
    valobj = valobj.GetNonSyntheticValue()
    # get vector type and scalar type
    custom_sparse_vector_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_sparse_vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()
    if n_int == 0:
        return "Empty Vector (n = 0)"
    # nnz — pointer-to-pointer field
    nnz_int: int = valobj.GetChildMemberWithName("nnz_").Dereference().GetValueAsUnsigned()
    if nnz_int == 0:
        return f"CustomSparseVector<n={n_int}> nnz=0"
    # values, indices — pointer-to-pointer fields
    values: lldb.SBValue = valobj.GetChildMemberWithName("values_").Dereference()
    indices: lldb.SBValue = valobj.GetChildMemberWithName("indices_").Dereference()
    # null values pointer indicates moved-from state
    if values.GetValueAsSigned() == 0:
        return "Moved-from Vector (values_ = nullptr)"
    # build compact summary string
    summary: str = "{"
    for i in range(nnz_int):
        cur_index: lldb.SBValue = iterate_data_array(indices, i)
        cur_value: lldb.SBValue = iterate_data_array(values, i)
        index_str = get_str_from_value(cur_index, ScalarType.Integer) if cur_index.IsValid() else "N/A"
        value_str = get_str_from_value(cur_value, scalar_type) if cur_value.IsValid() else "N/A"
        entry_str = f"{index_str}: {value_str}"
        # add entry string to summary
        summary += entry_str if i == nnz_int - 1 else f"{entry_str}, "
    summary += "}"
    # exit
    return summary


class CustomSparseVectorSyntheticChildrenProvider:

    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj
        self._refresh()

    def _refresh(self):
        # n
        self.n: lldb.SBValue = self.valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()
        # nnz — pointer-to-pointer field: dereference to read value and cache type
        nnz_deref: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_").Dereference()
        self.nnz_int: int = nnz_deref.GetValueAsUnsigned()
        self.nnz_type: lldb.SBType = nnz_deref.GetType()
        # values, indices — pointer-to-pointer fields
        values_deref: lldb.SBValue = self.valobj.GetChildMemberWithName("values_").Dereference()
        indices_deref: lldb.SBValue = self.valobj.GetChildMemberWithName("indices_").Dereference()
        # element types for array view children
        self.values_element_type: lldb.SBType = values_deref.GetType().GetPointeeType()
        self.indices_element_type: lldb.SBType = indices_deref.GetType().GetPointeeType()

    def update(self):
        self._refresh()

    def num_children(self, max_children: int) -> int:
        return 4

    def get_child_index(self, name: str) -> int:
        # map child name to index for n, nnz_, values_, and indices_ children
        if name == "n":
            return 0
        if name == "nnz_":
            return 1
        if name == "values_":
            return 2
        if name == "indices_":
            return 3
        # default case for unrecognized child name
        return -1

    def get_child_at_index(self, index: int):
        # map index to child for n, nnz_, values_, and indices_ children
        if index == 0:
            return self.n
        if index == 1:
            # build nnz_ scalar value from cached int — direct Dereference() yields an awkward display name
            data: lldb.SBData = lldb.SBData.CreateDataFromInt(self.nnz_int)
            return self.valobj.CreateValueFromData("nnz_", data, self.nnz_type)
        if index == 2:
            values: lldb.SBValue = self.valobj.GetChildMemberWithName("values_").Dereference()
            values_array_type: lldb.SBType = self.values_element_type.GetArrayType(self.nnz_int)
            return self.valobj.CreateValueFromAddress("values_", values.GetValueAsUnsigned(), values_array_type)
        if index == 3:
            indices: lldb.SBValue = self.valobj.GetChildMemberWithName("indices_").Dereference()
            indices_array_type: lldb.SBType = self.indices_element_type.GetArrayType(self.nnz_int)
            return self.valobj.CreateValueFromAddress("indices_", indices.GetValueAsUnsigned(), indices_array_type)
        # exit
        return None


def to_string(valobj: lldb.SBValue) -> str:
    # get vector type and scalar type
    custom_sparse_vector_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(custom_sparse_vector_type.GetTemplateArgumentType(0))
    # n
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()
    # nnz — pointer-to-pointer field
    nnz_int: int = valobj.GetChildMemberWithName("nnz_").Dereference().GetValueAsUnsigned()
    # values, indices — pointer-to-pointer fields
    values: lldb.SBValue = valobj.GetChildMemberWithName("values_").Dereference()
    indices: lldb.SBValue = valobj.GetChildMemberWithName("indices_").Dereference()
    # build values_ and indices_ summaries
    values_summary: str = "{"
    indices_summary: str = "{"
    for i in range(nnz_int):
        cur_values_element: lldb.SBValue = iterate_data_array(values, i)
        value_str = get_str_from_value(cur_values_element, scalar_type) if cur_values_element.IsValid() else "N/A"
        cur_indices_element: lldb.SBValue = iterate_data_array(indices, i)
        index_str = get_str_from_value(cur_indices_element, ScalarType.Integer) if cur_indices_element.IsValid() else "N/A"
        # add element strings to summaries
        values_summary += value_str if i == nnz_int - 1 else f"{value_str}, "
        indices_summary += index_str if i == nnz_int - 1 else f"{index_str}, "
    values_summary += "}"
    indices_summary += "}"
    # exit
    return f"n = {n_int}\nnnz_ = {nnz_int}\nvalues_ = {values_summary}\nindices_ = {indices_summary}"
