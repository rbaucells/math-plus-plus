#include <gtest/gtest.h>
#include "math++/math.h"

// epsilon tests
static_assert(epsilon<float>() == FLT_EPSILON, "Epsilon function has incorrect epsilon for float");
static_assert(epsilon<double>() == DBL_EPSILON, "Epsilon function has incorrect epsilon for double");
static_assert(epsilon<long double>() == LDBL_EPSILON, "Epsilon function has incorrect epsilon for long double");

static_assert(epsilon<int>() == 1, "Epsilon function has incorrect epsilon for int");
static_assert(epsilon<long>() == 1, "Epsilon function has incorrect epsilon for long");
static_assert(epsilon<long long>() == 1, "Epsilon function has incorrect epsilon for long long");
static_assert(epsilon<short>() == 1, "Epsilon function has incorrect epsilon for short");

static_assert(epsilon<unsigned int>() == 1, "Epsilon function has incorrect epsilon for unsigned int");
static_assert(epsilon<unsigned long>() == 1, "Epsilon function has incorrect epsilon for unsigned long");
static_assert(epsilon<unsigned long long>() == 1, "Epsilon function has incorrect epsilon for unsigned long long");
static_assert(epsilon<unsigned short>() == 1, "Epsilon function has incorrect epsilon for unsigned short");

static_assert(epsilon<std::complex<float>>() == FLT_EPSILON, "Epsilon function has incorrect epsilon for complex<float>");
static_assert(epsilon<std::complex<double>>() == DBL_EPSILON, "Epsilon function has incorrect epsilon for complex<double>");
static_assert(epsilon<std::complex<long double>>() == LDBL_EPSILON, "Epsilon function has incorrect epsilon for complex<long double>");

static_assert(epsilon<std::complex<int>>() == 1, "Epsilon function has incorrect epsilon for complex<int>");
static_assert(epsilon<std::complex<long>>() == 1, "Epsilon function has incorrect epsilon for complex<long>");
static_assert(epsilon<std::complex<long long>>() == 1, "Epsilon function has incorrect epsilon for complex<long long>");
static_assert(epsilon<std::complex<short>>() == 1, "Epsilon function has incorrect epsilon for complex<short>");

static_assert(epsilon<std::complex<unsigned int>>() == 1, "Epsilon function has incorrect epsilon for complex<unsigned int>");
static_assert(epsilon<std::complex<unsigned long>>() == 1, "Epsilon function has incorrect epsilon for complex<unsigned long>");
static_assert(epsilon<std::complex<unsigned long long>>() == 1, "Epsilon function has incorrect epsilon for complex<unsigned long long>");
static_assert(epsilon<std::complex<unsigned short>>() == 1, "Epsilon function has incorrect epsilon for complex<unsigned short>");

// =======================================================
// real with real
// =======================================================

TEST(Helper, int_with_int) {
    // compare
    ASSERT_TRUE(compare(1, 1));
    ASSERT_FALSE(compare(1, 2));

    // lesser
    ASSERT_TRUE(lesser(1, 2));
    ASSERT_FALSE(lesser(2, 1));
    ASSERT_FALSE(lesser(1, 1));

    // greater
    ASSERT_TRUE(greater(2, 1));
    ASSERT_FALSE(greater(1, 2));
    ASSERT_FALSE(greater(1, 1));
}

TEST(Helper, float_with_float) {
    // compare
    ASSERT_TRUE(compare(1.0f, 1.0f));
    ASSERT_FALSE(compare(1.0f, 2.0f));

    // lesser
    ASSERT_TRUE(lesser(1.0f, 2.0f));
    ASSERT_FALSE(lesser(2.0f, 1.0f));
    ASSERT_FALSE(lesser(1.0f, 1.0f));

    // greater
    ASSERT_TRUE(greater(2.0f, 1.0f));
    ASSERT_FALSE(greater(1.0f, 2.0f));
    ASSERT_FALSE(greater(1.0f, 1.0f));
}

TEST(Helper, double_with_double) {
    // compare
    ASSERT_TRUE(compare(1.0, 1.0));
    ASSERT_FALSE(compare(1.0, 2.0));

    // lesser
    ASSERT_TRUE(lesser(1.0, 2.0));
    ASSERT_FALSE(lesser(2.0, 1.0));
    ASSERT_FALSE(lesser(1.0, 1.0));

    // greater
    ASSERT_TRUE(greater(2.0, 1.0));
    ASSERT_FALSE(greater(1.0, 2.0));
    ASSERT_FALSE(greater(1.0, 1.0));
}

