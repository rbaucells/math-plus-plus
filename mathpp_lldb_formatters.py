# Pretty printer for math++ types

# it doesnt matter if we cant import lldb because LLDB injects its own python stuff
try:
    import lldb
except ImportError:
    pass

from typing import Any, Dict
import re
def _unwrap_swig(obj):
    """Get the actual c++ object"""

    # try to get the internal storage
    if hasattr(obj, '__dict__') and 'this' in obj.__dict__:
        return obj.__dict__['this']

    # try getting the "this" pointer
    if hasattr(obj, 'this'):
        return getattr(obj, 'this')

    # its already unwrapped
    return obj


def _format_matrix_grid(columns: int, rows: int, value_type: str, data: list[str]) -> str:
    string = f"= ["

    for r in range(rows):
        string += "["
        for c in range(columns):
            string += data[c * rows + r]

            if c < columns - 1:
                string += ", "

        string += "]"

        if r < rows - 1:
            string += ", "

    string += "]"
    return string


use_data = False

def matrix_summary(matrix_obj: Any, internal_dict: Dict[str, Any]) -> str:
    """
    A summary string showing matrix dimensions and type, and if its small enough inline it.

    Args:
        matrix_obj: LLDB SBValue object representing the Matrix
        internal_dict: Internal dictionary for caching
    """

    try:
        # get the actual matrix object
        val: Any = matrix_obj

        if callable(matrix_obj):
            val = matrix_obj()

        if not hasattr(val, 'GetTypeName') and '_unwrap_swig' in globals():
            val = _unwrap_swig(matrix_obj)

        if not hasattr(val, 'GetTypeName'):
            try:
                if str(type(matrix_obj)) == "<class 'SwigPyObject'>":
                    return "Matrix<?, ?> (SWIG binding issue - use 'p' instead of 'fr v')"
            except Exception:
                pass

        # parse the Matrix<COLUMNS, ROWS, T> for COLUMNS, ROWS, and T
        type_name: str = val.GetTypeName()
        match = re.match(r'Matrix<(\d+),\s*(\d+),\s*(.+)>', type_name)
        if not match:
            return type_name

        COLUMNS: int = int(match.group(1))
        ROWS: int = int(match.group(2))
        T: str = match.group(3).strip()

        # get the real deal stuff, dereference if needed
        actual_val: Any = val.GetNonSyntheticValue() if hasattr(val, 'GetNonSyntheticValue') else val

        if actual_val.GetType().IsReferenceType():
            actual_val = actual_val.Dereference()

        # matrix too big to inline, return blank
        if COLUMNS > 6 or ROWS > 6:
            return ""

        # access the .data field
        data_member: Any = actual_val.GetChildMemberWithName('data')

        # if we can access the .data member
        if data_member and data_member.IsValid() and use_data:
            values: list[str] = []

            # iterate columns
            for c in range(COLUMNS):
                col_array: Any = data_member.GetChildAtIndex(c)

                # invalid column, return blank
                if not col_array or not col_array.IsValid():
                    return ""

                # iterate rows
                for r in range(ROWS):
                    element_val: Any = col_array.GetChildAtIndex(r)

                    # invalid element, append ?
                    if not element_val or not element_val.IsValid():
                        values.append("?")
                        continue

                    formatted_val = format_scalar(element_val, 3)
                    values.append(formatted_val)

            # if we got the correct number of stuffs, return it nicely formatted
            if len(values) == COLUMNS * ROWS:
                return _format_matrix_grid(COLUMNS, ROWS, T, values)

        if 'lldb' not in globals():
            return ""

        # else we need to try via the raw memory
        try:
            # get the matrix's memory address
            addr: int = actual_val.GetLoadAddress()

            # make sure its legit
            if lldb and addr == lldb.LLDB_INVALID_ADDRESS:
                return "(error: invalid memory address)"

            # get the element type (not string like T) via template parameters
            elem_type: Any = matrix_obj.GetType().GetTemplateArgumentType(2)

            # calculate byte size
            elem_byte_size: int = elem_type.GetByteSize()

            values: list[str] = []

            # iterate columns
            for c in range(COLUMNS):
                # iterate rows
                for r in range(ROWS):
                    # calculate memory offset
                    offset: int = (c * ROWS + r) * elem_byte_size

                    # get the value at that address using the proper type
                    element_val: Any = matrix_obj.CreateValueFromAddress(f"[{c}, {r}]", addr + offset, elem_type)

                    # invalid element, append ?
                    if not element_val or not element_val.IsValid():
                        values.append("?")
                        continue

                    formatted_val = format_scalar(element_val, 3)
                    values.append(formatted_val)

            if len(values) == COLUMNS * ROWS:
                return _format_matrix_grid(COLUMNS, ROWS, T, values)

        except Exception as e:
            return f"(error: {str(e)})"

    except Exception as e:
        return f"(error: {str(e)})"

    return ""


