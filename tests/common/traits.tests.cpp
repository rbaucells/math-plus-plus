#include "gtest/gtest.h"
#include "mathpp/implementation/common/traits.h"

TEST(is_complex, given_int_should_return_false) {
    static_assert(is_complex<int>::value == false);
}

TEST(is_complex, given_float_should_return_false) {
    static_assert(is_complex<float>::value == false);
}

TEST(is_complex, given_complex_double_should_return_true) {
    static_assert(is_complex<std::complex<double>>::value == true);
}

TEST(is_complex, given_complex_long_should_return_true) {
    static_assert(is_complex<std::complex<long>>::value == true);
}

TEST(is_complex_v, given_float_should_return_false) {
    static_assert(is_complex_v<float> == false);
}

TEST(is_complex_v, given_complex_long_should_return_true) {
    static_assert(is_complex_v<std::complex<long>> == true);
}

TEST(complex, given_float_should_return_false) {
    static_assert(complex<float> == false);
}

TEST(complex, given_complex_long_should_return_true) {
    static_assert(complex<std::complex<long>> == true);
}

TEST(is_real, given_int_should_return_true) {
    static_assert(is_real<int>::value == true);
}

TEST(is_real, given_float_should_return_true) {
    static_assert(is_real<float>::value == true);
}

TEST(is_real, given_complex_double_should_return_false) {
    static_assert(is_real<std::complex<double>>::value == false);
}

TEST(is_real, given_complex_long_should_return_false) {
    static_assert(is_real<std::complex<long>>::value == false);
}

TEST(is_real_v, given_float_should_return_true) {
    static_assert(is_real_v<float> == true);
}

TEST(is_real_v, given_complex_long_should_return_false) {
    static_assert(is_real_v<std::complex<long>> == false);
}

TEST(real, given_float_should_return_true) {
    static_assert(real<float> == true);
}

TEST(real, given_complex_long_should_return_false) {
    static_assert(real<std::complex<long>> == false);
}

TEST(is_scalar, given_int_should_return_true) {
    static_assert(is_scalar<int>::value == true);
}

TEST(is_scalar, given_float_should_return_true) {
    static_assert(is_scalar<float>::value == true);
}

TEST(is_scalar, given_complex_double_should_return_true) {
    static_assert(is_scalar<std::complex<double>>::value == true);
}

TEST(is_scalar, given_complex_long_should_return_true) {
    static_assert(is_scalar<std::complex<long>>::value == true);
}

TEST(is_scalar_v, given_float_should_return_true) {
    static_assert(is_scalar_v<float> == true);
}

TEST(is_scalar_v, given_complex_long_should_return_true) {
    static_assert(is_scalar_v<std::complex<long>> == true);
}

TEST(scalar, given_float_should_return_true) {
    static_assert(scalar<float> == true);
}

TEST(scalar, given_complex_long_should_return_true) {
    static_assert(scalar<std::complex<long>> == true);
}

TEST(underlying_type, given_int_should_return_int) {
    static_assert(std::is_same_v<underlying_type<int>::ValueType, int>);
}

TEST(underlying_type, given_long_double_should_return_long_double) {
    static_assert(std::is_same_v<underlying_type<long double>::ValueType, long double>);
}

TEST(underlying_type, given_complex_double_should_return_int) {
    static_assert(std::is_same_v<underlying_type<std::complex<double>>::ValueType, double>);
}

TEST(underlying_type_t, given_int_should_return_int) {
    static_assert(std::is_same_v<underlying_type_t<int>, int>);
}

TEST(underlying_type_t, given_complex_double_should_return_int) {
    static_assert(std::is_same_v<underlying_type_t<std::complex<double>>, double>);
}

TEST(has_common_type, given_int_float_and_double_should_return_true) {
    static_assert(has_common_type<int, float, double> == true);
}

TEST(has_common_type, given_int_and_complex_int_and_floatshould_return_true) {
    static_assert(has_common_type<int, float, std::complex<int>> == true);
}