TEST(Helper, long_double_with_long_double) {
    // compare
    ASSERT_TRUE(compare(1.0L, 1.0L));
    ASSERT_FALSE(compare(1.0L, 2.0L));

    // lesser
    ASSERT_TRUE(lesser(1.0L, 2.0L));
    ASSERT_FALSE(lesser(2.0L, 1.0L));
    ASSERT_FALSE(lesser(1.0L, 1.0L));

    // greater
    ASSERT_TRUE(greater(2.0L, 1.0L));
    ASSERT_FALSE(greater(1.0L, 2.0L));
    ASSERT_FALSE(greater(1.0L, 1.0L));
}

// =======================================================
// complex with complex (compare only)
// =======================================================

TEST(Helper, complex_int_with_complex_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, std::complex<int>{1,0}));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, std::complex<int>{1,0}));
}

TEST(Helper, complex_float_with_complex_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, std::complex<float>{1.0f,0.0f}));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, std::complex<float>{1.0f,0.0f}));
}

TEST(Helper, complex_double_with_complex_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, std::complex<double>{1.0,0.0}));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, std::complex<double>{1.0,0.0}));
}

TEST(Helper, complex_long_double_with_complex_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, std::complex<long double>{1.0L,0.0L}));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, std::complex<long double>{1.0L,0.0L}));
}

// =======================================================
// complex with int
// =======================================================

TEST(Helper, complex_int_with_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, 1));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, 1));

    // lesser
    ASSERT_TRUE(lesser(std::complex<int>{1,0}, 2));
    ASSERT_FALSE(lesser(std::complex<int>{2,0}, 1));
    ASSERT_FALSE(lesser(std::complex<int>{1,0}, 1));

    // greater
    ASSERT_TRUE(greater(std::complex<int>{2,0}, 1));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 2));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 1));
}

TEST(Helper, complex_float_with_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, 1));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, 1));

    // lesser
    ASSERT_TRUE(lesser(std::complex<float>{1.0f,0.0f}, 2));
    ASSERT_FALSE(lesser(std::complex<float>{2.0f,0.0f}, 1));
    ASSERT_FALSE(lesser(std::complex<float>{1.0f,0.0f}, 1));

    // greater
    ASSERT_TRUE(greater(std::complex<float>{2.0f,0.0f}, 1));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 2));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 1));
}

TEST(Helper, complex_double_with_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, 1));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, 1));

    // lesser
    ASSERT_TRUE(lesser(std::complex<double>{1.0,0.0}, 2));
    ASSERT_FALSE(lesser(std::complex<double>{2.0,0.0}, 1));
    ASSERT_FALSE(lesser(std::complex<double>{1.0,0.0}, 1));

    // greater
    ASSERT_TRUE(greater(std::complex<double>{2.0,0.0}, 1));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 2));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 1));
}

TEST(Helper, complex_long_double_with_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, 1));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, 1));

    // lesser
    ASSERT_TRUE(lesser(std::complex<long double>{1.0L,0.0L}, 2));
    ASSERT_FALSE(lesser(std::complex<long double>{2.0L,0.0L}, 1));
    ASSERT_FALSE(lesser(std::complex<long double>{1.0L,0.0L}, 1));

    // greater
    ASSERT_TRUE(greater(std::complex<long double>{2.0L,0.0L}, 1));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 2));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 1));
}

// =======================================================
// complex with float
// =======================================================

TEST(Helper, complex_int_with_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, 1.0f));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, 1.0f));

    // lesser
    ASSERT_TRUE(lesser(std::complex<int>{1,0}, 2.0f));
    ASSERT_FALSE(lesser(std::complex<int>{2,0}, 1.0f));
    ASSERT_FALSE(lesser(std::complex<int>{1,0}, 1.0f));

    // greater
    ASSERT_TRUE(greater(std::complex<int>{2,0}, 1.0f));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 2.0f));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 1.0f));
}

