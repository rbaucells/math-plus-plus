# Python Bindings Test Suite
Tests for the pybind11 Python bindings layer.

***

# General Conventions
 - Tests must test the bindings interface, not the algorithms themselves.
 - 1 or 2 test cases per function is usually enough because correctness of the algorithm is covered by the C++ tests.
 - Use `__init__.py` in every directory so that `from ... import ...` works correctly.
 - Test files should be named `test_<module>.py`.
 - Use pytest style tests (functions prefixed with `test_`).
 - Tests are named simply on the function being done and seperate test cases are not in seperate functions, just in arrange/act/assert blocks one after another.

## Arrange / Act / Assert
Follow a minimal arrange/act/assert pattern:
 ```python
 # arrange
 a = mathpp.DenseMatrix([[1, 2], [3, 4]])
 # act
 result = a.trace()
 # assert
 assert result == 10
 ```

## Precision / Floating Point
 - All floating-point comparisons must use `Precision` (or the default epsilon) via the `compare` helper rather than raw `==`.
 - Prefer `mathpp.Precision(0.001)` when tighter tolerance is needed.

## Simple Classes
 - Simple test classes like `SimpleDenseMatrixLike` are in their own files next to the tests in the same directories (e.g. `tests/py/matrix/dense/simple_dense_matrix_like.py`).
