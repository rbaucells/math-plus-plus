import lldb


def __lldb_init_module(debugger: lldb.SBDebugger, dict):
    debugger.HandleCommand("command script import /Users/ricardo/Projects/math-plus-plus/lldb/dense_vector_lldb_formatter.py")
    debugger.HandleCommand("command script import /Users/ricardo/Projects/math-plus-plus/lldb/dense_matrix_lldb_formatter.py")

    debugger.HandleCommand(f'type summary add -x "^DenseVector<.*>$" -F dense_vector_lldb_formatter.dense_vector_summary')
    debugger.HandleCommand(f'type synthetic add -x "^DenseVector<.*>$" --python-class dense_vector_lldb_formatter.DenseVectorSyntheticChildrenProvider')
    debugger.HandleCommand(f'command script add -f dense_vector_lldb_formatter.to_string_dv to_string_dv')

    debugger.HandleCommand(f'type summary add -x "^DenseMatrix<.*>$" -F dense_matrix_lldb_formatter.dense_matrix_summary')
    debugger.HandleCommand(f'type synthetic add -x "^DenseMatrix<.*>$" --python-class dense_matrix_lldb_formatter.DenseMatrixSyntheticChildrenProvider')
    debugger.HandleCommand(f'command script add -f dense_matrix_lldb_formatter.to_string_dm to_string_dm')