TEST(Helper, complex_float_with_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, 1.0f));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, 1.0f));

    // lesser
    ASSERT_TRUE(lesser(std::complex<float>{1.0f,0.0f}, 2.0f));
    ASSERT_FALSE(lesser(std::complex<float>{2.0f,0.0f}, 1.0f));
    ASSERT_FALSE(lesser(std::complex<float>{1.0f,0.0f}, 1.0f));

    // greater
    ASSERT_TRUE(greater(std::complex<float>{2.0f,0.0f}, 1.0f));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 2.0f));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 1.0f));
}

TEST(Helper, complex_double_with_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, 1.0f));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, 1.0f));

    // lesser
    ASSERT_TRUE(lesser(std::complex<double>{1.0,0.0}, 2.0f));
    ASSERT_FALSE(lesser(std::complex<double>{2.0,0.0}, 1.0f));
    ASSERT_FALSE(lesser(std::complex<double>{1.0,0.0}, 1.0f));

    // greater
    ASSERT_TRUE(greater(std::complex<double>{2.0,0.0}, 1.0f));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 2.0f));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 1.0f));
}

TEST(Helper, complex_long_double_with_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, 1.0f));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, 1.0f));

    // lesser
    ASSERT_TRUE(lesser(std::complex<long double>{1.0L,0.0L}, 2.0f));
    ASSERT_FALSE(lesser(std::complex<long double>{2.0L,0.0L}, 1.0f));
    ASSERT_FALSE(lesser(std::complex<long double>{1.0L,0.0L}, 1.0f));

    // greater
    ASSERT_TRUE(greater(std::complex<long double>{2.0L,0.0L}, 1.0f));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 2.0f));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 1.0f));
}

// =======================================================
// complex with double
// =======================================================

TEST(Helper, complex_int_with_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, 1.0));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, 1.0));

    // lesser
    ASSERT_TRUE(lesser(std::complex<int>{1,0}, 2.0));
    ASSERT_FALSE(lesser(std::complex<int>{2,0}, 1.0));
    ASSERT_FALSE(lesser(std::complex<int>{1,0}, 1.0));

    // greater
    ASSERT_TRUE(greater(std::complex<int>{2,0}, 1.0));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 2.0));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 1.0));
}

TEST(Helper, complex_float_with_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, 1.0));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, 1.0));

    // lesser
    ASSERT_TRUE(lesser(std::complex<float>{1.0f,0.0f}, 2.0));
    ASSERT_FALSE(lesser(std::complex<float>{2.0f,0.0f}, 1.0));
    ASSERT_FALSE(lesser(std::complex<float>{1.0f,0.0f}, 1.0));

    // greater
    ASSERT_TRUE(greater(std::complex<float>{2.0f,0.0f}, 1.0));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 2.0));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 1.0));
}

TEST(Helper, complex_double_with_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, 1.0));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, 1.0));

    // lesser
    ASSERT_TRUE(lesser(std::complex<double>{1.0,0.0}, 2.0));
    ASSERT_FALSE(lesser(std::complex<double>{2.0,0.0}, 1.0));
    ASSERT_FALSE(lesser(std::complex<double>{1.0,0.0}, 1.0));

    // greater
    ASSERT_TRUE(greater(std::complex<double>{2.0,0.0}, 1.0));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 2.0));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 1.0));
}

TEST(Helper, complex_long_double_with_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, 1.0));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, 1.0));

    // lesser
    ASSERT_TRUE(lesser(std::complex<long double>{1.0L,0.0L}, 2.0));
    ASSERT_FALSE(lesser(std::complex<long double>{2.0L,0.0L}, 1.0));
    ASSERT_FALSE(lesser(std::complex<long double>{1.0L,0.0L}, 1.0));

    // greater
    ASSERT_TRUE(greater(std::complex<long double>{2.0L,0.0L}, 1.0));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 2.0));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 1.0));
}

// =======================================================
// complex with long double
// =======================================================

TEST(Helper, complex_int_with_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, 1.0L));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, 1.0L));

    // lesser
    ASSERT_TRUE(lesser(std::complex<int>{1,0}, 2.0L));
    ASSERT_FALSE(lesser(std::complex<int>{2,0}, 1.0L));
    ASSERT_FALSE(lesser(std::complex<int>{1,0}, 1.0L));

    // greater
    ASSERT_TRUE(greater(std::complex<int>{2,0}, 1.0L));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 2.0L));
    ASSERT_FALSE(greater(std::complex<int>{1,0}, 1.0L));
}

