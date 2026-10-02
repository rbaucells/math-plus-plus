#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VECTOR_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VECTOR_H

#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/common/telemetry.h"

#include "traits.h"

#include <cstddef>
#include <initializer_list>
#include <ranges>
#include <tuple>
#include <cstring>
#include <algorithm>
#include <span>
#include <unordered_map>

/**
 * @brief Owning sparse vector in DOK storage format.
 * @tparam T Scalar type of vector elements.
 */
template<scalar T>
struct DokSparseVector {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    /**
     * @brief Default constructor.
     *
     * Creates a vector of size 0.
     * Does not allocate memory on heap.
     * n and nnz are set to 0, values and indices are set to nullptr.
     */
    DokSparseVector() : n_(0), map_() {}

    /**
     * @brief Sized constructor.
     *
     * Creates a vector of size n with 0 nnz elements.
     * Does not allocate memory on heap.
     *
     * @param n Size of constructed vector.
     */
    explicit DokSparseVector(const std::size_t n) : n_(n), map_() {}

    /**
     * @brief Initializer list constructor.
     *
     * Allocates around 'initializerList.size() * sizeof(void*) + initializerList.size() * (24 + sizeof(T))' bytes of memory on the heap.
     * Emits an allocation.
     *
     * @param n Size of vector.
     * @param initializerList Initializer list of T, std::size_t tuples. Representing value and index.
     */
    DokSparseVector(const std::size_t n, std::initializer_list<std::tuple<T, std::size_t>> initializerList) : n_(n), map_(initializerList.size()) {
        for (const auto& nonZeroElement: initializerList) {
            map_[std::get<1>(nonZeroElement)] = std::get<0>(nonZeroElement);
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Range constructor.
     *
     * Allocates 'range.size() * sizeof(void*) + range.size() * (24 + sizeof(T))' bytes of memory on the heap.
     * Emits an allocation.
     *
     * @param n Size of vector.
     * @param range Any sized range type of T, std::size_t tuples. Representing value and index.
     */
    template<std::ranges::sized_range R> requires (is_tuple_v<std::ranges::range_value_t<R>> && lossless_convertible<std::tuple_element_t<0, std::ranges::range_value_t<R>>, T> && std::is_same_v<std::tuple_element_t<1, std::ranges::range_value_t<R>>, std::size_t>)
    DokSparseVector(const std::size_t n, R range) : n_(n), map_(range.size()) {
        for (const auto& nonZeroElement: range) {
            map_[std::get<1>(nonZeroElement)] = std::get<0>(nonZeroElement);
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from same type DokSparseVector.
     *
     * Allocates 'nnz * sizeof(void*) + nnz * (24 + sizeof(T))' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @param other Same type DokSparseVector to copy from.
     */
    DokSparseVector(const DokSparseVector<T>& other) : n_(other.n_), map_(other.map_) {
        Telemetry::emit_allocation();
        Telemetry::emit_copy_construct();
    }

    /**
    * @brief Copy constructor from different type DokSparseVector.
    *
    * Allocates 'nnz * sizeof(void*) + nnz * (24 + sizeof(T))' bytes on heap.
    * Emits an allocation and copy_construct.
    *
    * @tparam U Scalar type of other DokSparseVector.
    * @param other DokSparseVector to copy from.
    */
    template<scalar U> requires lossless_convertible<U, T>
    DokSparseVector(const DokSparseVector<U>& other) : n_(other.n()), map_(other.map().size()) {
        for (auto [key, value] : other.map()) {
            map_[key] = value;
        }

        Telemetry::emit_allocation();
        Telemetry::emit_copy_construct();
    }

    /**
     * @brief Copy constructor from any dok sparse vector like object.
     *
     * Allocates 'nnz * sizeof(void*) + nnz * (24 + sizeof(T))' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @tparam U Type that fulfills 'dok_sparse_vector_like' concept.
     * @param other Dense vector like object to copy from.
     */
    template<dok_sparse_vector_like U> requires lossless_convertible<typename U::ValueType, T>
    DokSparseVector(const U& other) : n_(other.n()), map_(other.map().size()) {
        for (auto [key, value] : other.map()) {
            map_[key] = value;
        }

        Telemetry::emit_allocation();
        Telemetry::emit_copy_construct();
    }

    /**
     * @brief Move constructor from same type DokSparseVector.
     *
     * Does not allocate memory on the heap.
     * Emits a move_construct.
     *
     * @param other SparseVector to move from.
     * @note Invalidates 'other' vector and leaves in an empty state.
     */
    DokSparseVector(DokSparseVector<T>&& other) noexcept : n_(other.n_), map_(std::move(other.map_)) {
        other.n_ = 0;

        Telemetry::emit_move_construct();
    }

    /**
     * @brief Copy assignment operator from same type DokSparseVector.
     *
     * If this vector's nnz is the same as 'other's, emits a copy_assign.
     * If this vector's nnz is different, emits a deallocation, allocation, and a copy_assign.
     * If this vector's nnz is different, allocates 'nnz * sizeof(void*) + nnz * (24 + sizeof(T))' bytes of memory.
     * If this vector's nnz is same, allocates 'nnz * (24 + sizeof(T))' bytes of memory.
     *
     * @param other DokSparseVector to copy from.
     * @return Reference to this vector.
     */
    DokSparseVector<T>& operator=(const DokSparseVector<T>& other) {
        if (this != &other) {
            map_ = other.map_;
            n_ = other.n_;

            Telemetry::emit_deallocation();
            Telemetry::emit_allocation();
            Telemetry::emit_copy_assign();
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator from different type DokSparseVector.
     *
     * If this vector's nnz is the same as 'other's, emits a copy_assign.
     * If this vector's nnz is different, emits a deallocations, allocations, and a copy_assign.
     * If this vector's nnz is different, allocates 'nnz * sizeof(void*) + nnz * (24 + sizeof(T))' bytes of memory.
     * If this vector's nnz is same, allocates 'nnz * (24 + sizeof(T))' bytes of memory.
     *
     * @tparam U Scalar type of other DokSparseVector.
     * @param other DokSparseVector to copy from.
     * @return Reference to this vector.
     */
    template<scalar U> requires lossless_convertible<U, T>
    DokSparseVector<T>& operator=(const DokSparseVector<U>& other) {
        map_.clear();
        Telemetry::emit_deallocation();

        map_.reserve(other.map().size());
        Telemetry::emit_allocation();

        for (auto [index, value] : other.map()) {
            map_[index] = value;
        }

        n_ = other.n();

        Telemetry::emit_copy_assign();

        return *this;
    }

    /**
     * @brief Copy assignment operator from any dok sparse vector like object.
     *
     * If this vector's nnz is the same as 'other's, emits a copy_assign.
     * If this vector's nnz is different, emits deallocation, allocation, and a copy_assign.
     * If this vector's nnz is different, allocates 'nnz * sizeof(void*) + nnz * (24 + sizeof(T))' bytes of memory.
     * If this vector's nnz is same, allocates 'nnz * (24 + sizeof(T))' bytes of memory.
     *
     * @tparam U Type that fulfills 'dok_sparse_vector_like' concept.
     * @param other Dok sparse vector like object to copy from.
     * @return Reference to this vector.
     */
    template<dok_sparse_vector_like U> requires lossless_convertible<typename U::ValueType, T>
    DokSparseVector<T>& operator=(const U& other) {
        map_.clear();
        Telemetry::emit_deallocation();

        map_.reserve(other.map().size());
        Telemetry::emit_allocation();

        for (auto [index, value] : other.map()) {
            map_[index] = value;
        }
        n_ = other.n();

        Telemetry::emit_copy_assign();

        return *this;
    }

    /**
     * @brief Move assignment operator from same type DokSparseVector.
     *
     * Does not allocate memory on heap.
     * Emits a move_assign.
     *
     * @param other DokSparseVector to move from.
     * @return Reference to this vector.
     * @note Invalidates other vector and leaves in a empty state.
     */
    DokSparseVector<T>& operator=(DokSparseVector<T>&& other) noexcept {
        if (this != &other) {
            map_ = std::move(other.map_);

            n_ = other.n_;
            other.n_ = 0;

            Telemetry::emit_move_assign();
        }

        return *this;
    }

    /**
     * @brief Accesses the element at a provided index.
     *
     * Retrieves the element at (i).
     * Checks bounds of provided i index.
     * Does not allocate memory on the heap.
     * O(nnz) time complexity.
     *
     * @param i Zero-based index of element.
     *
     * @return The element at (i).
     * @note Index must be withing vector bounds.
     * @throws InvalidIndexException If index 'i' is out of bounds (i.e. bigger than n).
     */
    [[nodiscard]] T get(const std::size_t i) const {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access vector at invalid index");
        }

        if (auto it = map_.find(i); it != map_.end()) {
            return it->second;
        }

        return 0;
    }

    /**
     * @brief Sets the element at a provided index to a provided value.
     *
     * Checks bounds of provided i index.
     * O(nnz) time complexity.
     *
     * If setting 0 on non-zero element, alocates '(nnz - 1) * sizeof(T) + (nnz - 1) * sizeof(std::size_t)' bytes on heap and emits 2x allocations and 2x deallocations.
     * If setting 0 on zero element, does nothing.
     * If setting non-zero on 0 element, alocates '(nnz + 1) * sizeof(T) + (nnz + 1) * sizeof(std::size_t)' bytes on heap and emits 2x allocations and 2x deallocations.
     * If setting non-zero on non-zero element, simply sets value.
     *
     * @param i Zero-based index of element.
     * @param v Value to set in element.
     *
     * @note Index must be withing vector bounds.
     * @throws InvalidIndexException If index 'i' is out of bounds (i.e. bigger than n).
     */
    void set(const std::size_t i, const T v) {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access vector at invalid index");
        }

        if (compare(v, 0)) {
            map_.erase(i);
        }
        else {
            map_[i] = v;
        }
    }

    /**
     * @return Number of non-zero elements in DokSparseVector.
     */
    [[nodiscard]] std::size_t nnz() const {
        return map_.size();
    }

    /**
     * @return Size of DokSparseVector.
     */
    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    /**
     * @return Const-reference to map of index, value pairs of non zero elements.
     */
    [[nodiscard]] const std::unordered_map<std::size_t, T>& map() const {
        return map_;
    }

    /**
     * @return Reference to map of index, value pairs of non zero elements.
     */
    [[nodiscard]] std::unordered_map<std::size_t, T>& map() {
        return map_;
    }

    ~DokSparseVector() = default;

private:
    // size of vector
    std::size_t n_;
    // key-value pair of index-element
    std::unordered_map<std::size_t, T> map_;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VECTOR_H
