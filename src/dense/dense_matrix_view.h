#pragma once
#include "dense_matrix.h"

template<scalar T>
struct DenseMatrixView : DenseMatrix<T> {
    const int rows;
    const int columns;
    const int ownerRows;
    
    DenseMatrixView() = delete;

    DenseMatrixView(const DenseMatrix<T>& owner, const int rows, const int columns, const int rowOffset, const int colOffset) : DenseMatrix<T>(rows, columns), rows(rows), columns(columns), ownerRows(owner.rows) {
        this->data = owner.data;
        rowOffset_ = rowOffset;
        colOffset_ = colOffset;
    }

    DenseMatrixView(const DenseMatrixView<T>& other) = delete;
    DenseMatrixView(DenseMatrixView<T>&& other) = delete;

    T& at(const int c, const int r) override {
        return this->data[(c + colOffset_) * ownerRows + (r + rowOffset_)];
    }

    const T& at(const int c, const int r) const override {
        return this->data[(c + colOffset_) * ownerRows + (r + rowOffset_)];
    }

private:
    int rowOffset_ = 0;
    int colOffset_ = 0;
};
