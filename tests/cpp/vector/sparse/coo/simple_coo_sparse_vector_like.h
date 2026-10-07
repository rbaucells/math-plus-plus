#ifndef MATHPP_TESTS_SIMPLE_COO_SPARSE_VECTOR_LIKE_H
#define MATHPP_TESTS_SIMPLE_COO_SPARSE_VECTOR_LIKE_H

#include <cstddef>
#include <initializer_list>
#include <vector>
#include <span>
#include <tuple>
#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/common/compare.h"

template<typename T>
struct SimpleCooSparseVectorLike {
    using ValueType = T;
    static constexpr bool isComplex = is_complex_v<T>;

    std::size_t n_;
    std::size_t nnz_;
    std::vector<std::size_t> indices_;
    std::vector<T> values_;

    SimpleCooSparseVectorLike(std::size_t n, std::initializer_list<std::tuple<T, std::size_t>> data) : n_(n), nnz_(data.size()), indices_(nnz_), values_(nnz_) {
        std::size_t i = 0;

        for (const auto& [value, index] : data) {
            values_[i] = value;
            indices_[i] = index;
            ++i;
        }
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    [[nodiscard]] std::size_t nnz() const {
        return nnz_;
    }

    [[nodiscard]] T get(std::size_t i) const {
        for (std::size_t j = 0; j < nnz_; ++j) {
            if (indices_[j] == i) {
                return values_[j];
            }
        }

        return 0;
    }

    void set(std::size_t i, T v) {
        for (std::size_t j = 0; j < nnz_; ++j) {
            if (indices_[j] == i) {
                if (compare(v, 0)) {
                    indices_.erase(indices_.begin() + j);
                    values_.erase(values_.begin() + j);
                    nnz_--;
                }
                else {
                    values_[j] = v;
                }

                return;
            }
        }

        if (!compare(v, 0)) {
            indices_.push_back(i);
            values_.push_back(v);
            nnz_++;
        }
    }

    [[nodiscard]] std::span<const std::size_t> indices() const {
        return indices_;
    }

    [[nodiscard]] std::span<std::size_t> indices() {
        return indices_;
    }

    [[nodiscard]] std::span<const T> values() const {
        return values_;
    }

    [[nodiscard]] std::span<T> values() {
        return values_;
    }
};

#endif // MATHPP_TESTS_SIMPLE_COO_SPARSE_VECTOR_LIKE_H
