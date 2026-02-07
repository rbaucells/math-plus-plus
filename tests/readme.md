# Run-Time Tests.
- Use 'arrange', 'act', and 'assert' comments only.
- Must at least test with 'float' and 'std::complex<float>' unless not applicable (e.g. unitary matrix only applies to complex).
- Assert something is equal to another through the 'compare' function.
- Assert something is greater than another through the 'greater' function.
- Assert something is less than another through the 'lesser' function.
- All precisions must be '0.001' unless not applicable (e.g. ints)
- For vectors, name variables either 'v' or 'a', 'b', 'c', etc.
- For matrices, name variables either 'm' or 'a', 'b', 'c', etc.

``` c++
// arrange
const DenseVector<float> a = {1, 2, 3};
constexpr float expected = 3.74166f;
// act
const float euclidianNorm = euclidianNorm(a);
// assert
ASSERT_TRUE(compare<float, float>(euclidianNorm, expected, 0.001f))
```

# Compile-Time Tests:
  - Should use static_asserts.
  - Messages should follow: '\<functionality being tested\> is wrong, '\<param passed to function/functionality\>' should/shouldn't be \<functionality being tested\>'.
``` c++
static_assert(dense_vector_view<DenseVectorView<float>>, "dense_vector_view is wrong, 'DenseVectorView<float>' should be dense_vector_view");
```

# General Conventions:
- Be explicit, if 'DenseVector' is by default templated on 'float', explicitly put 'DenseVector<float>'.
- Google Test Suites should be separated into pragma regions.
  - Names should be the functionality being tested.
- Google Test names should follow: 'given_\<input_or_condition\>\_should\_\<expected_result\>'
- Test files should end in .tests.cpp.
- There should be one test file for each header file in src of the same name.
- Tests for things that fail or may return false must have multiple tests for false/failure.
  - For example, a set of vectors can be non-orthonormal because they aren't all normalized
    or because they aren't all orthogonal, you must test this
  - When doing these multiple tests, suffix the test name with a 1, 2, 3, etc.
    - For example, 'given_set_of_non_orthogonal_vectors_return_false_1' and 'given_set_of_non_orthogonal_vectors_return_false_2'
- Prefer mathematical condition coverage over code coverage (but still aim for 100% code coverage)