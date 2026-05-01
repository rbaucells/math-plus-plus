#include "gtest/gtest.h"

#include "mathpp/core.h"

#pragma region is_complex
TEST(is_complex, given_complex_float_then_should_return_true) {
    static_assert(complex<std::complex<float>>, "is_complex_v is wrong, 'std::complex<float>' should be complex");
}

TEST(is_complex, given_float_then_should_return_false) {
    static_assert(!complex<float>, "is_complex_v is wrong, 'float' should not be complex");
}

TEST(is_complex, given_string_then_should_return_false) {
    static_assert(!complex<std::string>, "is_complex_v is wrong, 'std::string' should not be complex");
}
#pragma endregion
#pragma region is_real
TEST(is_real, give_float_then_should_return_true) {
    static_assert(real<float>, "real is wrong, 'float' should be real");
}

TEST(is_real, give_complex_float_then_should_return_false) {
    static_assert(!real<std::complex<float>>, "real is wrong, 'std::complex<float>' should not be real");
}

TEST(is_real, give_string_float_then_should_return_false) {
    static_assert(!real<std::string>, "real is wrong, 'std::string' should not be real");
}
#pragma endregion
#pragma region is_scalar
TEST(is_scalar, given_float_should_return_true) {
    static_assert(scalar<float>, "scalar is wrong, 'float' should be scalar");
}

TEST(is_scalar, given_complex_float_should_return_true) {
    static_assert(scalar<std::complex<float>>, "scalar is wrong, 'std::complex<float>' should be scalar");
}

TEST(is_scalar, given_string_should_return_false) {
    static_assert(!scalar<std::string>, "scalar is wrong, 'std::string' should not be scalar");
}
#pragma endregion
#pragma region underlying_type
TEST(underlying_type, given_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<float>, float>, "underlying_type is wrong, underlying type of 'float' should be 'float'");
}

TEST(underlying_type, given_complex_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<std::complex<float>>, float>, "underlying_type is wrong, underlying type of 'std::complex<float>' should be 'float'");
}
#pragma endregion
#pragma region has_common_type
TEST(has_common_type, given_float_and_float_should_return_true) {
    static_assert(has_common_type<float, float>, "has_common_type is wrong, 'float' and 'float' should have common type");
}

TEST(has_common_type, given_float_and_int_should_return_true) {
    static_assert(has_common_type<float, int>, "has_common_type is wrong, 'float' and 'int' should have common type");
}

TEST(has_common_type, given_string_and_float_should_return_false) {
    static_assert(!has_common_type<std::string, float>, "has_common_type is wrong, 'std::string' and 'int' should not have common type");
}
#pragma endregion
#pragma region radians_to_degrees
TEST(radians_to_degrees, given_pi_2_should_return_90) {
    ASSERT_FLOAT_EQ(radiansToDegrees<float>(std::numbers::pi / 2), 90);
}
#pragma endregion
#pragma region degrees_to_radians
TEST(degrees_to_radians, given_90_should_return_pi_2) {
    ASSERT_FLOAT_EQ(degreesToRadians<float>(90), std::numbers::pi / 2);
}
#pragma endregion
#pragma region convert
TEST(convert, given_degrees_should_return_degrees) {
    ASSERT_FLOAT_EQ(convert<float>(RotationType::degrees, RotationType::degrees, 90), 90);
}

TEST(convert, given_radians_should_return_radians) {
    ASSERT_FLOAT_EQ(convert<float>(RotationType::radians, RotationType::radians, std::numbers::pi / 2), std::numbers::pi / 2);
}

TEST(convert, given_degrees_should_return_radians) {
    ASSERT_FLOAT_EQ(convert<float>(RotationType::degrees, RotationType::radians, 90), std::numbers::pi / 2);
}

TEST(convert, given_radians_should_return_degrees) {
    ASSERT_FLOAT_EQ(convert<float>(RotationType::radians, RotationType::degrees, std::numbers::pi / 2), 90);
}
#pragma endregion
#pragma region epsilon
TEST(epsilon, given_int_should_return_1) {
    static_assert(epsilon<int>() == 0, "epsilon is wrong, epsilon of 'int' should be 0");
}

