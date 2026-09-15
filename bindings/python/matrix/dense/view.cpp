#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <memory>
#include <variant>
#include <ranges>
#include <cstddef>
#include <format>
#include <utility>

#include "like.h"
#include "view.h"
#include "matrix.h"

#include "../../main.h"

void matrix_dense_view_bindings(py::module_& m) {
    py::class_<Py_DenseMatrixView, DenseMatrixLikeBase>(m, "DenseMatrixView")
        .def(py::init([](const Py_DenseMatrix& owner, const std::size_t rows, const std::size_t cols, const std::size_t rowOffset, const std::size_t colOffset) -> Py_DenseMatrixView {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> Py_DenseMatrixView {
                return Py_DenseMatrixView(std::in_place_type<std::shared_ptr<const DenseMatrixView<T>>>, std::make_shared<DenseMatrixView<T>>(mat, rows, cols, rowOffset, colOffset));
            }, owner);
        }), py::arg("owner"), py::arg("rows"), py::arg("columns"), py::arg("row_offset"), py::arg("col_offset"), py::keep_alive<1, 2>(), "Constructs a DenseMatrixView on another DenseMatrix with a specified 'rows'x'columns' size with a 'rowOffset' and 'colOffset' relative to the DenseMatrix parent")
        .def("dtype", [](Py_DenseMatrixView& self) -> py::dtype {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        }, "Returns the dtype that represents the views's elements")
        .def("is_complex", [](Py_DenseMatrixView& self) -> bool {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> bool {
                return DenseMatrixView<T>::isComplex;
            }, self);
        }, "Returns whether the views's elements are complex or real")
        .def("rows", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->rows();
            }, self);
        }, "Returns the number of rows in the view")
        .def("columns", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->columns();
            }, self);
        }, "Returns the number of columns in the view")
        .def("row_offset", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->rowOffset();
            }, self);
        }, "Returns the number of rows the view is offset from its parent")
        .def("col_offset", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->colOffset();
            }, self);
        }, "Returns the number of columns the view is offset from its parent")
        .def("get", [](Py_DenseMatrixView& self, const std::size_t r, const std::size_t c) -> AnyNumber {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> AnyNumber {
                return py::cast(v->get(r, c));
            }, self);
        }, py::arg("r"), py::arg("c"), "Returns the element at row 'r' and column 'c' of the view. Checks 'r' and 'c' are within bounds of the view and of the parent")
        .def("set", [](Py_DenseMatrixView&, const std::size_t, const std::size_t, AnyNumber) -> void {
            throw py::type_error("Cannot set on dense matrix view");
        }, py::arg("r"), py::arg("c"), py::arg("v"), "Sets the views's element at row 'r' and columns 'c' to 'v'. Checks 'r' and c' are within bounds of the view and parent")
        .def("__getitem__", [](Py_DenseMatrixView& self, const std::pair<std::size_t, std::size_t>& indices) -> AnyNumber {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> AnyNumber {
                return py::cast(v->operator[](indices.first, indices.second));
            }, self);
        }, py::arg("indices"), "Returns the element in the view at 'indices' ([0] = row, [1] = col). Does not check bounds of 'indices'")
        .def("__setitem__", [](Py_DenseMatrixView&, const std::pair<std::size_t, std::size_t>&, AnyNumber) -> void {
            throw py::type_error("Cannot set on dense matrix view");
        }, py::arg("indices"), py::arg("v"), "Sets the element in the view at 'indices' ([0] = row, [1] = col) to 'v'. Does not check bounds of 'indices'");
}
