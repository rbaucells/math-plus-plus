#include "gtest/gtest.h"

#include "mathpp/implementation/matrix/common/asserts.h"

template<std::size_t ROWS, std::size_t COLUMNS, typename T>
struct sized_matrix_like {
    using ValueType = T;
    static constexpr bool isComplex = true;

    [[nodiscard]] std::size_t rows() const {
        return ROWS;
    }

    [[nodiscard]] std::size_t columns() const {
        return COLUMNS;
    }
};

TEST(assert_assert_square, given_square_should_not_throw) {
    // arrange
    constexpr sized_matrix_like<3, 3, float> m;
    // act / assert
    ASSERT_NO_THROW(assert_square(m));
}

TEST(assert_assert_square, given_wide_should_throw) {
    // arrange
    constexpr sized_matrix_like<3, 4, double> m;
    // act / assert
    ASSERT_THROW(assert_square(m), InvalidDimensionException);
}

TEST(assert_assert_square, given_tall_should_throw) {
    // arrange
    constexpr sized_matrix_like<4, 3, long double> m;
    // act / assert
    ASSERT_THROW(assert_square(m), InvalidDimensionException);
}

TEST(assert_assert_wide, given_square_throw) {
    // arrange
    constexpr sized_matrix_like<3, 3, std::complex<unsigned long>> m;
    // act / assert
    ASSERT_THROW(assert_wide(m), InvalidDimensionException);
}

TEST(assert_assert_wide, given_wide_should_not_throw) {
    // arrange
    constexpr sized_matrix_like<3, 4, std::complex<short>> m;
    // act / assert
    ASSERT_NO_THROW(assert_wide(m));
}

TEST(assert_assert_wide, given_tall_should_throw) {
    // arrange
    constexpr sized_matrix_like<4, 3, int> m;
    // act / assert
    ASSERT_THROW(assert_wide(m), InvalidDimensionException);
}

TEST(assert_assert_tall, given_square_throw) {
    // arrange
    constexpr sized_matrix_like<3, 3, long long> m;
    // act / assert
    ASSERT_THROW(assert_tall(m), InvalidDimensionException);
}

TEST(assert_assert_tall, given_wide_throw) {
    // arrange
    constexpr sized_matrix_like<3, 4, std::complex<double>> m;
    // act / assert
    ASSERT_THROW(assert_tall(m), InvalidDimensionException);
}

TEST(assert_assert_tall, given_tall_should_not_throw) {
    // arrange
    constexpr sized_matrix_like<4, 3, float> m;
    // act / assert
    ASSERT_NO_THROW(assert_tall(m));
}

TEST(assert_can_multiple, given_multipliable_should_not_throw) {
    // arrange
    constexpr sized_matrix_like<4, 3, float> a;
    constexpr sized_matrix_like<3, 4, std::complex<long long>> b;
    // act / assert
    ASSERT_NO_THROW(assert_can_multiply(a, b));
}

TEST(assert_can_multiple, given_non_multipliable_should_throw) {
    // arrange
    constexpr sized_matrix_like<4, 3, std::complex<float>> a;
    constexpr sized_matrix_like<4, 4, char> b;
    // act / assert
    ASSERT_THROW(assert_can_multiply(a, b), InvalidDimensionException);
}

TEST(assert_same_dimensions, given_matrix_like_of_same_dimensions_should_not_throw) {
    // arrange
    constexpr sized_matrix_like<3, 3, char> a;
    constexpr sized_matrix_like<3, 3, short> b;
    constexpr sized_matrix_like<3, 3, int> c;
    // act / assert
    ASSERT_NO_THROW(assert_same_dimensions(a, b, c));
}

TEST(assert_same_dimensions, given_matrix_like_of_diff_dimensions_should_throw) {
    // arrange
    constexpr sized_matrix_like<3, 3, char> a;
    constexpr sized_matrix_like<3, 3, short> b;
    constexpr sized_matrix_like<2, 3, int> c;
    // act / assert
    ASSERT_THROW(assert_same_dimensions(a, b, c), InvalidDimensionException);
}