TEST(epsilon, given_float_should_return_FLT_EPSILON) {
    static_assert(epsilon<float>() == FLT_EPSILON, "epsilon is wrong, epsilon of 'float' should be FLT_EPSILON");
}

TEST(epsilon, given_complex_float_should_return_FLT_EPSILON) {
    static_assert(epsilon<std::complex<float>>() == FLT_EPSILON, "epsilon is wrong, epsilon of 'std::complex<float>' should be FLT_EPSILON");
}
#pragma endregion
#pragma region compare
TEST(compare, given_ints_should_return_true) {
    ASSERT_TRUE(compare(1, 1, 1));
}

TEST(compare, given_ints_should_return_false) {
    ASSERT_FALSE(compare(1, 2, 1));
}

TEST(compare, given_ints_and_precision_should_return_true) {
    ASSERT_TRUE(compare(Precision(1), 1, 2, 1));
}

TEST(compare, given_ints_and_precision_should_return_false) {
    ASSERT_FALSE(compare(Precision(1), 1, 2, 0));
}

TEST(compare, given_floats_should_return_true) {
    ASSERT_TRUE(compare(1.0f, 1.0f, 1.0f));
}

TEST(compare, given_floats_should_return_false) {
    ASSERT_FALSE(compare(1.0f, 1.1f, 1.0f));
}

TEST(compare, given_floats_and_precision_should_return_true) {
    // Precision(0.11f) instead of Precision(0.1f) because 1.1f is not actually 1.1
    ASSERT_TRUE(compare(Precision(0.11f), 1.0f, 1.1f, 1.0f));
}

TEST(compare, given_floats_and_precision_should_return_false) {
    ASSERT_FALSE(compare(Precision(0.1f), 1.0f, 0.9f, 1.1f));
}

TEST(compare, given_complex_floats_should_return_true) {
    ASSERT_TRUE(compare(std::complex<float>(1.0f, 2.0f), std::complex<float>(1.0f, 2.0f), std::complex<float>(1.0f, 2.0f)));
}

TEST(compare, given_complex_floats_should_return_false_1) {
    ASSERT_FALSE(compare(std::complex<float>(1.0f, 2.0f), std::complex<float>(2.0f, 2.0f), std::complex<float>(1.0f, 2.0f)));
}

TEST(compare, given_complex_floats_should_return_false_2) {
    ASSERT_FALSE(compare(std::complex<float>(1.0f, 2.0f), std::complex<float>(1.0f, 3.0f), std::complex<float>(1.0f, 2.0f)));
}

TEST(compare, given_complex_floats_and_precision_should_return_true) {
    // Precision(0.11f) instead of Precision(0.1f) because 1.1f is not actually 1.1
    ASSERT_TRUE(compare(Precision(0.11f), std::complex<float>(1.0f, 2.0f), std::complex<float>(1.1f, 2.1f), std::complex<float>(1.0f, 2.0f)));
}

TEST(compare, given_complex_floats_and_precision_should_return_false_1) {
    ASSERT_FALSE(compare(Precision(0.1f), std::complex<float>(1.0f, 2.0f), std::complex<float>(1.1f, 2.0f), std::complex<float>(0.9f, 2.0f)));
}

TEST(compare, given_complex_floats_and_precision_should_return_false_2) {
    ASSERT_FALSE(compare(Precision(0.1f), std::complex<float>(1.0f, 2.0f), std::complex<float>(1.0f, 2.1f), std::complex<float>(1.0f, 1.9f)));
}

TEST(compare, given_int_and_float_should_return_true) {
    ASSERT_TRUE(compare(1, 1.0f));
}

TEST(compare, given_int_and_float_should_return_false) {
    ASSERT_FALSE(compare(1, 1.1f));
}

TEST(compare, given_int_and_float_and_precision_should_return_true) {
    // Precision(0.11f) instead of Precision(0.1f) because 1.1f is not actually 1.1
    ASSERT_TRUE(compare(Precision(0.11f), 1, 1.1f));
}

TEST(compare, given_int_and_float_and_precision_should_return_false) {
    ASSERT_FALSE(compare(Precision(0.1f), 1, 1.2f));
}

TEST(compare, given_float_and_complex_float_should_return_true) {
    ASSERT_TRUE(compare(1.0f, std::complex<float>(1.0f, 0.0f)));
}

