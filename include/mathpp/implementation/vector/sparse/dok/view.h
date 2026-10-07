#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VIEW_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VIEW_H

#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/common/exceptions.h"

#include "vector.h"

#include <cstddef>
#include <ranges>

template<scalar T>
struct DokSparseVectorView {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    DokSparseVectorView() = delete;
    DokSparseVectorView(const DokSparseVectorView<T>& other) = delete;
    DokSparseVectorView(DokSparseVectorView<T>&& other) noexcept = delete;
    DokSparseVectorView<T>& operator=(const DokSparseVectorView<T>& other) = delete;
    DokSparseVectorView<T>& operator=(DokSparseVectorView<T>&& other) noexcept = delete;

    /**
     * @brief Owner constructor.
     *
     * Creates a view of the owner vector of size 'n'.
     * View starts at offset.
     * Does not allocate memory on heap.
     *
     * @param owner DokSparseVector owner containing real data.
     * @param n Number of elements in constructed view.
     * @param offset Zero-based index at which the view starts relative to owner.
     *
     * @note DokSparseVector owner must outlive view.
     */
    DokSparseVectorView(const DokSparseVector<T>& owner, const std::size_t n, const std::size_t offset) : n_(n), offset_(offset), owner_(owner) {}

    /**
     * @warning Modifying owner through view is illegal.
     */
    void set(const std::size_t, const T)  {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot modify owner through view");
    }

    /**
     * @brief Accesses the element at a provided index.
     *
     * Retrieves the element at (i) relative to where the view starts.
     * Implemented by accessing owner at i + offset.
     * Checks bounds of provided index relative to view AND to owner.
     * Does not allocate memory on the heap.
     * O(log(owner.nnz)) time complexity.
     *
     * @param i Zero-based index of element.
     *
     * @throws InvalidIndexException If index is not withing view OR i + offset is not within owner vector.
     * @note Index must be within size of view AND i + offset must be within size of owner vector.
     * @return Element at (i).
     */
    [[nodiscard]] T get(const std::size_t i) const  {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access view at invalid index");
        }

        return owner_.get(i + offset_);
    }

    /**
     * O(owner.nnz) time complexity.
     * @return Number of non-zero elements visible to view.
     */
    [[nodiscard]] std::size_t nnz() const  {
        std::size_t nnz = 0;

        for (const auto& [key, value] : owner_.map()) {
            if (key >= offset_ && key <= offset_ + n_) {
                nnz++;
            }
        }

        return nnz;
    }

    // Type to wrap map of owner of view.
    template<std::ranges::view V>
    struct OwnerMapView : std::ranges::view_interface<OwnerMapView<V>> {
        OwnerMapView() = default;
        explicit OwnerMapView(const DokSparseVectorView<T>& view, V transformView) : view_(view), transformView_(std::move(transformView)) {}

        auto begin() const {
            return std::ranges::begin(transformView_);
        }

        auto end() const {
            return std::ranges::end(transformView_);
        }

        /**
         * @brief Checks if the map view has a nnz element at index 'i'.
         *
         * If it's not in the map, the element at index 'i' is zero.
         * Implemented by checking if the owner map has the element at 'i + offset'.
         * O(1) (O(n) worst case) time complexity.
         *
         * @param i Index of element to check.
         * @return Whether the element at index 'i' is in the map view.
         */
        [[nodiscard]] bool contains(std::size_t i) const {
            if (i >= view_.n()) {
                return false;
            }

            return view_.owner().map().contains(i + view_.offset());
        }

        [[nodiscard]] T at(const std::size_t i) const {
            if (i >= view_.n()) {
                throw InvalidIndexException("Cannot access MapView at invalid index");
            }

            return view_.owner().map().at(i + view_.offset());
        }

        [[nodiscard]] T& at(std::size_t) {
            static_assert(false, "Cannot edit owner map through view");
        }

        [[nodiscard]] T operator[](std::size_t) const {
            static_assert(false, "Cannot edit owner map through view");
        }

        [[nodiscard]] T& operator[](std::size_t) {
            static_assert(false, "Cannot edit owner map through view");
        }

    private:
        const DokSparseVectorView<T>& view_;
        V transformView_;
    };

    auto map() const {
        auto start = owner().map().lower_bound(offset());
        auto end = owner().map().upper_bound(offset() + n());

        // lambda returns i-th nnz in view
        return OwnerMapView(*this, std::ranges::subrange(start, std::prev(end)) | std::views::transform([this](const std::pair<std::size_t, T>& i) -> std::pair<std::size_t, T> {
            return {i.first - offset_, i.second};
        }));
    }

    OwnerMapView<std::ranges::transform_view<std::ranges::subrange<typename std::unordered_map<std::size_t, T>::iterator, typename std::unordered_map<std::size_t, T>::iterator, std::ranges::subrange_kind::sized>, std::function<std::pair<std::size_t, T>(const std::pair<std::size_t, T>&)>>> map() {
        static_assert(false, "Cannot edit owner map through view");
    }

    /**
     * @return Number of elements in DokSparseVectorView.
     */
    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    /**
     * @return Number of elements to offset view by relative to owner vector.
     */
    [[nodiscard]] std::size_t offset() const {
        return offset_;
    }

    /**
     * @return DokSparseVector view is viewing.
     */
    [[nodiscard]] const DokSparseVector<T>& owner() const {
        return owner_;
    }

    ~DokSparseVectorView()  = default;

private:
    // number of elements
    std::size_t n_;
    // offset relative to owner
    const std::size_t offset_;

    // owner dok sparse vector
    const DokSparseVector<T>& owner_;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VIEW_H
