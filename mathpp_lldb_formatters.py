"""
LLDB Pretty Printer for math++ Matrix class

This module provides custom formatters for the Matrix template class
to display matrices in a human-readable format during debugging sessions.

Usage:
    In LLDB, run: command script import /path/to/lldb_formatters.py
    Or add to .lldbinit file for automatic loading
"""

try:
    import lldb
except ImportError:
    # LLDB module not available when running standalone
    pass

import re


def _unwrap_swig(obj):
    """Unwrap SWIG proxy objects to get the actual LLDB object."""
    # Try multiple unwrapping strategies
    if hasattr(obj, '__dict__') and 'this' in obj.__dict__:
        return obj.__dict__['this']
    if hasattr(obj, 'this'):
        return getattr(obj, 'this')
    # Already unwrapped or different type
    return obj


def _format_matrix_grid(columns, rows, values, value_type):
    """
    Format matrix values in a grid layout.
    
    Args:
        columns: Number of columns
        rows: Number of rows
        values: Flat list of values in column-major order
        value_type: The element type (float, int, etc)
        
    Returns:
        Formatted string showing the matrix as a grid
    """
    # Build 2D array in row-major order for display
    matrix = []
    for row in range(rows):
        row_values = []
        for col in range(columns):
            idx = col * rows + row
            row_values.append(values[idx])
        matrix.append(row_values)
    
    # Format as {{row1}, {row2}, ...}
    row_strings = []
    for row in matrix:
        row_str = ', '.join(str(v) for v in row)
        row_strings.append(f"{{{row_str}}}")
    
    result = ', '.join(row_strings)
    return f"{{{result}}}"


def matrix_summary(valobj, internal_dict):
    """
    Provides a summary string for Matrix objects.
    
    Args:
        valobj: LLDB SBValue object representing the Matrix
        internal_dict: Internal dictionary for caching
        
    Returns:
        A summary string showing matrix dimensions and type
    """
    try:
        # Try to get the actual LLDB SBValue - handle SWIG proxy
        val = valobj
        
        # Check if it's callable (sometimes SWIG objects are)
        if callable(valobj):
            val = valobj()
        
        # Try direct unwrap
        if not hasattr(val, 'GetTypeName'):
            val = _unwrap_swig(valobj)
        
        # Last resort: try to import lldb and cast
        if not hasattr(val, 'GetTypeName'):
            try:
                import lldb
                # The valobj might need to be casted
                if str(type(valobj)) == "<class 'SwigPyObject'>":
                    return "Matrix<?, ?> (SWIG binding issue - use 'p' instead of 'fr v')"
            except:
                pass
        
        # Get type name
        type_name = val.GetTypeName()
        
        # Parse Matrix<COLUMNS, ROWS, T> pattern
        match = re.match(r'Matrix<(\d+),\s*(\d+),\s*(.+)>', type_name)
        if not match:
            return f"Matrix ({type_name})"
        
        columns = int(match.group(1))
        rows = int(match.group(2))
        value_type = match.group(3).strip()
        
        # Try to get the non-synthetic value (unwrap const/reference)
        actual_val = val.GetNonSyntheticValue() if hasattr(val, 'GetNonSyntheticValue') else val
        
        # If it's a reference type, dereference it
        if actual_val.GetType().IsReferenceType():
            actual_val = actual_val.Dereference()
        
        # Try to access data member first (faster)
        data_member = actual_val.GetChildMemberWithName('data')
        
        # For small matrices, show values
        if columns <= 4 and rows <= 4:
            # If we can access data member directly, use it
            if data_member and data_member.IsValid():
                values = []
                for col in range(columns):
                    col_array = data_member.GetChildAtIndex(col)
                    if col_array and col_array.IsValid():
                        for row in range(rows):
                            val_elem = col_array.GetChildAtIndex(row)
                            if val_elem and val_elem.IsValid():
                                val_str = val_elem.GetValue()
                                if val_str:
                                    values.append(val_str)
                
                if len(values) == columns * rows:
                    return _format_matrix_grid(columns, rows, values, value_type)
            
            # Fallback: read raw memory directly
            try:
                import lldb
                addr = actual_val.GetLoadAddress()
                if addr != lldb.LLDB_INVALID_ADDRESS:
                    # Map type to size
                    type_sizes = {'float': 4, 'double': 8, 'int': 4, 'long': 8}
                    elem_size = type_sizes.get(value_type, 4)
                    
                    process = actual_val.GetProcess()
                    error = lldb.SBError()
                    values = []
                    
                    for col in range(columns):
                        for row in range(rows):
                            offset = (col * rows + row) * elem_size
                            data = process.ReadMemory(addr + offset, elem_size, error)
                            if error.Success():
                                import struct
                                format_char = {'float': 'f', 'double': 'd', 'int': 'i', 'long': 'q'}.get(value_type, 'f')
                                val_num = struct.unpack(format_char, data)[0]
                                values.append(f"{val_num:.6g}" if isinstance(val_num, float) else str(val_num))
                    
                    if len(values) == columns * rows:
                        return _format_matrix_grid(columns, rows, values, value_type)
            except:
                pass
        
        return f"Matrix<{columns}x{rows}, {value_type}>"
        
    except Exception as e:
        return f"Matrix<?, ?> (error: {str(e)})"


