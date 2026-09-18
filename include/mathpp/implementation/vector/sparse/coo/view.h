#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_VIEW_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_VIEW_H

template<scalar T>
struct CooSparseVectorView {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    CooSparseVectorView() = delete;
    CooSparseVectorView(const CooSparseVectorView<T>& other) = delete;
    CooSparseVectorView(CooSparseVectorView<T>&& other) noexcept = delete;
    CooSparseVectorView<T>& operator=(const CooSparseVectorView<T>& other) = delete;
    CooSparseVectorView<T>& operator=(CooSparseVectorView<T>&& other) noexcept = delete;

    /**
     * @brief Owner constructor.
     *
     * Creates a view of the owner vector of size 'n'.
     * View starts at offset.
     * Does not allocate memory on heap.
     *
     * @param owner CooSparseVector owner containing real data.
     * @param n Number of elements in constructed view.
     * @param offset Zero-based index at which the view starts relative to owner.
     *
     * @note CooSparseVector owner must outlive view.
     */
    CooSparseVectorView(const CooSparseVector<T>& owner, const std::size_t n, const std::size_t offset) : n_(n), offset_(offset), owner_(owner) {}

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
     * O(owner.nnz) time complexity.
     *
     * @param i Zero-based index of element.
     *
     * @throws InvalidIndexException If index is not withing view OR i + offset is not within owner vector.
     * @note Index must be within size of view AND i + offset must be within size of owner vector.
     * @return Element at (r, c).
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

        for (std::size_t i = 0; i < owner_.nnz(); i++) {
            const std::size_t curIndex = owner_.rawIndices()[i];

            if (curIndex >= offset_ && curIndex < offset_ + n_) {
                nnz++;
            }
        }

        return nnz;
    }

    /**
     * @brief What the view 'sees' of the owners indices array.
     *
     * O(owner.nnz) time complexity.
     * Implemented by accessing the owners indices at a starting offset + i and subtracting offset from that.
     *
     * @return Lazy evaluated container that constructs what the view 'sees' of the owners indices array.
     * @info Coo Sparse Vector owner must not change indices array while this indices 'view' is alive.
     */
    [[nodiscard]] auto indices() const {
        std::size_t nnz = 0;
        std::size_t whereStart = 0;

        for (std::size_t i = 0; i < owner_.nnz(); i++) {
            const std::size_t curIndex = owner_.rawIndices()[i];

            if (curIndex >= offset_ && curIndex < offset_ + n_) {
                if (nnz == 0) {
                    whereStart = i;
                }

                nnz++;
            }
        }

        return std::views::iota(0ul, nnz) | std::views::transform([whereStart, this](const std::size_t i) -> std::size_t {
            return owner().indices()[i + whereStart] - offset_;
        });
    }

    /**
     * @brief What the view 'sees' of the owners values array.
     *
     * O(owner.nnz) time complexity.
     * Implemented by accessing the owners values at a starting offset + i.
     *
     * @return Lazy evaluated container that constructs what the view 'sees' of the owners values array.
     * @info Coo Sparse Vector owner must not change values or indices array while this values 'view' is alive.
     */
    [[nodiscard]] auto values() const {
        std::size_t nnz = 0;
        std::size_t whereStart = 0;

        for (std::size_t i = 0; i < owner_.nnz(); i++) {
            const std::size_t curIndex = owner_.rawIndices()[i];

            if (curIndex >= offset_ && curIndex < offset_ + n_) {
                if (nnz == 0) {
                    whereStart = i;
                }

                nnz++;
            }
        }

        return std::views::iota(0ul, nnz) | std::views::transform([whereStart, this](const std::size_t i) -> T {
            return owner().values()[i + whereStart];
        });
    }

    /**
     * @return Number of elements in CooSparseVectorView.
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
     * @return CooSparseVector view is viewing.
     */
    [[nodiscard]] const CooSparseVector<T>& owner() const {
        return owner_;
    }

    ~CooSparseVectorView()  = default;

private:
    // number of elements
    std::size_t n_;
    // offset relative to owner
    const std::size_t offset_;

    // owner coo sparse vector
    const CooSparseVector<T>& owner_;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_VIEW_H
