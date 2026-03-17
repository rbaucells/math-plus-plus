from utils import *
import lldb


class SparseVectorViewSyntheticChildrenProvider:
    def __init__(self, valobj: lldb.SBValue, internal_dict):
        self.valobj: lldb.SBValue = valobj

        self.n: lldb.SBValue = valobj.GetChildMemberWithName("n")
        self.n_int: int = self.n.GetValueAsUnsigned()

        self.offset: lldb.SBValue = valobj.GetChildMemberWithName("offset_")
        self.offset_int: int = self.offset.GetValueAsUnsigned()

        self.owner: lldb.SBValue = valobj.GetChildMemberWithName("owner_")

        values: lldb.SBValue = self.owner.GetChildMemberWithName("values_")
        indices: lldb.SBValue = self.owner.GetChildMemberWithName("indices_")

        self.values_element_type: lldb.SBType = values.GetType().GetPointeeType()
        self.indices_element_type: lldb.SBType = indices.GetType().GetPointeeType()

    def num_children(self, max_children: int) -> int:
        return 5

    def get_child_index(self, name: str) -> int:
        if name == "n":
            return 0

        if name == "nnz_":
            return 1

        if name == "values_":
            return 2

        if name == "indices_":
            return 3

        if name == "owner_":
            return 4

        return -1

    def get_child_at_index(self, index: int):
        if index == 0:
            return self.n

        if index == 1:
            return self.valobj.GetChildMemberWithName("nnz_")

        if index == 2:
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_")
            nnz_int: int = nnz.GetValueAsUnsigned()

            values: lldb.SBValue = self.owner.GetChildMemberWithName("values_")
            indices: lldb.SBValue = self.owner.GetChildMemberWithName("indices_")

            data: lldb.SBData = lldb.SBData()

            count: int = 0
            for i in range(0, nnz_int):
                cur_index: lldb.SBValue = iterate_data_array(indices, i)
                cur_index_int: int = cur_index.GetValueAsUnsigned()

                if cur_index_int < self.offset_int or cur_index_int > self.offset_int + self.n_int:
                    continue

                cur_value = iterate_data_array(values, i)

                data.Append(cur_value.GetData())
                count += 1

            values_array_type: lldb.SBType = self.values_element_type.GetArrayType(count)

            return values.CreateValueFromData(
                "values_",
                data,
                values_array_type
            )

        if index == 3:
            nnz: lldb.SBValue = self.valobj.GetChildMemberWithName("nnz_")
            nnz_int: int = nnz.GetValueAsUnsigned()

            indices: lldb.SBValue = self.owner.GetChildMemberWithName("indices_")

            data: lldb.SBData = lldb.SBData()

            count: int = 0
            for i in range(0, nnz_int):
                cur_index: lldb.SBValue = iterate_data_array(indices, i)
                cur_index_int: int = cur_index.GetValueAsUnsigned()

                if cur_index_int < self.offset_int or cur_index_int > self.offset_int + self.n_int:
                    continue

                data.Append(cur_index.GetData())
                count += 1

            indices_array_type: lldb.SBType = self.indices_element_type.GetArrayType(count)

            return indices.CreateValueFromData(
                "indices_",
                data,
                indices_array_type
            )

        if index == 4:
            return self.owner

        return None


def to_string(valobj: lldb.SBValue):
    ...