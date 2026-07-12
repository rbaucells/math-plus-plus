#include "gtest/gtest.h"

#include "mathpp/implementation/vector/common/traits.h"

template<typename TValueType, bool TisComplex>
struct should_be_vector_like {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t n() const;
};

TEST(vector_like, given_should_be_vector_like_should_return_true_1) {
    static_assert(vector_like<should_be_vector_like<float, true>>);
}

TEST(vector_like, given_should_be_vector_like_should_return_true_2) {
    static_assert(vector_like<should_be_vector_like<float, false>>);
}

TEST(vector_like, given_should_be_vector_like_should_return_true_3) {
    static_assert(vector_like<should_be_vector_like<std::complex<double>, false>>);
}

TEST(vector_like, given_float_should_return_false) {
    static_assert(!vector_like<float>);
}

TEST(is_vector_like_v, given_should_be_vector_like_should_return_true) {
    static_assert(is_vector_like_v<should_be_vector_like<float, true>>);
}

TEST(is_vector_like_v, given_float_should_return_false) {
    static_assert(!is_vector_like_v<float>);
}

TEST(is_vector_like, given_should_be_vector_like_should_return_true) {
    static_assert(is_vector_like<should_be_vector_like<float, true>>::value);
}

TEST(is_vector_like, given_float_should_return_false) {
    static_assert(!is_vector_like<float>::value);
}

TEST(underlying_type, given_f_vector_like_should_return_float) {
    static_assert(std::same_as<underlying_type<should_be_vector_like<float, true>>::ValueType, float>);
}

TEST(underlying_type, given_cd_vector_like_should_return_float) {
    static_assert(std::same_as<underlying_type<should_be_vector_like<std::complex<double>, true>>::ValueType, std::complex<double>>);
}
