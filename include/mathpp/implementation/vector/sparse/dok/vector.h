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
#include <map>

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
     * n and nnz are set to 0, the map is empty.
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
     * Allocates around 'initializerList.size() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
     * Emits an allocation.
     *
     * @param n Size of vector.
     * @param initializerList Initializer list of T, std::size_t tuples. Representing value and index.
     */
    DokSparseVector(const std::size_t n, std::initializer_list<std::tuple<T, std::size_t>> initializerList) : n_(n), map_() {
        for (const auto& nonZeroElement: initializerList) {
            const auto index = std::get<1>(nonZeroElement);
            map_[index] = std::get<0>(nonZeroElement);
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Range constructor.
     *
     * Allocates around 'range.size() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
     * Emits an allocation.
     *
     * @param n Size of vector.
     * @param range Any sized range type of T, std::size_t tuples. Representing value and index.
     */
    template<std::ranges::sized_range R> requires (is_tuple_v<std::ranges::range_value_t<R>> && lossless_convertible<std::tuple_element_t<0, std::ranges::range_value_t<R>>, T> && std::is_same_v<std::tuple_element_t<1, std::ranges::range_value_t<R>>, std::size_t>)
    DokSparseVector(const std::size_t n, R range) : n_(n), map_() {
        for (const auto& nonZeroElement: range) {
            const auto index = std::get<1>(nonZeroElement);
            map_[index] = std::get<0>(nonZeroElement);
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from same type DokSparseVector.
     *
     * Allocates around 'other.nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
     * Emits an allocation and a copy_construct.
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
    * Allocates around 'other.nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
    * Emits an allocation and a copy_construct.
    *
    * @tparam U Scalar type of other DokSparseVector.
    * @param other DokSparseVector to copy from.
    */
    template<scalar U> requires lossless_convertible<U, T>
    DokSparseVector(const DokSparseVector<U>& other) : n_(other.n()), map_() {
        for (auto [key, value] : other.map()) {
            map_[key] = value;
        }

        Telemetry::emit_allocation();
        Telemetry::emit_copy_construct();
    }

    /**
     * @brief Copy constructor from any dok sparse vector like object.
     *
     * Allocates around 'other.nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
     * Emits an allocation and a copy_construct.
     *
     * @tparam U Type that fulfills 'dok_sparse_vector_like' concept.
     * @param other Dense vector like object to copy from.
     */
    template<dok_sparse_vector_like U> requires lossless_convertible<typename U::ValueType, T>
    DokSparseVector(const U& other) : n_(other.n()), map_() {
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
     * Deallocates around 'nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes.
     * Allocates around 'other.nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
     * Emits a deallocation, an allocation, and a copy_assign.
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
     * Deallocates around 'nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes.
     * Allocates around 'other.nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
     * Emits a deallocation, an allocation, and a copy_assign.
     *
     * @tparam U Scalar type of other DokSparseVector.
     * @param other DokSparseVector to copy from.
     * @return Reference to this vector.
     */
    template<scalar U> requires lossless_convertible<U, T>
    DokSparseVector<T>& operator=(const DokSparseVector<U>& other) {
        map_.clear();
        Telemetry::emit_deallocation();

        for (auto [index, value] : other.map()) {
            map_[index] = value;
        }
        Telemetry::emit_allocation();

        n_ = other.n();

        Telemetry::emit_copy_assign();

        return *this;
    }

    /**
     * @brief Copy assignment operator from any dok sparse vector like object.
     *
     * Deallocates around 'nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes.
     * Allocates around 'other.nnz() * (sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*))' bytes on the heap.
     * Emits a deallocation, an allocation, and a copy_assign.
     *
     * @tparam U Type that fulfills 'dok_sparse_vector_like' concept.
     * @param other Dok sparse vector like object to copy from.
     * @return Reference to this vector.
     */
    template<dok_sparse_vector_like U> requires lossless_convertible<typename U::ValueType, T>
    DokSparseVector<T>& operator=(const U& other) {
        map_.clear();
        Telemetry::emit_deallocation();

        for (auto [index, value] : other.map()) {
            map_[index] = value;
        }
        Telemetry::emit_allocation();

        n_ = other.n();

        Telemetry::emit_copy_assign();

        return *this;
    }

    /**
     * @brief Move assignment operator from same type DokSparseVector.
     *
     * Does not allocate memory on the heap.
     * Emits a deallocation and a move_assign.
     *
     * @param other DokSparseVector to move from.
     * @return Reference to this vector.
     * @note Invalidates other vector and leaves in a empty state.
     */
    DokSparseVector<T>& operator=(DokSparseVector<T>&& other) noexcept {
        if (this != &other) {
            map_ = std::move(other.map_);
            Telemetry::emit_deallocation();

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
     * O(log(nnz)) time complexity.
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
     * O(log(nnz)) time complexity.
     *
     * If setting 0 on non-zero element, deallocates around 'sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*)' bytes and emits a deallocation.
     * If setting 0 on zero element, does nothing.
     * If setting non-zero on 0 element, allocates around 'sizeof(std::size_t) + sizeof(T) + 3 * sizeof(void*)' bytes and emits an allocation.
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
            if (map_.erase(i) != 0) {
                Telemetry::emit_deallocation();
            }
        }
        else {
            map_[i] = v;
            Telemetry::emit_allocation();
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
    [[nodiscard]] const std::map<std::size_t, T>& map() const {
        return map_;
    }

    /**
     * @return Reference to map of index, value pairs of non zero elements.
     */
    [[nodiscard]] std::map<std::size_t, T>& map() {
        return map_;
    }

    ~DokSparseVector() = default;

private:
    // size of vector
    std::size_t n_;
    // key-value pair of index-element
    std::map<std::size_t, T> map_;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VECTOR_H
