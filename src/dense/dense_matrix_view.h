#pragma once
#include "dense_matrix.h"

template<int ROWS, int COLUMNS, int OWNER_ROWS, scalar T>
struct DenseMatrixView : DenseMatrix<ROWS, COLUMNS, T> {
    DenseMatrixView() = delete;

    template<int OWNER_COLUMNS>
    DenseMatrixView(const DenseMatrix<OWNER_ROWS, OWNER_COLUMNS, T>& owner, const int rowOffset, const int colOffset) {
        this->data = &owner.data[0][0];
        rowOffset_ = rowOffset;
        colOffset_ = colOffset;
    }

    DenseMatrixView(const DenseMatrixView<ROWS, COLUMNS, OWNER_ROWS, T>& other) = delete;

    DenseMatrixView(DenseMatrixView<ROWS, COLUMNS, OWNER_ROWS, T>&& other) noexcept {
        this->data = other.data;
        other.data = nullptr;
    }

    T& at(const int c, const int r) override {
        return this->data[(c + colOffset_) * OWNER_ROWS + (r + rowOffset_)];
    }

    const T& at(const int c, const int r) const override {
        return this->data[(c + colOffset_) * OWNER_ROWS + (r + rowOffset_)];
    }

private:
    int rowOffset_ = 0;
    int colOffset_ = 0;
};
