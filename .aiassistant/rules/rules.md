---
apply: always
---

## General Principles

*   **Idiomatic C++23:** All generated code must be modern C++23, following established best practices for performance and readability.
*   **Consistency:** Always refer to existing code for style, patterns, and conventions before introducing new code.
*   **Explicitness:** Prioritize explicit declarations and type safety. Avoid `auto` unless absolutely necessary (e.g., lambdas, `std::apply`).
*   **Security:** Never introduce code that exposes, logs, or commits secrets, API keys, or other sensitive information.

## Code Style

Adhere strictly to the `.clang-format` file and the following conventions:

*   **Naming:**
    *   Classes/Structs, Namespaces, Usings/typedefs, Enums: `PascalCase`
    *   Concepts, Free functions, File names, Enumerators: `snake_case`
    *   Compile-time const variables, Template parameters, Macros: `ALL_CAPS`
    *   Local variables, Global variables, Member functions: `camelCase`
    *   Private member variables: `_` suffix (e.g., `myVariable_`)
    *   Loop variables: single letter (e.g., `i`, `j`, `k`)
*   **Structure:**
    *   Use `struct` for primarily public data types; `class` otherwise.
    *   Explicitly delete or define constructors/assignment operators.
    *   Avoid overusing `using` and `typedef` statements.
*   **File Organization:**
    *   Follow the existing directory structure (e.g., `src/common`, `src/matrix/common`, etc.).

## Code Documentation

Comprehensive and accurate documentation is **CRITICAL**. Every function, class, struct, and complex algorithm **MUST** be thoroughly documented.

*   **Function Comments:** Every function **MUST** include:
    *   A one-liner `@brief` section.
    *   A `@param` section for every argument.
    *   An `@returns` section if the function returns a value.
    *   A `@tparam` section for template parameters.
    *   A `@throws` section if the function may throw exceptions.
*   **Algorithm Documentation (for complex algorithms):**
    *   Provide a link to a relevant paper or article for more information.
    *   Show how and when to use the algorithm for common use cases (e.g., solving `Ax = b`).
    *   State the time complexity in Big O notation.
    *   Mention memory allocation in bytes.

## Unit Testing

All new features and bug fixes **MUST** be accompanied by comprehensive unit tests.

*   **GoogleTest (GTEST):** Use the existing GoogleTest framework.
*   **Coverage:** Test all functions and operators at both runtime and compile time.
*   **Interface Testing:** Tests should primarily focus on the public interface, minimizing reliance on internal data structures.
*   **File Naming:** Test files **MUST** end in `.tests.cpp`.
*   **Structure:**
    *   Google Test Suites should be separated into pragma regions.
    *   There should be one test file for each header file in `src` of the same name.
*   **Test Naming:**
    *   Overall suite names should reflect the functionality being tested.
    *   Individual test cases **MUST** follow: `given_<input_or_condition>_should_<expected_result>`.
    *   For multiple failure/edge cases of the same functionality, suffix with `_1`, `_2`, etc. (e.g., `given_set_of_non_orthogonal_vectors_return_false_1`).
*   **Run-Time Tests:**
    *   Use `// arrange`, `// act`, and `// assert` comments. Add `// cleanup` if heap memory is used.
    *   Variable Naming: `v` or `a, b, c` for vectors; `m` or `a, b, c` for matrices.
    *   Floating-point comparisons **MUST** use the `compare` function with explicit precisions (e.g., `0.001f`) instead of epsilon.
*   **Compile-Time Tests:**
    *   Use `static_asserts`.
    *   Messages **MUST** follow: `'<param passed to function/functionality>' should/shouldn't be <functionality being tested>'`.
