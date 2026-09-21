#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_VECTOR_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_VECTOR_H

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

/**
 * @brief Owning sparse vector in COO storage format.
 * @tparam T Scalar type of vector elements.
 */
template<scalar T>
struct CooSparseVector {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    /**
     * @brief Default constructor.
     *
     * Creates a vector of size 0.
     * Does not allocate memory on heap.
     * n and nnz are set to 0, values and indices are set to nullptr.
     */
    CooSparseVector() : n_(0), nnz_(0), values_(nullptr), indices_(nullptr) {};

    /**
     * @brief Sized constructor.
     *
     * Creates a vector of size n with 0 nnz elements.
     * Does not allocate memory on heap.
     *
     * @param n Size of constructed vector.
     */
    explicit CooSparseVector(const std::size_t n) : n_(n), nnz_(0), values_(new T[0]), indices_(new std::size_t[0]) {
    }

    /**
     * @brief Initializer list constructor.
     *
     * Allocates 'initializerList.size() x sizeof(T) + initializerList.size() x sizeof(std::size_t)' bytes of memory on the heap.
     * Emits an allocation.
     *
     * @param n Size of vector.
     * @param initializerList Initializer list of T, std::size_t tuples. Representing value and index.
     *
     * @note 'initializerList' must be sorted in increasing indices.
     */
    CooSparseVector(const std::size_t n, std::initializer_list<std::tuple<T, std::size_t>> initializerList) : n_(n), nnz_(initializerList.size()), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        std::size_t i = 0;
        for (const auto& nonZeroElement: initializerList) {
            values_[i] = std::get<0>(nonZeroElement);
            indices_[i] = std::get<1>(nonZeroElement);
            ++i;
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Range constructor.
     *
     * Allocates 'range.size() x sizeof(T) + range.size() x sizeof(std::size_t)' bytes of memory on the heap.
     * Emits an allocation.
     *
     * @param n Size of vector.
     * @param range Any sized range type of T, std::size_t tuples. Representing value and index.
     *
     * @note 'range' must be sorted in increasing indices.
     */
    template<std::ranges::sized_range R> requires (is_tuple_v<std::ranges::range_value_t<R>> && lossless_convertible<std::tuple_element_t<0, std::ranges::range_value_t<R>>, T> && std::is_same_v<std::tuple_element_t<1, std::ranges::range_value_t<R>>, std::size_t>)
    CooSparseVector(const std::size_t n, R range) : n_(n), nnz_(range.size()), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        std::size_t i = 0;
        for (const auto& nonZeroElement: range) {
            values_[i] = std::get<0>(nonZeroElement);
            indices_[i] = std::get<1>(nonZeroElement);
            ++i;
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from same type CooSparseVector.
     *
     * Allocates 'nnz * sizeof(T) + nnz * sizeof(std::size_t)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @param other Same type CooSparseVector to copy from.
     */
    CooSparseVector(const CooSparseVector<T>& other) : n_(other.n_), nnz_(other.nnz_), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        std::memcpy(values_, other.values_, nnz_ * sizeof(T));
        std::memcpy(indices_, other.indices_, nnz_ * sizeof(std::size_t));

        Telemetry::emit_allocation();
        Telemetry::emit_copy_construct();
    }

    /**
    * @brief Copy constructor from different type CooSparseVector.
    *
    * Allocates 'nnz * sizeof(T) + nnz * sizeof(std::size_t)' bytes on the heap.
    * Emits an allocation and copy_construct.
    *
    * @tparam U Scalar type of other CooSparseVector.
    * @param other CooSparseVector to copy from.
    */
    template<scalar U> requires lossless_convertible<U, T>
    CooSparseVector(const CooSparseVector<U>& other) : n_(other.n()), nnz_(other.nnz()), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        std::copy(other.rawValues(), other.rawValues() + nnz_, values_);
        std::memcpy(indices_, other.rawIndices(), nnz_ * sizeof(std::size_t));

        Telemetry::emit_allocation();
        Telemetry::emit_copy_construct();
    }

    /**
     * @brief Copy constructor from any coo sparse vector like object.
     *
     * Allocates 'n * sizeof(T)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @tparam U Type that fulfills 'coo_sparse_vector_like' concept.
     * @param other Dense vector like object to copy from.
     */
    template<coo_sparse_vector_like U>
    CooSparseVector(const U& other) : n_(other.n()), nnz_(other.nnz()), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        for (std::size_t i = 0; i < nnz_; i++) {
            values_[i] = other.values()[i];
            indices_[i] = other.values()[i];
        }