TEST(Helper, complex_float_with_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, 1.0L));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, 1.0L));

    // lesser
    ASSERT_TRUE(lesser(std::complex<float>{1.0f,0.0f}, 2.0L));
    ASSERT_FALSE(lesser(std::complex<float>{2.0f,0.0f}, 1.0L));
    ASSERT_FALSE(lesser(std::complex<float>{1.0f,0.0f}, 1.0L));

    // greater
    ASSERT_TRUE(greater(std::complex<float>{2.0f,0.0f}, 1.0L));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 2.0L));
    ASSERT_FALSE(greater(std::complex<float>{1.0f,0.0f}, 1.0L));
}

TEST(Helper, complex_double_with_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, 1.0L));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, 1.0L));

    // lesser
    ASSERT_TRUE(lesser(std::complex<double>{1.0,0.0}, 2.0L));
    ASSERT_FALSE(lesser(std::complex<double>{2.0,0.0}, 1.0L));
    ASSERT_FALSE(lesser(std::complex<double>{1.0,0.0}, 1.0L));

    // greater
    ASSERT_TRUE(greater(std::complex<double>{2.0,0.0}, 1.0L));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 2.0L));
    ASSERT_FALSE(greater(std::complex<double>{1.0,0.0}, 1.0L));
}

TEST(Helper, complex_long_double_with_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, 1.0L));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, 1.0L));

    // lesser
    ASSERT_TRUE(lesser(std::complex<long double>{1.0L,0.0L}, 2.0L));
    ASSERT_FALSE(lesser(std::complex<long double>{2.0L,0.0L}, 1.0L));
    ASSERT_FALSE(lesser(std::complex<long double>{1.0L,0.0L}, 1.0L));

    // greater
    ASSERT_TRUE(greater(std::complex<long double>{2.0L,0.0L}, 1.0L));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 2.0L));
    ASSERT_FALSE(greater(std::complex<long double>{1.0L,0.0L}, 1.0L));
}

TEST(Helper, complex_int_with_complex_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, std::complex<float>{1.0f,0.0f}));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, std::complex<float>{1.0f,0.0f}));
}

TEST(Helper, complex_int_with_complex_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, std::complex<double>{1.0,0.0}));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, std::complex<double>{1.0,0.0}));
}

TEST(Helper, complex_int_with_complex_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<int>{1,0}, std::complex<long double>{1.0L,0.0L}));
    ASSERT_FALSE(compare(std::complex<int>{1,1}, std::complex<long double>{1.0L,0.0L}));
}

// complex<float> with *
TEST(Helper, complex_float_with_complex_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, std::complex<int>{1,0}));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, std::complex<int>{1,0}));
}

TEST(Helper, complex_float_with_complex_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, std::complex<double>{1.0,0.0}));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, std::complex<double>{1.0,0.0}));
}

TEST(Helper, complex_float_with_complex_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<float>{1.0f,0.0f}, std::complex<long double>{1.0L,0.0L}));
    ASSERT_FALSE(compare(std::complex<float>{1.0f,1.0f}, std::complex<long double>{1.0L,0.0L}));
}

// complex<double> with *
TEST(Helper, complex_double_with_complex_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, std::complex<int>{1,0}));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, std::complex<int>{1,0}));
}

TEST(Helper, complex_double_with_complex_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, std::complex<float>{1.0f,0.0f}));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, std::complex<float>{1.0f,0.0f}));
}

TEST(Helper, complex_double_with_complex_long_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<double>{1.0,0.0}, std::complex<long double>{1.0L,0.0L}));
    ASSERT_FALSE(compare(std::complex<double>{1.0,1.0}, std::complex<long double>{1.0L,0.0L}));
}

// complex<long double> with *
TEST(Helper, complex_long_double_with_complex_int) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, std::complex<int>{1,0}));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, std::complex<int>{1,0}));
}

TEST(Helper, complex_long_double_with_complex_float) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, std::complex<float>{1.0f,0.0f}));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, std::complex<float>{1.0f,0.0f}));
}

TEST(Helper, complex_long_double_with_complex_double) {
    // compare
    ASSERT_TRUE(compare(std::complex<long double>{1.0L,0.0L}, std::complex<double>{1.0,0.0}));
    ASSERT_FALSE(compare(std::complex<long double>{1.0L,1.0L}, std::complex<double>{1.0,0.0}));
}