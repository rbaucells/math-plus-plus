import lldb

def __lldb_init_module(debugger: lldb.SBDebugger, dict):
    # dense vector
    debugger.HandleCommand("command script import ./lldb/dense_vector_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/dense_vector_view_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/custom_dense_vector_lldb_formatter.py")

    # sparse vector
    debugger.HandleCommand("command script import ./lldb/sparse_vector_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/sparse_vector_view_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/custom_sparse_vector_lldb_formatter.py")

    # dense matrix
    debugger.HandleCommand("command script import ./lldb/dense_matrix_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/dense_matrix_view_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/custom_dense_matrix_lldb_formatter.py")

    # sparse matrix
    debugger.HandleCommand("command script import ./lldb/sparse_matrix_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/sparse_matrix_view_lldb_formatter.py")
    debugger.HandleCommand("command script import ./lldb/custom_sparse_matrix_lldb_formatter.py")

    # DenseVector
    debugger.HandleCommand(f'type summary add -x "^DenseVector<.*>$" -F dense_vector_lldb_formatter.dense_vector_summary')
    debugger.HandleCommand(f'type synthetic add -x "^DenseVector<.*>$" --python-class dense_vector_lldb_formatter.DenseVectorSyntheticChildrenProvider')
    debugger.HandleCommand(f'type summary add -x "^DenseVectorView<.*>$" -F dense_vector_view_lldb_formatter.dense_vector_view_summary')
    debugger.HandleCommand(f'type synthetic add -x "^DenseVectorView<.*>$" --python-class dense_vector_view_lldb_formatter.DenseVectorViewSyntheticChildrenProvider')
    debugger.HandleCommand(f'type summary add -x "^CustomDenseVector<.*>$" -F custom_dense_vector_lldb_formatter.custom_dense_vector_summary')
    debugger.HandleCommand(f'type synthetic add -x "^CustomDenseVector<.*>$" --python-class custom_dense_vector_lldb_formatter.CustomDenseVectorSyntheticChildrenProvider')

    # SparseVector
    debugger.HandleCommand(f'type synthetic add -x "^SparseVector<.*>$" --python-class sparse_vector_lldb_formatter.SparseVectorSyntheticChildrenProvider')
    debugger.HandleCommand(f'type synthetic add -x "^SparseVectorView<.*>$" --python-class sparse_vector_view_lldb_formatter.SparseVectorViewSyntheticChildrenProvider')
    debugger.HandleCommand(f'type synthetic add -x "^CustomSparseVector<.*>$" --python-class custom_sparse_vector_lldb_formatter.CustomSparseVectorSyntheticChildrenProvider')

    # DenseMatrix
    debugger.HandleCommand(f'type summary add -x "^DenseMatrix<.*>$" -F dense_matrix_lldb_formatter.dense_matrix_summary')
    debugger.HandleCommand(f'type synthetic add -x "^DenseMatrix<.*>$" --python-class dense_matrix_lldb_formatter.DenseMatrixSyntheticChildrenProvider')
    debugger.HandleCommand(f'type summary add -x "^DenseMatrixView<.*>$" -F dense_matrix_view_lldb_formatter.dense_matrix_view_summary')
    debugger.HandleCommand(f'type synthetic add -x "^DenseMatrixView<.*>$" --python-class dense_matrix_view_lldb_formatter.DenseMatrixViewSyntheticChildrenProvider')
    debugger.HandleCommand(f'type summary add -x "^CustomDenseMatrix<.*>$" -F custom_dense_matrix_lldb_formatter.custom_dense_matrix_summary')
    debugger.HandleCommand(f'type synthetic add -x "^CustomDenseMatrix<.*>$" --python-class custom_dense_matrix_lldb_formatter.CustomDenseMatrixSyntheticChildrenProvider')

    # SparseMatrix
    debugger.HandleCommand(f'type synthetic add -x "^SparseMatrix<.*>$" --python-class sparse_matrix_lldb_formatter.SparseMatrixSyntheticChildrenProvider')
    debugger.HandleCommand(f'type synthetic add -x "^SparseMatrixView<.*>$" --python-class sparse_matrix_view_lldb_formatter.SparseMatrixViewSyntheticChildrenProvider')
    debugger.HandleCommand(f'type synthetic add -x "^CustomSparseMatrix<.*>$" --python-class custom_sparse_matrix_lldb_formatter.CustomSparseMatrixSyntheticChildrenProvider')

    # to_string
    debugger.HandleCommand(f'command script add -f mathpp_lldb_formatter.to_string to_string')


def to_string(debugger: lldb.SBDebugger, command: str, result: lldb.SBCommandReturnObject, internal_dict):
    frame: lldb.SBFrame = debugger.GetSelectedTarget().GetProcess().GetSelectedThread().GetSelectedFrame()
    valobj: lldb.SBValue = frame.FindVariable(command).GetNonSyntheticValue()

    valobj_type: lldb.SBType = valobj.GetType()
    type_name: str = valobj_type.GetName()

    if "Dense" in type_name:
        if "Vector" in type_name:
            if "View" in type_name:
                import dense_vector_view_lldb_formatter
                result.PutCString(dense_vector_view_lldb_formatter.to_string(valobj))
                return

            if "Custom" in type_name:
                import custom_dense_vector_lldb_formatter
                result.PutCString(custom_dense_vector_lldb_formatter.to_string(valobj))
                return

            import dense_vector_lldb_formatter
            result.PutCString(dense_vector_lldb_formatter.to_string(valobj))
            return

        if "Matrix" in type_name:
            if "View" in type_name:
                import dense_matrix_view_lldb_formatter
                result.PutCString(dense_matrix_view_lldb_formatter.to_string(valobj))
                return

            if "Custom" in type_name:
                import custom_dense_matrix_lldb_formatter
                result.PutCString(custom_dense_matrix_lldb_formatter.to_string(valobj))
                return

            import dense_matrix_lldb_formatter
            result.PutCString(dense_matrix_lldb_formatter.to_string(valobj))
            return

    if "Sparse" in type_name:
        if "Vector" in type_name:
            if "View" in type_name:
                import sparse_vector_view_lldb_formatter
                result.PutCString(sparse_vector_view_lldb_formatter.to_string(valobj))
                return

            if "Custom" in type_name:
                import custom_sparse_vector_lldb_formatter
                result.PutCString(custom_sparse_vector_lldb_formatter.to_string(valobj))
                return

            import sparse_vector_lldb_formatter
            result.PutCString(sparse_vector_lldb_formatter.to_string(valobj))
            return

        if "Matrix" in type_name:
            if "View" in type_name:
                import sparse_matrix_view_lldb_formatter
                result.PutCString(sparse_matrix_view_lldb_formatter.to_string(valobj))
                return

            if "Custom" in type_name:
                import custom_sparse_matrix_lldb_formatter
                result.PutCString(custom_sparse_matrix_lldb_formatter.to_string(valobj))
                return

            import sparse_matrix_lldb_formatter
            result.PutCString(sparse_matrix_lldb_formatter.to_string(valobj))
            return

    result.PutError(f"unknown type = {type_name}")
