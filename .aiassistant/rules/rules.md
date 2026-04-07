---
apply: always
---

# Code Style Guidelines

## Naming Conventions
- **Classes/Structs**: PascalCase
- **Namespaces**: PascalCase
- **Concepts**: snake_case
- **Usings/typedefs**: PascalCase
- **Compile-time const variables**: ALL_CAPS
- **Template parameters**: ALL_CAPS
- **Macros**: ALL_CAPS
- **Local variables**: camelCase
- **Global variables**: camelCase
- **Member functions**: camelCase
- **Free functions**: snake_case
- **Loop variables**: Single letter (i, j, k, c, r, etc.)
- **Private member variables**: Suffix with underscore (e.g., `value_`)
- **File names**: Short and snake_case
- **Enums**: PascalCase with snake_case enumerators

## Code Structure
- **Formatting**: Use clang-format (LLVM style, 4-space indentation, column limit: 0)
- **One action per line**: Don't increment a pointer, dereference it, and call a method in one line
- **Be explicit**: Write `MyClass<T>` instead of `MyClass`; avoid `auto` unless absolutely needed (e.g., std::apply on tuples)
- **Delete unused constructors**: Even if implicitly deleted
- **Follow mathematical definitions closely**: Provide workarounds/shortcuts as optional parameters (e.g., allowing Cholesky on PSD matrices)

## Code Patterns
- **Use structs** for data types with primarily public members
- **Use classes** for types with private members
- **Avoid overusing** `using` and `typedef` statements
- **Always use explicit template parameters**: Don't rely on deduction in class templates

# Function Comments

All functions must include comprehensive documentation with these required sections:

## Required Sections
1. **@brief**: One-liner description of what the function does
2. **@tparam**: For each template parameter
3. **@param**: For each function parameter
4. **@return** or **@returns**: If the function returns a value
5. **@throws**: If the function may throw exceptions

## Additional Documentation
When appropriate, include:
- **Memory allocation**: State how much memory is allocated in bytes
- **Complexity**: Time and space complexity in Big O notation
- **Reference/Link**: For complex algorithms, reference a paper or article if told to do so
- **Use cases**: Show how and when to use for common scenarios (e.g., solving Ax = b)
- **@note**: Any important caveats or behavior details

## Comment Format Example
```cpp
/**
 * @brief Compares arguments up to the specified precision.
 *
 * @tparam T Scalar type of 'a'.
 * @tparam U Scalar type of 'b'.
 * @tparam ARGS Scalar types of 'args'.
 * @param precision How precise the comparison should be (inclusive).
 * @param a First scalar argument.
 * @param b Second scalar argument.
 * @param args Remaining scalar arguments.
 *
 * @return Whether all arguments are equal up to the specified precision.
 * @note Inclusive comparison: 1, 0.9, and 1.1 are all equal up to precision 0.1
 */
```

## Inline Comments
- Comment only code that needs clarification
- Don't over-comment obvious code
- Use clear, concise language

# Test Writing Guidelines

## Compile-Time Tests
- Use `static_assert` for compile-time checks
- Format assertions as: `<functionality being tested> is wrong, '<param passed>' should/shouldn't be <functionality>`
- Example: `static_assert(dense_vector_view<DenseVectorView<float>>, "dense_vector_view is wrong, 'DenseVectorView<float>' should be dense_vector_view");`

## Runtime Tests
- Use 'arrange/act/assert' comments ONLY
- Optional: Add 'cleanup' comments for heap-allocated memory

### Test Coverage
- Test with **at least** `float` and `std::complex<float>` unless not applicable
- Assertions must use comparison functions:
  - **Equal**: `compare(Precision<T>, value1, value2)`
- **Precision**: Always use `0.001` unless not applicable (e.g., integer tests)

### Variable Naming in Tests
- **Vectors**: Use `v` or `a`, `b`, `c`, etc.
- **Matrices**: Use `m` or `a`, `b`, `c`, etc.

### Test Structure
- **Test files**: End in `.tests.cpp`
- **One test file per header**: `src/myfeature.h` → `tests/myfeature.tests.cpp`
- **Use pragma regions**: Organize tests by functionality with `#pragma region`/`#pragma endregion`
- **Explicit types**: Always write `DenseVector<float>` instead of relying on default template params.

### Test Naming
- Format: `given_<input_or_condition>_should_<expected_result>`
- Example: `given_dense_matrix_should_return_true`
- For multiple tests with similar logic: Append `_1`, `_2`, etc. to distinguish
- Example: `given_set_of_non_orthogonal_vectors_return_false_1` (orthogonality), `_2` (normalization)

### Test Quality
- Prefer **mathematical condition coverage** over code coverage (but aim for 100% code coverage)
- Test **internal data structures** when possible to minimize dependencies
- When testing functions that can fail: Create multiple test cases for each failure reason
- Example: If a function can fail because of missing orthogonality or normalization, test both cases separately

### Example Test Pattern
```cpp
#pragma region euclidian_norm
TEST(euclidian_norm, given_float_vector_should_calculate_correct_norm) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    constexpr float expected = 3.74166f;
    // act
    const float euclidianNorm = euclidianNorm(a);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), euclidianNorm, expected));
}
#pragma endregion
```

