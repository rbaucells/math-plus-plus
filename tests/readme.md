# GoogleTest (GTEST) Test Suite
Extensive testing of all functions and operators at both runtime and compile time.

***

# General Conventions
 - Tests must test interface while minimizing testing of internal data structures.
 - Test files should end in .tests.cpp.
 - Google Test Suites should be separated into pragma regions.
 - Names should be the functionality being tested.
 - Google Test names should follow: 'given_\<input_or_condition\>\_should\_\<expected_result\>'
 - There should be one test file for each header file in src of the same name.
 - Tests for things that fail or may return false must have multiple tests for false/failure.
     - For example, a set of vectors can be non-orthonormal because they aren't all normalized
       or because they aren't all orthogonal, you must test this
     - When doing these multiple tests, suffix the test name with a 1, 2, 3, etc.
         - For example, 'given_set_of_non_orthogonal_vectors_return_false_1' and 'given_set_of_non_orthogonal_vectors_return_false_2'

## Run-Time Tests
 - Use 'arrange', 'act', and 'assert' comments only. 'cleanup' comments may also be used if using heap allocated memory.
 - Must be named "{type_name}_{function_name}", "given\_{condition/input}\_should\_(return/throw/do\_nothing)".
 - All comparisons must be done through the 'compare' function
   - Floating point types must use precisions instead of epsilon (e.g. 0.001f)
 - For vectors, name variables either 'v' or 'a', 'b', 'c', etc. 
 - For matrices, name variables either 'm' or 'a', 'b', 'c', etc.
    ``` c++
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    constexpr float expected = 3.74166f;
    // act
    const float euclidianNorm = euclidianNorm(a);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), euclidianNorm, expected))
    ```

# Compile-Time Tests:
- Should use static_asserts.
- Messages should follow: ''\<param passed to function/functionality\>' should/shouldn't be \<functionality being tested\>'.
    ``` c++
    static_assert(dense_vector_view<DenseVectorView<float>>, "'DenseVectorView<float>' should be dense_vector_view");
    ```