#ifndef MATHPP_IMPLEMENTATION_VECTOR_DENSE_VECTOR
#define MATHPP_IMPLEMENTATION_VECTOR_DENSE_VECTOR

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <concepts>
#include <cstring>

#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/telemetry.h"

#include "mathpp/implementation/common/traits.h"

#include "traits.h"


/**
 * @brief Owning dense vector.
 * @tparam T Scalar type of vector elements.
 */
template<scalar T>
struct DenseVector {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    /**
     * @brief Default constructor.
     *
     * Creates a vector of size 0.
     * Does not allocate memory on heap.
     * n is set to 0 and data is set to nullptr.
     */
    DenseVector() : n_(0), data_(nullptr) {}

    /**
     * @brief Sized constructor.
     *
     * Creates a vector of size n.
     * Allocates 'n * sizeof(T)' bytes on heap.
     * Optionally fills the allocated memory with default initialized elements.
     * Emits an allocation.
     *
     * @param n Number of elements in constructed vector.
     * @param fill If true initializes all elements to default. If false leaves elements uninitialized.
     */
    DenseVector(const std::size_t n, const bool fill = true) : n_(n), data_(fill ? new T[n_]() : new T[n_]) {
        Telemetry::emit_allocation();
    }

    /**
     * @brief Initializer list constructor.
     *
     * Creates a vector of size initializerList.size.
     * Allocates 'n * sizeof(T)' bytes on heap.
     * Emits an allocation.
     *
     * @param initializerList Initializer list of vector elements
     */
    DenseVector(const std::initializer_list<T>& initializerList) : n_(initializerList.size()), data_(new T[n_]) {
        std::size_t i = 0;
        for (const T element: initializerList) {
            data_[i] = element;
            ++i;
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from same type DenseVector.
     *
     * Allocates 'n * sizeof(T)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @param other Same type DenseVector to copy from.
     */
    DenseVector(const DenseVector<T>& other) : n_(other.n_), data_(new T[n_]) {
        std::memcpy(data_, other.data_, n_ * sizeof(T));

        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from different type DenseVector.
     *
     * Allocates 'n * sizeof(T)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @tparam U Scalar type of other DenseVector.
     * @param other DenseVector to copy from.
     */
    template<scalar U> requires is_lossless_convertible<U, T>
    DenseVector(const DenseVector<U>& other) : n_(other.n()), data_(new T[n_]) {
        std::copy(other.rawData(), other.rawData() + n_, data_);

        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from any dense vector like object.
     *
     * Allocates 'n * sizeof(T)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @tparam U Type that fulfills 'dense_vector_like' concept.
     * @param other Dense vector like object to copy from.
     */
    template<dense_vector_like U> requires is_lossless_convertible<typename U::ValueType, T>
    DenseVector(const U& other) : n_(other.n()), data_(new T[n_]) {
        for (std::size_t i = 0; i < n_; i++) {
            data_[i] = other[i];
        }

        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    /**
     * @brief Move constructor from same type DenseVector.
     *
     * Does not allocate memory on heap.
     * Emits a move_construct.
     *
     * @param other DenseVector to move from.
     * @note Invalidates 'other' vector and leaves in an empty state.
     */
    DenseVector(DenseVector<T>&& other) noexcept : n_(other.n_), data_(other.data_) {
        other.n_ = 0;
        other.data_ = nullptr;
        Telemetry::emit_move_construct();
    }

    /**
     * @brief Copy assignment operator from same type DenseVector.
     *
     * If this vector is not resized, emits a copy_assign.
     * If this vector is resized, emits a deallocation, allocation, and copy_assign.
     * If this vector is resized, allocates 'other.n * sizeof(T)' bytes of memory.
     *
     * @param other DenseVector to copy from.
     * @return Reference to this vector.
     */
    DenseVector<T>& operator=(const DenseVector<T>& other) {
        if (this != &other) {
            if (n_ != other.n_) {
                n_ = other.n_;
                delete[] data_;
                Telemetry::emit_deallocation();
                data_ = new T[n_];
                Telemetry::emit_allocation();
            }

            std::memcpy(data_, other.data_, n_ * sizeof(T));
            Telemetry::emit_copy_assign();
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator from diff type DenseVector.
     *
     * If this vector is not resized, emits a copy_assign.
     * If this vector is resized, emits a deallocation, allocation, and copy_assign.
     * If this vector is resized, allocates 'other.n * sizeof(T)' bytes of memory.
     *
     * @tparam U Scalar type of other DenseVector.
     * @param other DenseVector to copy from.
     * @return Reference to this vector.
     */
    template<scalar U> requires is_lossless_convertible<U, T>
    DenseVector<T>& operator=(const U& other) {
        if (this->n_ != other.n()) {
            Telemetry::emit_deallocation();
            n_ = other.n();
            delete[] data_;
            data_ = new T[n_];
            Telemetry::emit_allocation();
        }

        std::copy(other.rawData(), other.rawData() + n_, data_);

        Telemetry::emit_copy_assign();
        return *this;
    }

    /**
     * @brief Copy assignment operator from any dense vector like object.
     *
     * If this vector is not resized, emits a copy_assign.
     * If this vector is resized, emits a deallocation, allocation, and copy_assign.
     * If this vector is resized, allocates 'other.n * sizeof(T)' bytes of memory.
     *
     * @tparam U Type that fulfills 'dense_vector_like' concept.
     * @param other Dense vector like object to copy from.
     * @return Reference to this vector
     */
    template<dense_vector_like U> requires is_lossless_convertible<typename U::ValueType, T>
    DenseVector<T>& operator=(const U& other) {
        if (this->n_ != other.n()) {
            Telemetry::emit_deallocation();
            n_ = other.n();
            delete[] data_;
            data_ = new T[n_];
            Telemetry::emit_allocation();
        }

        for (std::size_t i = 0; i < n_; i++) {
            data_[i] = other[i];
        }

        Telemetry::emit_copy_assign();
        return *this;
    }

    /**
     * @brief Move assignment operator from same type DenseVector.
     *
     * Does not allocate memory on heap.
     * Emits a deallocation and move_assign.
     *
     * @param other DenseVector to move from.
     * @return Reference to this vector.
     * @note Invalidates other vector and leaves in a empty state.
     */
    DenseVector<T>& operator=(DenseVector<T>&& other) noexcept {
        if (this != &other) {
            Telemetry::emit_deallocation();
            n_ = other.n_;
            other.n_ = 0;

            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;

            Telemetry::emit_move_assign();
        }

        return *this;
    }

    /**
     * @brief Reshapes the vector to 'n'.
     *
     * Does nothing if specified new size is identical to current.
     * If specified new size is different to current, emits an allocation and deallocation.
     *
     * @param newN Numbers of elements for the reshaped vector to have.
     * @param preserve Whether to preserve data or leave uninitialized.
     *
     * @note When preserve is false, ALL vector elements will be left uninitialized.
     */
    void reshape(const std::size_t newN, const bool preserve) {
        if (newN == n_) {
            return;
        }

        T* newData = new T[newN];
        Telemetry::emit_allocation();

        if (preserve) {
            for (std::size_t i = 0; i < newN; i++) {
                    if (i < n_) {
                        newData[i] = data_[i];
                    }
            }
        }

        n_ = newN;

        delete[] data_;
        Telemetry::emit_deallocation();

        data_ = newData;
    }

    /**
     * @brief Reshapes the vector to 'n'.
     *
     * Does nothing if specified new size is identical to current.
     * If specified new size is different to current, emits an allocation and deallocation.
     *
     * @param newN Number of elements for the reshaped vector.
     * @param preserve Whether to preserve data or leave initialized to value.
     * @param value Value to set all uninitialized elements too.
     *
     * @note When preserve is true, ONLY vector elements not initialized by old data will be initialized to value.
     * @note When preserve is false, ALL vector elements will be left initialized to value.
     */
    void reshape(const std::size_t newN, const bool preserve, const T value) {
        if (newN == n_) {
            return;
        }

        T* newData = new T[newN];
        Telemetry::emit_allocation();

            for (std::size_t i = 0; i < newN; i++) {
                if (i < n_ && preserve) {
                    newData[i] = data_[i];
                }
                else {
                    newData[i] = value;
                }
            }

        n_ = newN;

        delete[] data_;
        Telemetry::emit_deallocation();

        data_ = newData;
    }

    /**
     * @brief Creates a new vector that is an exact copy of this represented as a DenseVector<U>.
     * @tparam U Scalar type of new dense vector.
     * @return Copy of this of type DenseVector<U>.
     * @warning Does not follow standard conversion rules, will convert any type to any type even if it means losing precision.
     */
    template<scalar U>
    DenseVector<U> as_type() const {
        if constexpr (std::is_same_v<U, T>) {
            return *this;
        }
        else if constexpr (is_lossless_convertible<T, U>) {
            return DenseVector<U>(*this);
        }
        else {
            DenseVector<U> result = DenseVector<U>(n(), false);

            for (int i = 0; i < n(); i++) {
                result[i] = static_cast<U>(std::real(data_[i]));
            }

            return result;
        }
    }

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a reference to the element at coordinates (r, c).
     * Checks bounds of provided r and c indices.
     * Does not allocate memory on the heap.
     *
     * @param i Zero-based index of element.
     *
     * @see DenseVector::operator[](const std::size_t i).
     *
     * @return Reference to the element at (i).
     * @note Index must be withing vector bounds.
     * @throws InvalidIndexException If index 'i' is out of bounds (i.e. bigger than n).
     */
    [[nodiscard]] T& at(const std::size_t i) {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access vector at invalid index");
        }

        return data_[i];
    }

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a const reference to the element at coordinates (r, c).
     * Checks bounds of provided r and c indices.
     * Does not allocate memory on the heap.
     *
     * @param i Zero-based index of element.
     *
     * @see DenseVector::operator[](const std::size_t i).
     *
     * @return Const reference to the element at (i).
     * @note Index must be withing vector bounds.
     * @throws InvalidIndexException If index 'i' is out of bounds (i.e. bigger than n).
     */
    [[nodiscard]] const T& at(const std::size_t i) const {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access vector at invalid index");
        }

        return data_[i];
    }

    /**
     * @brief Accesses the element at a provided index.
     *
     * Retrieves a reference to the element at (i).
     * Does not check bounds of provided index.
     * Does not allocate memory on the heap.
     *
     * @param i Zero-based index of element.
     *
     * @see DenseVector::at(const std::size_t i).
     *
     * @return Reference to the element at (i).
     * @note Undefined behavior if index is out of bounds.
     */
    [[nodiscard]] T& operator[](const std::size_t i) {
        return data_[i];
    }

    /**
     * @brief Accesses the element at a provided index.
     *
     * Retrieves a const reference to the element at (i).
     * Does not check bounds of provided index.
     * Does not allocate memory on the heap.
     *
     * @param i Zero-based index of element.
     *
     * @see DenseVector::at(const std::size_t i).
     *
     * @return Const reference to the element at (i).
     * @note Undefined behavior if index is out of bounds.
     */
    [[nodiscard]] const T& operator[](const std::size_t i) const {
        return data_[i];
    }

    /**
     * @return Number of elements in DenseVector.
     */
    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    /**
    * @return Pointer to array containing all vector elements.
    * @note Pointer to array of size n.
    */
    [[nodiscard]] T* rawData() {
        return data_;
    }

    /**
     * @return Const-pointer to array containing all vector elements.
     * @note Const-pointer to array of size n.
     */
    [[nodiscard]] const T* rawData() const {
        return data_;
    }

    /**
     * @brief Destructor for DenseVector.
     * If data is not nullptr, emits a deallocation.
     * Deallocates data array.
     */
    ~DenseVector() {
        if (data_ != nullptr) {
            Telemetry::emit_deallocation();
            delete[] data_;
        }
    }

private:
    // number of elements
    std::size_t n_;

    // data array
    T* data_;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_DENSE_VECTOR
