// #pragma once
// #include "../matrix.h"
// #include "../../../expression.h"
// #include "../../../helper.h"
//
// template<dense_matrix_base T, dense_matrix_base U, dense_matrix_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
// DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> multiply(const T& a, const U& b, const ARGS&... args) {
//     assert_can_multiply(a, b, args...);
//
//     if constexpr (sizeof...(args) == 0) {
//         const int aRows = a.rows();
//         const int aColumns = a.columns();
//         const int bColumns = b.columns();
//
//         DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType>> result(aRows, bColumns, false);
//
//         for (int c = 0; c < bColumns; c++) {
//             for (int r = 0; r < aRows; r++) {
//                 result[c, r] = 0;
//
//                 for (int x = 0; x < aColumns; x++) {
//                     result[c, r] += a[x, r] * b[c, x];
//                 }
//             }
//         }
//
//         return std::move(result);
//     }
//
//     DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> result = multiply(a, b);
//
//     ((result = multiply(result, args)), ...);
//
//     return std::move(result);
// }
//
// template<dense_matrix_base... ARGS> requires has_common_type<typename ARGS::ValueType...>
// struct DenseMatrixMultiplyExpr : Expression<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> , ARGS...> {
//     using Expression<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> , ARGS...>::Expression;
//
//     [[nodiscard]] DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> evaluate() const override {
//         return std::apply([](const auto&... args) {
//             return multiply(args...);
//         }, this->args);
//     }
//
//     template<dense_matrix_base OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
//     DenseMatrixMultiplyExpr<ARGS..., OTHER> operator*(const OTHER& other) const {
//         return std::apply([&](const auto&... args) {
//             return DenseMatrixMultiplyExpr<ARGS..., OTHER>(args..., other);
//         }, this->args);
//     }
// };
//
// template<dense_matrix_base T, dense_matrix_base U> requires has_common_type<typename T::ValueType, typename U::ValueType>
// DenseMatrixMultiplyExpr<T, U> operator*(const T& a, const U& b) {
//     return DenseMatrixMultiplyExpr<T, U>(a, b);
// }