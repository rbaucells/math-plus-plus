# Math++ - Linear Algebra Math Library
C++ templated linear algebra math library that aims to be simple and performant.
***

## Details
 - C++23.
 - Built using CMake.
 - Header-only math library.
 - GTEST testing suite.

## Features
 - Easy to use included types with potential for modular new types.
   - DenseMatrix(View)
   - DenseVector(View)
   - (COO/DOK)SparseVector(View)
   - (CSC/CSR)SparseVector(View)
 - Concepts instead of virtual inheritance for performance and ease of use.
 - Custom lldb debugger for all types.
 - Telemetry.
 - Python bindings (wip)
 - GitHub actions for unit testing and pr code coverage.
 - Operator overloading.

## Roadmap
1. Refactor old algorithms into new dense matrix/vector structure.
2. Implement sparse versions of old algorithms in new sparse matrix/vector structures.
3. Python bindings.
4. Command line based interface for using math library, similar to Math Notepad (https://mathnotepad.com).
5. Implement every decomposition on (https://en.wikipedia.org/wiki/Matrix_decomposition).
6. Implement every eigen algorithm on (https://en.wikipedia.org/wiki/Eigenvalue_algorithm).

## Contributing
 - See src/readme.md

## Unit Tests
 - See tests/readme.md