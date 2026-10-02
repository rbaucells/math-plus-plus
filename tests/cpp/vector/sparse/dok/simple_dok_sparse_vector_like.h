#ifndef MATHPP_TESTS_SIMPLE_DOK_SPARSE_VECTOR_LIKE_H
#define MATHPP_TESTS_SIMPLE_DOK_SPARSE_VECTOR_LIKE_H

#include <cstddef>
#include <initializer_list>
#include <flat_map>
#include <tuple>
#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/common/compare.h"

template<typename T>
struct SimpleDokSparseVectorLike {
    using ValueType = T;
    static constexpr bool isComplex = is_complex_v<T>;

    std::size_t n_;
    std::flat_map<std::size_t, T> map_;

    SimpleDokSparseVectorLike(std::size_t n, std::initializer_list<std::tuple<T, std::size_t>> data) : n_(n) {
        for (const auto& [value, index] : data) {
            map_[index] = value;
        }
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    [[nodiscard]] std::size_t nnz() const {
        return map_.size();
    }

    [[nodiscard]] T get(std::size_t i) const {
        if (auto it = map_.find(i); it != map_.end()) {
            return *it;
        }

        return 0;
    }

    void set(std::size_t i, T v) {
        if (compare(v, 0)) {
            map_.erase(i);
        }
        else {
            map_[i] = v;
        }
    }

    [[nodiscard]] const std::flat_map<std::size_t, T>& map() const {
        return map_;
    }

    [[nodiscard]] std::flat_map<std::size_t, T>& map() {
        return map_;
    }
};

#endif // MATHPP_TESTS_SIMPLE_DOK_SPARSE_VECTOR_LIKE_H
