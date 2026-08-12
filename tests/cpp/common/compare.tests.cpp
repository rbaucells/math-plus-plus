#include "gtest/gtest.h"

#include "mathpp/implementation/common/compare.h"

TEST(scalar_compare, given_int_and_double_should_return_true) {
    // act
    const bool result = compare(1, 1);
    // assert
    ASSERT_TRUE(result);
}

TEST(scalar_compare, given_int_and_double_should_return_false) {
    // act
    const bool result = compare(1, 1.1l);
    // assert
    ASSERT_FALSE(result);
}

TEST(scalar_compare, given_float_and_int_and_complex_double_should_return_true) {
    // act
    const bool result = compare(1.0f, 1, std::complex<double>(1.l, 0.l));
    // assert
    ASSERT_TRUE(result);
}

TEST(scalar_compare, given_float_and_int_and_complex_double_should_return_false_1) {
    // act
    const bool result = compare(1.1f, 1, std::complex<double>(1.l, 0.l));
    // assert
    ASSERT_FALSE(result);
}

TEST(scalar_compare, given_float_and_int_and_complex_double_should_return_false_2) {
    // act
    const bool result = compare(1.f, 2, std::complex<double>(1.l, 0.l));
    // assert
    ASSERT_FALSE(result);
}

TEST(scalar_compare, given_float_and_int_and_complex_double_should_return_false_3) {
    // act
    const bool result = compare(1.f, 1, std::complex<double>(1.l, 0.1l));
    // assert
    ASSERT_FALSE(result);
}