def format_scalar(element, precision: int = 3) -> str:
    """
    Format a scalar as a string

    Args:
        element: The value to be formatted (SBValue)
        precision: For floating-point numbers, how many decimals of precision (int)

    Supported types:
        - short (1)
        - unsigned short (2)
        - int (3)
        - unsigned int (4)
        - long (5)
        - unsigned long (6)
        - long long (7)
        - unsigned long long (8)
        - float (9.10)
        - double (11.12)
        - long double (13.14)
        - std::complex<short> (1 + 2i)
        - std::complex<unsigned short> (3 + 4i)
        - std::complex<int> (5 + 6i)
        - std::complex<unsigned int> (7 + 8i)
        - std::complex<long> (9 + 10i)
        - std::complex<unsigned long> (11 + 12i)
        - std::complex<long long> (13 + 14i)
        - std::complex<unsigned long long> (15 + 16i)
        - std::complex<float> (17.18 + 19.20i)
        - std::complex<double> (21.22 + 23.24i)
        - std::complex<long double> (25.26 + 27.28i)
    """

    if not element or not element.IsValid():
        return "?"

    elem_type = element.GetType()
    type_name = elem_type.GetName()

    # std::complex<T>
    if "complex" in type_name:
        # sometimes we need to access it through the private members
        real_val = element.GetChildMemberWithName("__re_")
        imag_val = element.GetChildMemberWithName("__im_")

        # we might have to access it via _M_value
        if not real_val or not real_val.IsValid() or not imag_val or not imag_val.IsValid():
            val = element.GetChildMemberWithName("_M_value")
            real_val = val.GetChildAtIndex(0)
            imag_val = val.GetChildAtIndex(1)

        real_str = real_val.GetValue()
        imag_str = imag_val.GetValue()
        # handle negative image nicely (1 - 4i) instead of (1 + -4i)
        if imag_str.startswith('-'):
            imag_str_without_minus = imag_str.rstrip('-')
            return f"{real_str} - {imag_str_without_minus}i"
        else:
            return f"{real_str} + {imag_str}i"


    # floating point
    if lldb and elem_type.GetTypeClass() == lldb.eTypeClassBuiltin and ("float" in type_name or "double" in type_name):
        # get it as a double
        num = float(element.GetValue())
        # format
        formatted = f"{num:.{precision}f}"
        # return with whitespace removed
        return formatted.rstrip(".")

    # integers
    return element.GetValue()



class MatrixSyntheticProvider:
    def __init__(self, valobj, internal_dict):
        """
        Initialize the synthetic provider.

        Args:
            valobj: LLDB SBValue object representing the Matrix
            internal_dict: Internal dictionary for caching
        """

        # get reference to real c++ object
        self.valobj = _unwrap_swig(valobj)
        self.internal_dict = internal_dict

        self.set_columns_rows_and_value_type()

    def set_columns_rows_and_value_type(self):
        try:
            # extract template parameters from name
            type_name = self.valobj.GetTypeName()
            match = re.match(r'Matrix<(\d+),\s*(\d+),\s*([^>]+)>', type_name)

            # we got stuff, set it
            if match:
                self.internal_dict["columns"] = int(match.group(1))
                self.internal_dict["rows"] = int(match.group(2))
                self.internal_dict["value_type"] = match.group(3).strip()
            else:
                self.internal_dict["columns"] = 0
                self.internal_dict["rows"] = 0
                self.internal_dict["value_type"] = "unknown"

        except Exception as e:
            self.internal_dict["columns"] = 0
            self.internal_dict["rows"] = 0
            self.internal_dict["value_type"] = "error"

    def num_children(self):
        return self.internal_dict["columns"] * self.internal_dict["rows"]

    def has_children(self):
        return self.internal_dict["columns"] > 0 and self.internal_dict["rows"] > 0

    def get_child_index(self, name):
        """Get a childs index from a name ("[0,0]", "[1,2]"""

        try:
            # find the child by the name and extract the col and row index
            match = re.match(r'\[(\d+),(\d+)]', name)

            # if we found something
            if match:
                col = int(match.group(1))
                row = int(match.group(2))

                # if its within range
                if 0 <= col < self.internal_dict["columns"] and 0 <= row < self.internal_dict["rows"]:
                    return col * self.internal_dict["rows"] + row
        except:
            pass

        # we didn't find something or had an error, -1 is error
        return -1

    def get_child_at_index(self, index):
        """get the child element at the linear index 'index'"""

        # invalid index
        if index < 0 or index >= self.num_children():
            return None

        # get real col and row index
        col = index // self.internal_dict["rows"]
        row = index % self.internal_dict["rows"]

        # try to dereference the matrix and access it via the data array
        try:
            # dereference matrix pointer/reference
            actual_val = self.valobj.GetNonSyntheticValue() if hasattr(self.valobj, 'GetNonSyntheticValue') else self.valobj
            if actual_val.GetType().IsReferenceType():
                actual_val = actual_val.Dereference()

            # get the data field, and read from it
            data_member = actual_val.GetChildMemberWithName('data')

            if data_member and data_member.IsValid():
                col_array = data_member.GetChildAtIndex(col)

                if col_array and col_array.IsValid():
                    element = col_array.GetChildAtIndex(row)

                    if element and element.IsValid():
                        return element

            # if that didn't work, get it by memory
            try:
                # get the mem address of the matrix
                addr = actual_val.GetLoadAddress()

                # if its legit
                if lldb and addr != lldb.LLDB_INVALID_ADDRESS:
                    # calculate the offset
                    offset = (col * self.internal_dict["rows"] + row) * self.element_size()

                    # return
                    return actual_val.CreateChildAtOffset(f"[{col},{row}]", offset, self.element_type())
            except:
                pass
        except:
            pass

        # error
        return None

    def element_type(self):
        return self.valobj.GetTemplateArgumentType(2)

    def element_size(self):
        return self.element_type().GetByteSize()

    def update(self):
        ...


# if running the script itself
if __name__ == "__main__":
    print("This script is meant to be ran by LLDB, not directly.")
    print("To use it: command script import /path/to/lldb_formatters.py")