TEST(compare, given_float_and_complex_float_should_return_false_1) {
    ASSERT_FALSE(compare(1.0f, std::complex<float>(1.0f, 0.1f)));
}

TEST(compare, given_float_and_complex_float_should_return_false_2) {
    ASSERT_FALSE(compare(1.0f, std::complex<float>(1.1f, 0.0f)));
}

TEST(compare, given_float_and_complex_float_and_precision_should_return_true_1) {
    // Precision(0.11f) instead of Precision(0.1f) because 1.1f is not actually 1.1
    ASSERT_TRUE(compare(Precision(0.11f), 1.0f, std::complex<float>(1.1f, 0.0f)));
}

TEST(compare, given_float_and_complex_float_and_precision_should_return_true_2) {
    ASSERT_TRUE(compare(Precision(0.1f), 1.0f, std::complex<float>(1.0f, 0.1f)));
}

TEST(compare, given_float_and_complex_float_and_precision_should_return_false_1) {
    ASSERT_FALSE(compare(Precision(0.1f), 1.0f, std::complex<float>(1.0f, 0.2f)));
}

TEST(compare, given_float_and_complex_float_and_precision_should_return_false_2) {
    ASSERT_FALSE(compare(Precision(0.1f), 1.0f, std::complex<float>(1.2f, 0.0f)));
}

TEST(compare, given_int_and_complex_float_should_return_true) {
    ASSERT_TRUE(compare(1, std::complex<float>(1.0f, 0.0f)));
}

TEST(compare, given_int_and_complex_float_should_return_false_1) {
    ASSERT_FALSE(compare(1, std::complex<float>(1.0f, 0.1f)));
}

TEST(compare, given_int_and_complex_float_should_return_false_2) {
    ASSERT_FALSE(compare(1, std::complex<float>(1.1f, 0.0f)));
}

TEST(compare, given_int_and_complex_float_and_precision_should_return_true_1) {
    // Precision(0.11f) instead of Precision(0.1f) because 1.1f is not actually 1.1
    ASSERT_TRUE(compare(Precision(0.11f), 1, std::complex<float>(1.1f, 0.0f)));
}

TEST(compare, given_int_and_complex_float_and_precision_should_return_true_2) {
    ASSERT_TRUE(compare(Precision(0.1f), 1, std::complex<float>(1.0f, 0.1f)));
}

TEST(compare, given_int_and_complex_float_and_precision_should_return_false_1) {
    ASSERT_FALSE(compare(Precision(0.1f), 1, std::complex<float>(1.0f, 0.2f)));
}

TEST(compare, given_int_and_complex_float_and_precision_should_return_false_2) {
    ASSERT_FALSE(compare(Precision(0.1f), 1, std::complex<float>(1.2f, 0.0f)));
}

TEST(compare, given_int_float_and_complex_float_shoud_return_true_1) {
    ASSERT_TRUE(compare(1, 1.0f, std::complex<float>(1.0f, 0.0f)));
}
TEST(compare, given_int_float_and_complex_float_shoud_return_false_1) {
    ASSERT_FALSE(compare(1, 1.0f, std::complex<float>(1.1f, 0.0f)));
}
TEST(compare, given_int_float_and_complex_float_shoud_return_false_2) {
    ASSERT_FALSE(compare(1, 1.0f, std::complex<float>(1.0f, 0.1f)));
}
TEST(compare, given_int_float_and_complex_float_precision_should_return_true_1) {
    ASSERT_TRUE(compare(Precision(0.11f), 1, 1.0f, std::complex<float>(1.1f, 0.0f)));
}
TEST(compare, given_int_float_and_complex_float_precision_should_return_true_2) {
    ASSERT_TRUE(compare(Precision(0.1f), 1, 1.0f, std::complex<float>(1.0f,  0.1f)));
}
TEST(compare, given_int_float_and_complex_float_precision_should_return_false_1) {
    ASSERT_FALSE(compare(Precision(0.1f), 1, 1.0f, std::complex<float>(1.0f, 0.2f)));
}
TEST(compare, given_int_float_and_complex_float_precision_should_return_false_2) {
    ASSERT_FALSE(compare(Precision(0.1f), 1, 1.0f, std::complex<float>(0.8f, 0.0f)));
}
#pragma endregion