class MatrixSyntheticProvider:
    """
    Synthetic children provider for Matrix template class.
    
    This class allows LLDB to display matrix elements in a structured way,
    showing individual elements with their row/column positions.
    """
    
    def __init__(self, valobj, internal_dict):
        """
        Initialize the synthetic provider.
        
        Args:
            valobj: LLDB SBValue object representing the Matrix
            internal_dict: Internal dictionary for caching
        """
        # Unwrap SWIG proxy
        self.valobj = _unwrap_swig(valobj)
        self.update()
    
    def num_children(self):
        """
        Returns the number of children (matrix elements).
        
        Returns:
            Total number of elements (columns * rows)
        """
        # Always return at least 1 to force expand button to show
        count = self.columns * self.rows
        return count if count > 0 else 0
    
    def has_children(self):
        """
        Indicates whether this object has children.
        
        Returns:
            True if the matrix has elements
        """
        return (self.columns > 0 and self.rows > 0)
    
    def get_child_index(self, name):
        """
        Get the index for a child by name.
        
        Args:
            name: Child name (e.g., "[0,0]", "[1,2]")
            
        Returns:
            Index of the child or -1 if not found
        """
        try:
            # Parse names like "[col,row]"
            match = re.match(r'\[(\d+),(\d+)\]', name)
            if match:
                col = int(match.group(1))
                row = int(match.group(2))
                if 0 <= col < self.columns and 0 <= row < self.rows:
                    return row * self.columns + col
        except:
            pass
        return -1
    
    def get_child_at_index(self, index):
        """
        Get the child element at the given index.
        
        Args:
            index: Linear index (0 to columns*rows-1)
            
        Returns:
            LLDB SBValue representing the matrix element
        """
        if index < 0 or index >= self.num_children():
            return None
        
        try:
            # Convert linear index to column/row
            row = index // self.columns
            col = index % self.columns
            
            # Get actual value
            actual_val = self.valobj.GetNonSyntheticValue() if hasattr(self.valobj, 'GetNonSyntheticValue') else self.valobj
            if actual_val.GetType().IsReferenceType():
                actual_val = actual_val.Dereference()
            
            # Try to access data member
            data_member = actual_val.GetChildMemberWithName('data')
            if data_member and data_member.IsValid():
                col_array = data_member.GetChildAtIndex(col)
                if col_array and col_array.IsValid():
                    element = col_array.GetChildAtIndex(row)
                    if element and element.IsValid():
                        return element.CreateChildAtOffset(f"[{row},{col}]", 0, element.GetType())
            
            # Fallback: read from memory
            try:
                import lldb
                addr = actual_val.GetLoadAddress()
                if addr != lldb.LLDB_INVALID_ADDRESS:
                    type_sizes = {'float': 4, 'double': 8, 'int': 4, 'long': 8}
                    elem_size = type_sizes.get(self.value_type, 4)
                    
                    offset = (col * self.rows + row) * elem_size
                    
                    # Create type
                    if self.value_type == 'float':
                        elem_type = actual_val.GetTarget().GetBasicType(lldb.eBasicTypeFloat)
                    elif self.value_type == 'double':
                        elem_type = actual_val.GetTarget().GetBasicType(lldb.eBasicTypeDouble)
                    elif self.value_type == 'int':
                        elem_type = actual_val.GetTarget().GetBasicType(lldb.eBasicTypeInt)
                    else:
                        elem_type = actual_val.GetTarget().GetBasicType(lldb.eBasicTypeFloat)
                    
                    return actual_val.CreateChildAtOffset(f"[{row},{col}]", offset, elem_type)
            except:
                pass
            
        except Exception as e:
            pass
        
        return None
    
    def update(self):
        """
        Update internal state when the variable changes.
        
        This method is called by LLDB to refresh the provider's state.
        """
        try:
            # Extract template parameters from type name
            type_name = self.valobj.GetTypeName()
            match = re.match(r'Matrix<(\d+),\s*(\d+),\s*(.+)>', type_name)
            
            if match:
                self.columns = int(match.group(1))
                self.rows = int(match.group(2))
                self.value_type = match.group(3).strip()
            else:
                self.columns = 0
                self.rows = 0
                self.value_type = "unknown"
            
        except Exception as e:
            self.columns = 0
            self.rows = 0
            self.value_type = "error"
    
    def has_children(self):
        """
        Indicates whether this object has children.
        
        Returns:
            True if the matrix has elements
        """
        return (self.columns > 0 and self.rows > 0)


# If running standalone, provide usage information
if __name__ == "__main__":
    print(__doc__)
    print("\nThis script should be imported into LLDB, not run directly.")
    print("Usage: (lldb) command script import /path/to/lldb_formatters.py")
