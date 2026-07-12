#include "gtest/gtest.h"
#include <limits>

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/common/precision.h"

TEST(epsilon, given_int_should_return_epsilon) {
    static_assert(epsilon<int>() == std::numeric_limits<int>::epsilon());
}

TEST(epsilon, given_float_should_return_epsilon) {
    static_assert(epsilon<float>() == std::numeric_limits<float>::epsilon());
}

TEST(epsilon, given_long_double_should_return_epsilon) {
    static_assert(epsilon<long double>() == std::numeric_limits<long double>::epsilon());
}

TEST(epsilon, given_complex_short_should_return_epsilon) {
    static_assert(epsilon<std::complex<short>>() == std::numeric_limits<short>::epsilon());
}

TEST(epsilon, given_complex_double_should_return_epsilon) {
    static_assert(epsilon<std::complex<double>>() == std::numeric_limits<double>::epsilon());
}

TEST(precision, given_value_should_construct) {
    // arrange
    constexpr float value = 0.1f;
    // act
    constexpr Precision<float> precision = Precision<float>(value);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), precision.value, value));
}
