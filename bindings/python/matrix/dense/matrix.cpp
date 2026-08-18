#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "mathpp/implementation/matrix/dense/matrix.h"
#include "../../main.h"
#include "matrix.h"

#include "like.h"

void dense_matrix_bindings(py::module_& m) {
    py::class_<Py_DenseMatrix, DenseMatrixLikeBase>(m, "DenseMatrix")
        .def(py::init([](const py::dtype& dt) {
            return dispatch_dt(dt, [&]<typename T>(){
                return Py_DenseMatrix(DenseMatrix<T>());
            });
        }), py::arg("dt"))
        .def(py::init([](const py::dtype& dt, const std::size_t rows, const std::size_t columns, const bool fill) {
            return dispatch_dt(dt, [&]<typename T>(){
                return Py_DenseMatrix(DenseMatrix<T>(rows, columns, fill));
            });
        }), py::arg("dt"), py::arg("rows"), py::arg("columns"), py::arg("fill") = true)
        .def(py::init([](const Py_DenseMatrix& other) {
            return std::visit([](const auto& otherMat) {
                using U = std::decay_t<decltype(otherMat)>::ValueType;

                return Py_DenseMatrix(DenseMatrix<U>(otherMat));
            }, other.storage);
        }), py::arg("other"))
        .def(py::init([](const py::dtype& dt, const Py_DenseMatrix& other) {
            return std::visit([&](const auto& otherMat) {
                using U = std::decay_t<decltype(otherMat)>::ValueType;

                return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        return Py_DenseMatrix(DenseMatrix<T>(otherMat));
                    }
                    else {
                        throw py::type_error("Cannot copy construct a Dense Matrix from another with non convertible type");
                    }
                });
            }, other.storage);
        }), py::arg("dt"), py::arg("other"))
        .def("dtype", [](Py_DenseMatrix& self) -> py::dtype {
            return std::visit([](const auto& mat) {
                using T = std::decay_t<decltype(mat)>::ValueType;

                return py::dtype::of<T>();
            }, self.storage);
        })
        .def("as_type", [](Py_DenseMatrix& self, const py::dtype& dt) {
            return std::visit([&](const auto& mat) {
                return dispatch_dt(dt, [&]<scalar T>(){
                    return py::cast(mat.template as_type<T>());
                });
            }, self.storage);
        }, py::arg("dt"))
        .def("columns", [](Py_DenseMatrix& self) -> std::size_t {
            return std::visit([&](const auto& mat) {
                return mat.columns();
            }, self.storage);
        })
        .def("rows", [](Py_DenseMatrix& self) -> std::size_t {
            return std::visit([&](const auto& mat) {
                return mat.rows();
            }, self.storage);
        })
        .def("is_complex", [](Py_DenseMatrix& self) -> bool {
            return std::visit([&](const auto& mat) {
                using U = std::decay_t<decltype(mat)>;
                return U::isComplex;
            }, self.storage);
        })
        .def("at", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c) -> py::object {
            return std::visit([&](const auto& mat) {
                 return py::cast(mat.at(r, c));
             }, self.storage);
        }, py::arg("c"), py::arg("r"))
        .def("__getitem__", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c) -> py::object {
            return std::visit([&](const auto& mat) {
                 return py::cast(mat[r, c]);
             }, self.storage);
        }, py::arg("c"), py::arg("r"))
        .def("__setitem__", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c, const py::object v) {
            const py::dtype dt = get_common_dtype(v);

            dispatch_dt(dt, [&]<typename T>(){
                std::visit([&](auto& mat) {
                    using U = std::decay_t<decltype(mat)>::ValueType;

                    if constexpr (std::is_convertible_v<T, U>) {
                        mat[r, c] = py::cast<T>(v);
                    }
                    else {
                        throw py::type_error("Cannot assign to matrix element with non convertible dt");
                    }
                }, self.storage);
            });
        }, py::arg("c"), py::arg("r"), py::arg("v"));;
}
