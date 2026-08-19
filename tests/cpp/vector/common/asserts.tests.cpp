#include "gtest/gtest.h"

#include "mathpp/implementation/vector/common/asserts.h"

template<std::size_t N, typename T>
struct sized_vector_like {
    using ValueType = T;
    static constexpr bool isComplex = true;

    [[nodiscard]] std::size_t n() const {
        return N;
    }

    [[nodiscard]] T get(std::size_t) const;
    void set(std::size_t, T);
};

TEST(vector_assert_same_size, given_vector_of_same_size_should_return_true) {
    // arrange
    constexpr sized_vector_like<3, float> a;
    constexpr sized_vector_like<3, int> b;
    constexpr sized_vector_like<3, std::complex<double>> c;
    // act / assert
    ASSERT_NO_THROW(assert_same_size(a, b, c));
}

TEST(vector_assert_same_size, given_vector_of_diff_size_should_return_false) {
    // arrange
    constexpr sized_vector_like<3, float> a;
    constexpr sized_vector_like<2, int> b;
    constexpr sized_vector_like<3, std::complex<double>> c;
    // act / assert
    ASSERT_THROW(assert_same_size(a, b, c), InvalidSizeException);
}
