#include "gtest/gtest.h"

#include "mathpp/implementation/common/rotations.h"
#include "mathpp/implementation/common/compare.h"

TEST(radians_to_degrees, given_real_radians_should_return_real_degrees) {
    // arrange
    constexpr float expected = 45.f;
    constexpr float radians = std::numbers::pi / 4;
    // act
    const float degrees = radians_to_degrees(radians);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), degrees, expected));
}

TEST(radians_to_degrees, given_complex_radians_should_return_complex_degrees) {
    // arrange
    constexpr std::complex<float> expected = {45.f, 90.f};
    constexpr std::complex<float> radians = std::complex<float>(std::numbers::pi / 4, std::numbers::pi / 2);
    // act
    const std::complex<float> degrees = radians_to_degrees(radians);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), degrees, expected));
}

TEST(degrees_to_radians, given_real_degrees_should_return_real_radians) {
    // arrange
    constexpr float expected = std::numbers::pi / 4;
    constexpr float degrees = 45.f;
    // act
    const float radians = degrees_to_radians(degrees);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), radians, expected));
}

TEST(degrees_to_radians, given_complex_degrees_should_return_complex_radians) {
    // arrange
    constexpr std::complex<float> expected = std::complex<float>(std::numbers::pi / 4, std::numbers::pi / 2);
    constexpr std::complex<float> degrees = {45.f, 90.f};
    // act
    const std::complex<float> radians = degrees_to_radians(degrees);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), radians, expected));
}

TEST(compare, given_real_radians_should_return_real_degrees) {
    // arrange
    constexpr float expected = 45.f;
    constexpr float radians = std::numbers::pi / 4;
    // act
    const float degrees = convert(RotationType::radians, RotationType::degrees, radians);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), degrees, expected));
}

TEST(compare, given_real_radians_should_return_real_radians) {
    // arrange
    constexpr float expected = std::numbers::pi / 4;
    // act
    const float radians = convert(RotationType::radians, RotationType::radians, expected);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), radians, expected));
}

TEST(compare, given_complex_radians_should_return_complex_degrees) {
    // arrange
    constexpr std::complex<float> expected = {45.f, 90.f};
    constexpr std::complex<float> radians = std::complex<float>(std::numbers::pi / 4, std::numbers::pi / 2);
    // act
    const std::complex<float> degrees = convert(RotationType::radians, RotationType::degrees, radians);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), degrees, expected));
}

TEST(compare, given_real_degrees_should_return_real_radians) {
    // arrange
    constexpr float expected = std::numbers::pi / 4;
    constexpr float degrees = 45.f;
    // act
    const float radians = convert(RotationType::degrees, RotationType::radians, degrees);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), radians, expected));
}

TEST(compare, given_real_degrees_should_return_real_degrees) {
    // arrange
    constexpr float expected = 90;
    // act
    const float radians = convert(RotationType::degrees, RotationType::degrees, expected);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), radians, expected));
}

TEST(compare, given_complex_degrees_should_return_complex_radians) {
    // arrange
    constexpr std::complex<float> expected = std::complex<float>(std::numbers::pi / 4, std::numbers::pi / 2);
    constexpr std::complex<float> degrees = {45.f, 90.f};
    // act
    const std::complex<float> radians = convert(RotationType::degrees, RotationType::radians, degrees);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), radians, expected));
}
