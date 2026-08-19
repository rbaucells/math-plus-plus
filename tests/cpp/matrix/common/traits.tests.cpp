#include "gtest/gtest.h"

#include "mathpp/implementation/matrix/common/traits.h"

template<typename TValueType, bool TisComplex>
struct should_be_matrix_like {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t rows() const;
    [[nodiscard]] std::size_t columns() const;

    [[nodiscard]] TValueType get(std::size_t, std::size_t) const;
    void set(std::size_t, std::size_t, TValueType);
};

TEST(matrix_like, given_should_be_matrix_like_should_return_true_1) {
    static_assert(matrix_like<should_be_matrix_like<float, true>>);
}

TEST(matrix_like, given_should_be_matrix_like_should_return_true_2) {
    static_assert(matrix_like<should_be_matrix_like<float, false>>);
}

TEST(matrix_like, given_should_be_matrix_like_should_return_true_3) {
    static_assert(matrix_like<should_be_matrix_like<std::complex<double>, false>>);
}

TEST(matrix_like, given_float_should_return_false) {
    static_assert(!matrix_like<float>);
}

TEST(is_matrix_like_v, given_should_be_matrix_like_should_return_true) {
    static_assert(is_matrix_like_v<should_be_matrix_like<float, true>>);
}

TEST(is_matrix_like_v, given_float_should_return_false) {
    static_assert(!is_matrix_like_v<float>);
}

TEST(is_matrix_like, given_should_be_matrix_like_should_return_true) {
    static_assert(is_matrix_like<should_be_matrix_like<float, true>>::value);
}

TEST(is_matrix_like, given_float_should_return_false) {
    static_assert(!is_matrix_like<float>::value);
}

TEST(underlying_type, given_f_matrix_like_should_return_float) {
    static_assert(std::same_as<underlying_type<should_be_matrix_like<float, true>>::ValueType, float>);
}

TEST(underlying_type, given_cd_matrix_like_should_return_float) {
    static_assert(std::same_as<underlying_type<should_be_matrix_like<std::complex<double>, true>>::ValueType, std::complex<double>>);
}
