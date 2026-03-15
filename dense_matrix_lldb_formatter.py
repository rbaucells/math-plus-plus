import numbers

import lldb

precision: int = 2

def __lldb_init_module(debugger: lldb.SBDebugger, dict):
    debugger.HandleCommand(f'type summary add -x "^DenseMatrix<.*>$" -F dense_matrix_lldb_formatter.dense_matrix_summary')
    print("Imported dense_matrix_lldb_formatter.py")

def dense_matrix_summary(valobj: lldb.SBValue, internal_dict):
    columns: lldb.SBValue = valobj.GetChildMemberWithName("columns")

    if not columns.IsValid():
        raise RuntimeError("columns member is not valid")

    rows: lldb.SBValue = valobj.GetChildMemberWithName("rows")

    if not rows.IsValid():
        raise RuntimeError("rows member is not valid")

    columns_int: int = columns.GetValueAsSigned()
    rows_int: int = rows.GetValueAsSigned()

    if columns_int == 0 or rows_int == 0:
        raise RuntimeError("empty dense matrix")

    if columns_int > 5 or rows_int > 5:
        return ""

    data: lldb.SBValue = valobj.GetChildMemberWithName("data_")

    if not data.IsValid():
        raise RuntimeError("data member is not valid")

    if data.GetValueAsSigned() == 0:
        raise RuntimeError("data member is nullptr")

    summary: str = "{"

    for r in range(0, rows_int):
        summary += "{"
        for c in range(0, columns_int):
            index: int = c * rows_int + r

            cur_element: lldb.SBValue = data.GetChildAtIndex(index, lldb.eNoDynamicValues, True)

            if not cur_element.IsValid():
                raise RuntimeError(f"cur_element at (c = {c}, r = {r}, index = {index}) is not valid")

            value: str = cur_element.GetValue()

            value = value[0:value.find(".") + precision + 1]

            if c != columns_int - 1:
                summary += f"{value}, "
            else:
                summary += value

        if r != rows_int - 1:
            summary += "}, "
        else:
            summary += "}"

    summary += "}"

    return summary