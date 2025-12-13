# LLDB Pretty Printer for math++ Matrix Class

This directory contains LLDB debugger formatters for the math++ library, specifically for the `Matrix` template class.

## Files

- **`lldb_formatters.py`**: Python script containing the LLDB pretty printer implementation
- **`.lldbinit`**: LLDB initialization file that automatically loads the formatters
- **`.vscode/launch.json`**: VS Code debug configurations with LLDB integration

## Features

The LLDB formatter provides:

1. **Summary Display**: Shows matrix dimensions and type in a compact format
   ```
   Matrix<3x3, float> [1.0, 0.0, 0.0, 0.0, 1.0, 0.0...]
   ```

2. **Synthetic Children**: Displays individual matrix elements with their positions
   ```
   matrix
     ├─ [0,0] = 1.0
     ├─ [0,1] = 0.0
     ├─ [1,0] = 0.0
     └─ [1,1] = 1.0
   ```

3. **Automatic Type Recognition**: Works with all Matrix template instantiations
   - Different dimensions (2x2, 3x3, 4x4, etc.)
   - Different scalar types (float, double, int, complex numbers)

## Usage

### Method 1: Automatic Loading (Recommended)

The `.lldbinit` file is automatically loaded when LLDB starts in the project directory:

```bash
cd /workspaces/math-plus-plus
lldb build/tests/math-tests
```

You should see: `LLDB initialized for math++ debugging`

### Method 2: Manual Import

In an LLDB session, manually import the formatter:

```bash
(lldb) command script import lldb_formatters.py
```

### Method 3: VS Code Debugging

Use the provided VS Code launch configurations:

1. Open the Run and Debug panel (Ctrl+Shift+D)
2. Select "LLDB: Debug Tests" from the dropdown
3. Press F5 to start debugging

The formatters will be automatically loaded.

## Testing the Formatter

1. **Build the project with debug symbols**:
   ```bash
   cd build
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   cmake --build .
   ```

2. **Start LLDB**:
   ```bash
   lldb tests/math-tests
   ```

3. **Set a breakpoint** where Matrix objects are used:
   ```lldb
   (lldb) breakpoint set --file matrix_general_tests.cpp --line 50
   (lldb) run
   ```

4. **Inspect Matrix variables**:
   ```lldb
   (lldb) frame variable matrix1
   (lldb) p matrix2
   (lldb) frame variable --show-types
   ```

## Example Output

Without formatter:
```
(Matrix<3, 3, float>) matrix1 = {
  data = {
    [0] = { [0] = 1, [1] = 0, [2] = 0 }
    [1] = { [0] = 0, [1] = 1, [2] = 0 }
    [2] = { [0] = 0, [1] = 0, [2] = 1 }
  }
}
```

With formatter:
```
(Matrix<3, 3, float>) matrix1 = Matrix<3x3, float> [1, 0, 0, 0, 1, 0...]
  [0,0] = 1
  [0,1] = 0
  [0,2] = 0
  [1,0] = 0
  [1,1] = 1
  [1,2] = 0
  [2,0] = 0
  [2,1] = 0
  [2,2] = 1
```

## Customization

You can modify `lldb_formatters.py` to customize:

- **Display format**: Change how values are formatted in `matrix_summary()`
- **Element naming**: Modify element names in `get_child_at_index()`
- **Size limits**: Adjust when to show preview vs. summary in `matrix_summary()`
- **Additional types**: Add formatters for Vector or other math++ types

## Troubleshooting

### Formatter not loading

1. Check that the path in `.lldbinit` is correct:
   ```bash
   cat .lldbinit
   ```

2. Verify Python script is accessible:
   ```bash
   ls -l lldb_formatters.py
   ```

3. Manually test import:
   ```lldb
   (lldb) command script import lldb_formatters.py
   ```

### Type not recognized

If Matrix types don't show formatted:

1. Check type name matches the regex pattern in the formatter
2. Verify the Matrix type is instantiated (not just forward declared)
3. Use `type lookup Matrix` to see how LLDB sees the type

### Permission issues

If `.lldbinit` is not loading automatically:

```bash
# Allow LLDB to load local .lldbinit files
echo "settings set target.load-cwd-lldbinit true" >> ~/.lldbinit
```

### Python/SWIG errors on LLDB startup

You may see errors like:
```
NameError: name 'run_one_line' is not defined
ModuleNotFoundError: No module named 'lldb.embedded_interpreter'
```

**These are harmless** - they come from LLDB's own initialization scripts (not our formatter) and are a known issue with LLDB 14.x in certain environments. The formatters will still work correctly. You can verify by running:

```lldb
(lldb) type summary list Matrix
(lldb) type synthetic list Matrix
```

Both should show the registered formatters.

## Additional Resources

- [LLDB Python API Documentation](https://lldb.llvm.org/use/python-reference.html)
- [LLDB Type Summaries](https://lldb.llvm.org/use/variable.html)
- [LLDB Synthetic Children](https://lldb.llvm.org/use/variable.html#synthetic-children)

## Contributing

To extend the formatters for other math++ types (Vector, Curve, etc.):

1. Add new provider classes to `lldb_formatters.py`
2. Register them in `__lldb_init_module()`
3. Update this documentation with examples
