#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <memory>
#include <ranges>
#include <cstddef>
#include <ranges>

#include "like.h"
#include "view.h"
#include "matrix.h"

#include "../../main.h"

void dense_matrix_view_bindings(py::module_& m) {
    py::class_<Py_DenseMatrixView, DenseMatrixLikeBase>(m, "DenseMatrixView")
        .def(py::init([](const Py_DenseMatrix& owner, const std::size_t rows, const std::size_t cols, const std::size_t rowOffset, const std::size_t colOffset) -> Py_DenseMatrixView {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> Py_DenseMatrixView {
                return Py_DenseMatrixView(std::in_place_type<std::shared_ptr<const DenseMatrixView<T>>>, std::make_shared<DenseMatrixView<T>>(mat, rows, cols, rowOffset, colOffset));
            }, owner);
        }), py::arg("owner"), py::arg("rows"), py::arg("columns"), py::arg("row_offset"), py::arg("col_offset"), py::keep_alive<1, 2>())
        .def("dtype", [](Py_DenseMatrixView& self) -> py::dtype {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        })
        .def("is_complex", [](Py_DenseMatrixView& self) -> bool {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> bool {
                return DenseMatrixView<T>::isComplex;
            }, self);
        })
        .def("rows", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->rows();
            }, self);
        })
        .def("columns", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->columns();
            }, self);
        })
        .def("row_offset", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->rowOffset();
            }, self);
        })
        .def("col_offset", [](Py_DenseMatrixView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> std::size_t {
                return v->colOffset();
            }, self);
        })
        .def("get", [](Py_DenseMatrixView& self, const std::size_t r, const std::size_t c) -> py::object {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> py::object {
                return py::cast(v->get(r, c));
            }, self);
        }, py::arg("r"), py::arg("c"))
        .def("set", [](Py_DenseMatrixView&, const std::size_t, const std::size_t, py::handle) -> void {
            throw py::type_error("Cannot set on dense matrix view");
        })
        .def("__getitem__", [](Py_DenseMatrixView& self, const std::pair<std::size_t, std::size_t>& indices) -> py::object {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseMatrixView<T>>& v) -> py::object {
                return py::cast(v->operator[](indices.first, indices.second));
            }, self);
        }, py::arg("indices"))
        .def("__setitem__", [](Py_DenseMatrixView&, const std::pair<std::size_t, std::size_t>&, py::handle) -> void {
            throw py::type_error("Cannot set on dense matrix view");
        });
}
