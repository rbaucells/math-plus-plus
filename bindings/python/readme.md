# Python Bindings
***

# General Conventions
 - Each subdirectory exposes its own `main.h` + `main.cpp`.
 - main.cpp forward declares functions in the same directory, includes the main.h and calls the function through there of any subdirectories.
 - Global named operator functions must be in `common/operators` because it needs to take in the entire py::object by param and it cant differentiate overloads by the internal type checks. So it calls the correct c++ function depending on the args.
 - Use standard library utilities such as `std::variant`, `std::views::iota`, and `std::views::transform` to do type erasure and wrap py sequences and arrays in a std::ranges::sized_range or std::ranges::random_access_range.
 - Use custom py type with custom casters like AnyNumber instead of raw Python types in bindings signatures.
 - Every `m.def` must include argument names via `py::arg("name")`.
 - Every exported function must have a single-line comment above it stating what it does.
 - Includes must be like in include/implementation, include all headers even if a header includes the one you need. Be explicit with includes.

## Typing & Wrappers
 - Use types like DenseMatrixLikePyWrapper to wrap a DenseMatrixLike py object in a c++ class that passes the dense_matrix_like concept.
 - Dispatch on dtype and etype using the existing `dispatch_dt` / `get_sequence_info` / `get_array_info` helpers.
