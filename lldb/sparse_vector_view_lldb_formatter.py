import textwrap

from utils import *
import lldb
import sparse_vector_lldb_formatter


class SparseVectorViewSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.n: lldb.SBValue = valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()

        self.offset: lldb.SBValue = valobj.GetChildMemberWithName("offset_")
        self.offset_int: int = self.offset.GetValueAsUnsigned()

        self.owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

        owner_values: lldb.SBValue = self.owner.GetChildMemberWithName("values_")
        owner_indices: lldb.SBValue = self.owner.GetChildMemberWithName("indices_")
        owner_nnz: lldb.SBValue = self.owner.GetChildMemberWithName("nnz_")

        self.owner_values_element_type: lldb.SBType = owner_values.GetType().GetPointeeType()
        self.owner_indices_element_type: lldb.SBType = owner_indices.GetType().GetPointeeType()
        self.owner_nnz_type: lldb.SBType = owner_nnz.GetType()

    def num_children(self, max_children: int) -> int:
        return 5

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "nnz_view":
            return 1

        if name == "values_view":
            return 2

        if name == "indices_view":
            return 3

        if name == "owner_":
            return 4

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            owner_nnz: lldb.SBValue = self.owner.GetChildMemberWithName("nnz_")
            owner_nnz_int: int = owner_nnz.GetValueAsUnsigned()

            owner_indices: lldb.SBValue = self.owner.GetChildMemberWithName("indices_")

            nnz_int: int = calculate_nnz(owner_nnz_int, owner_indices, self.n_int, self.offset_int)

            data: lldb.SBData = lldb.SBData.CreateDataFromInt(nnz_int)

            return self.valobj.CreateValueFromData(
                "nnz_view",
                data,
                self.owner_nnz_type
            )

        if index == 2:
            owner_nnz: lldb.SBValue = self.owner.GetChildMemberWithName("nnz_")
            owner_nnz_int: int = owner_nnz.GetValueAsUnsigned()

            owner_values: lldb.SBValue = self.owner.GetChildMemberWithName("values_")
            owner_indices: lldb.SBValue = self.owner.GetChildMemberWithName("indices_")

            data: lldb.SBData = lldb.SBData()

            nnz_int: int = 0
            for i in range(0, owner_nnz_int):
                cur_index: lldb.SBValue = iterate_data_array(owner_indices, i)
                cur_index_int: int = cur_index.GetValueAsUnsigned()

                if cur_index_int < self.offset_int or cur_index_int >= self.n_int + self.offset_int:
                    continue

                cur_value = iterate_data_array(owner_values, i)
                data.Append(cur_value.GetData())

                nnz_int += 1

            values_array_type: lldb.SBType = self.owner_values_element_type.GetArrayType(nnz_int)

            return self.valobj.CreateValueFromData(
                "values_view",
                data,
                values_array_type
            )

        if index == 3:
            owner_nnz: lldb.SBValue = self.owner.GetChildMemberWithName("nnz_")
            owner_nnz_int: int = owner_nnz.GetValueAsUnsigned()

            owner_indices: lldb.SBValue = self.owner.GetChildMemberWithName("indices_")

            data: lldb.SBData = lldb.SBData()

            nnz_int: int = 0
            for i in range(0, owner_nnz_int):
                cur_index: lldb.SBValue = iterate_data_array(owner_indices, i)
                cur_index_int: int = cur_index.GetValueAsUnsigned()

                if cur_index_int < self.offset_int or cur_index_int >= self.n_int + self.offset_int:
                    continue

                relative_cur_index_int: int = cur_index_int - self.offset_int

                data.Append(lldb.SBData.CreateDataFromInt(relative_cur_index_int))

                nnz_int += 1

            indices_array_type: lldb.SBType = self.owner_indices_element_type.GetArrayType(nnz_int)

            return self.valobj.CreateValueFromData(
                "indices_view",
                data,
                indices_array_type
            )

        if index == 4:
            return self.owner

        return None


def calculate_nnz(owner_nnz: int, indices: lldb.SBValue, n: int, offset: int) -> int:
    nnz: int = 0

    for i in range(0, owner_nnz):
        cur_index: lldb.SBValue = iterate_data_array(indices, i)
        cur_index_int: int = cur_index.GetValueAsUnsigned()

        if offset <= cur_index_int < n + offset:
            nnz += 1

    return nnz


def to_string(valobj: lldb.SBValue):
    sparse_vector_view_type: lldb.SBType = get_real_type(valobj.GetType())
    scalar_type: ScalarType = scalar_type_from_type(sparse_vector_view_type.GetTemplateArgumentType(0))
    n: lldb.SBValue = valobj.GetChildMemberWithName("n")
    n_int: int = n.GetValueAsUnsigned()

    offset: lldb.SBValue = valobj.GetChildMemberWithName("offset_")
    offset_int: int = offset.GetValueAsUnsigned()

    owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

    owner_values: lldb.SBValue = owner.GetChildMemberWithName("values_")
    owner_indices: lldb.SBValue = owner.GetChildMemberWithName("indices_")
    owner_nnz: lldb.SBValue = owner.GetChildMemberWithName("nnz_")

    owner_nnz_int: int = owner_nnz.GetValueAsUnsigned()
    nnz_int: int = calculate_nnz(owner_nnz_int, owner_indices, n_int, offset_int)

    indices_view_summary: str = "{"
    values_view_summary: str = "{"

    for i in range(owner_nnz_int):
        cur_index: lldb.SBValue = iterate_data_array(owner_indices, i)
        cur_index_int: int = cur_index.GetValueAsUnsigned()

        if cur_index_int < offset_int or cur_index_int >= n_int + offset_int:
            continue

        relative_cur_index_int: int = cur_index_int - offset_int

        if cur_index.IsValid():
            cur_element = str(relative_cur_index_int)
        else:
            cur_element = "N/A"

        if i != nnz_int - 1:
            indices_view_summary += f"{cur_element}, "
        else:
            indices_view_summary += cur_element

        cur_value: lldb.SBValue = iterate_data_array(owner_values, i)

        if cur_value.IsValid():
            cur_element = get_str_from_value(cur_value, scalar_type)
        else:
            cur_element = "N/A"

        if i != nnz_int - 1:
            values_view_summary += f"{cur_element}, "
        else:
            values_view_summary += cur_element

    indices_view_summary += "}"
    values_view_summary += "}"

    owner_summary: str = sparse_vector_lldb_formatter.to_string(owner)
    owner_summary: str = textwrap.indent(owner_summary, "    ")

    return f"n = {n_int}\nnnz_view = {nnz_int}\noffset_ = {offset_int}\nvalues_view = {values_view_summary}\nindices_view = {indices_view_summary}\nowner_ = {{\n{owner_summary}\n}}"