        Telemetry::emit_allocation();
        Telemetry::emit_copy_construct();
    }

    /**
     * @brief Move constructor from same type CooSparseVector.
     *
     * Does not allocate memory on the heap.
     * Emits a move_construct.
     *
     * @param other SparseVector to move from.
     * @note Invalidates 'other' vector and leaves in an empty state.
     */
    CooSparseVector(CooSparseVector<T>&& other) noexcept : n_(other.n_), nnz_(other.nnz_), values_(other.values_), indices_(other.indices_) {
        other.values_ = nullptr;
        other.indices_ = nullptr;
        other.n_ = 0;
        other.nnz_ = 0;

        Telemetry::emit_move_construct();
    }

    /**
     * @brief Copy assignment operator from same type CooSparseVector.
     *
     * If this vector's nnz is the same as 'other's, emits a copy_assign.
     * If this vector's nnz is different, emits a 2 deallocations, 2 allocations, and a copy_assign.
     * If this vector's nnz is different, allocates 'other.nnz * sizeof(T) + other.nnz * sizeof(std::size_t)' bytes of memory.
     *
     * @param other CooSparseVector to copy from.
     * @return Reference to this vector.
     */
    CooSparseVector<T>& operator=(const CooSparseVector<T>& other) {
        if (this != &other) {
            if (nnz_ != other.nnz_) {
                nnz_ = other.nnz_;

                delete[] values_;
                Telemetry::emit_deallocation();
                values_ = new T[nnz_];
                Telemetry::emit_allocation();

                delete[] indices_;
                Telemetry::emit_deallocation();
                indices_ = new std::size_t[nnz_];
                Telemetry::emit_allocation();

            }

            n_ = other.n_;

            std::memcpy(values_, other.values_, nnz_ * sizeof(T));
            std::memcpy(indices_, other.indices_, nnz_ * sizeof(std::size_t));

            Telemetry::emit_copy_assign();
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator from different type CooSparseVector.
     *
     * If this vector's nnz is the same as 'other's, emits a copy_assign.
     * If this vector's nnz is different, emits a 2 deallocations, 2 allocations, and a copy_assign.
     * If this vector's nnz is different, allocates 'other.nnz * sizeof(T) + other.nnz * sizeof(std::size_t)' bytes of memory.
     *
     * @tparam U Scalar type of other CooSparseVector.
     * @param other CooSparseVector to copy from.
     * @return Reference to this vector.
     */
    template<scalar U> requires lossless_convertible<U, T>
    CooSparseVector<T>& operator=(const CooSparseVector<U>& other) {
        if (nnz_ != other.nnz()) {
            nnz_ = other.nnz();

            delete[] values_;
            Telemetry::emit_deallocation();
            values_ = new T[nnz_];
            Telemetry::emit_allocation();

            delete[] indices_;
            Telemetry::emit_deallocation();
            indices_ = new std::size_t[nnz_];
            Telemetry::emit_allocation();
        }

        n_ = other.n();

        std::copy(other.rawValues(), other.rawValues() + nnz_, values_);
        std::memcpy(indices_, other.indices(), nnz_ * sizeof(std::size_t));

        Telemetry::emit_copy_assign();

        return *this;
    }

    /**
     * @brief Copy assignment operator from any coo sparse vector like object.
     *
     * If this vector's nnz is the same as 'other's, emits a copy_assign.
     * If this vector's nnz is different, emits 2 deallocations, 2 allocations, and a copy_assign.
     * If this vector's nnz is different, allocates 'other.nnz * sizeof(T) + other.nnz * sizeof(std::size_t)' bytes of memory.
     *
     * @tparam U Type that fulfills 'coo_sparse_vector_like' concept.
     * @param other Coo sparse vector like object to copy from.
     * @return Reference to this vector.
     */
    template<coo_sparse_vector_like U>
    CooSparseVector<T>& operator=(const U& other) {
        if (nnz_ != other.nnz()) {
            nnz_ = other.nnz();

            delete[] values_;
            Telemetry::emit_deallocation();
            values_ = new T[nnz_];
            Telemetry::emit_allocation();

            delete[] indices_;
            Telemetry::emit_deallocation();
            indices_ = new std::size_t[nnz_];
            Telemetry::emit_allocation();
        }

        for (std::size_t i = 0; i < nnz_; i++) {
            values_[i] = other.values()[i];
            indices_[i] = other.values()[i];
        }

        Telemetry::emit_copy_assign();

        return *this;
    }

    /**
     * @brief Move assignment operator from same type CooSparseVector.
     *
     * Does not allocate memory on heap.
     * Emits 2x deallocation and a move_assign.
     *
     * @param other CooSparseVector to move from.
     * @return Reference to this vector.
     * @note Invalidates other vector and leaves in a empty state.
     */
    CooSparseVector<T>& operator=(CooSparseVector<T>&& other) noexcept {
        if (this != &other) {
            delete[] values_;
            Telemetry::emit_deallocation();
            values_ = other.values_;
            other.values_ = nullptr;

            delete[] indices_;
            Telemetry::emit_deallocation();
            indices_ = other.indices_;
            other.indices_ = nullptr;

            nnz_ = other.nnz_;
            other.nnz_ = 0;

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

        for (std::size_t j = 0; j < nnz_; j++) {
            if (indices_[j] == i) {
                return values_[j];
            }
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

        std::size_t j;

        for (j = 0; j < nnz_; j++) {
            const std::size_t curIndex = indices_[j];

            if (curIndex == i) {
                // there is currently a non-zero element there, and we are placing a zero so we remove a non-zero element;
                if (compare(v, 0)) {
                    T* newValues = new T[nnz_ - 1];
                    Telemetry::emit_allocation();

                    // copy everything before us
                    std::memcpy(newValues, values_, j * sizeof(T));

                    // copy everything after us but 1 back
                    std::memcpy(&newValues[j], &values_[j + 1], (nnz_ - j - 1) * sizeof(T));

                    // delete old array
                    delete[] values_;
                    Telemetry::emit_deallocation();

                    // and set the new array
                    values_ = newValues;

                    std::size_t* newIndices = new std::size_t[nnz_ - 1];
                    Telemetry::emit_allocation();

                    std::memcpy(newIndices, indices_, j * sizeof(std::size_t));

                    std::memcpy(&newIndices[j], &indices_[j + 1], (nnz_ - j - 1) * sizeof(std::size_t));

                    delete[] indices_;
                    Telemetry::emit_deallocation();

                    indices_ = newIndices;

                    nnz_--;

                    return;
                }

                // there is a non-zero element, and we are setting another non-zero element, indices do not need to change
                values_[j] = v;

                return;
            }

            // arrays are sorted, no reason to keep iterating
            if (curIndex > i) {
                break;
            }
        }

        // there is currently a zero element, and we are setting another zero element
        if (compare(v, 0)) {
            return;
        }

        T* newValues = new T[nnz_ + 1];
        Telemetry::emit_allocation();

        // copy everything up to j
        std::memcpy(newValues, values_, j * sizeof(T));

        // set the new value
        newValues[j] = v;

        // copy everything after j
        std::memcpy(&newValues[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] values_;
        Telemetry::emit_deallocation();

        values_ = newValues;

        std::size_t* newIndices = new std::size_t[nnz_ + 1];
        Telemetry::emit_allocation();

        std::memcpy(newIndices, indices_, j * sizeof(std::size_t));

        newIndices[j] = i;

        std::memcpy(&newIndices[j + 1], &indices_[j], (nnz_ - j) * sizeof(std::size_t));

        delete[] indices_;
        Telemetry::emit_deallocation();

        indices_ = newIndices;

        nnz_++;
    }

    /**
     * @return Number of non-zero elements in CooSparseVector.
     */
    [[nodiscard]] std::size_t nnz() const {
        return nnz_;
    }

    /**
     * @return Size of CooSparseVector.
     */
    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    /**
     * @return Pointer to array containing all vector non zero values.
     * @note Pointer to array of size nnz.
     */
    [[nodiscard]] T* rawValues() {
        return values_;
    }

    /**
     * @return Const-pointer to array containing all vector non zero values.
     * @note Const-pointer to array of size nnz.
     */
    [[nodiscard]] const T* rawValues() const {
        return values_;
    }

    /**
     * @return Pointer to array containing all indices of vector non zero values.
     * @note Pointer to array of size nnz.
     */
    [[nodiscard]] std::size_t* rawIndices() {
        return indices_;
    }

    /**
     * @return Const-pointer to array containing all indices of vector non zero values.
     * @note Const-pointer to array of size nnz.
     */
    [[nodiscard]] const std::size_t* rawIndices() const {
        return indices_;
    }

    /**
     * @return Span containing all vector non zero values.
     * @note Span of size nnz.
     */
    [[nodiscard]] std::span<T> values() {
        return std::span<T>(values_, nnz_);
    }

    /**
     * @return Span of const elements containing all vector non zero values.
     * @note Span of size nnz.
     */
    [[nodiscard]] std::span<const T> values() const {
        return std::span<const T>(values_, nnz_);
    }

    /**
     * @return Span containing all indices of vector non zero values.
     * @note Span of size nnz.
     */
    [[nodiscard]] std::span<std::size_t> indices() {
        return std::span<std::size_t>(indices_, nnz_);
    }

    /**
     * @return Span of const elements containing all indices of vector non zero values.
     * @note Span of size nnz.
     */
    [[nodiscard]] std::span<const std::size_t> indices() const {
        return std::span<const std::size_t>(indices_, nnz_);
    }

    /**
     * @brief Destructor for CooSparseVector.
     * If values is not nullptr, emits a deallocation.
     * If indices is not nullptr, emits a deallocation.
     * Deallocates values and indices array.
     */
    ~CooSparseVector() {
        if (values_ != nullptr) {
            Telemetry::emit_deallocation();
            delete[] values_;
        }

        if (indices_ != nullptr) {
            Telemetry::emit_deallocation();
            delete[] indices_;
        }
    }

private:
    // size of vector
    std::size_t n_;
    // number of non zero elements
    std::size_t nnz_;

    // array of non-zero values
    T* values_;
    // array of indices of non-zero values
    std::size_t* indices_;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_VECTOR_H
