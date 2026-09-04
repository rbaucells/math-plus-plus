#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <ranges>
#include <cstddef>
#include <ranges>

#include "like.h"
#include "matrix.h"
#include "../../main.h"

namespace py = pybind11;

void dense_matrix_bindings(py::module_& m) {
    py::class_<Py_DenseMatrix, DenseMatrixLikeBase>(m, "DenseMatrix")
        .def(py::init([](const py::dtype dt) -> Py_DenseMatrix {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>);
            });
        }), py::arg("dt"))
        .def(py::init([](const py::dtype dt, const std::size_t rows, const std::size_t columns, const bool fill) -> Py_DenseMatrix {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, rows, columns, fill);
            });
        }), py::arg("dt"), py::arg("rows"), py::arg("columns"), py::arg("fill") = true)
        .def(py::init([](const py::sequence sequence) -> Py_DenseMatrix {
            const auto [dt, et, size, nestedSize] = get_sequence_info_2d(sequence);

            if (et != EType::scalar) {
                throw py::type_error("Cannot construct dense matrix from 2d sequence of etype: " + to_string(et) + " (should be scalar)");
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t r) {
                    const py::sequence inner = sequence[r];

                    return std::views::iota(0u, nestedSize) | std::views::transform([inner](const std::size_t c) -> T {
                        return py::cast<T>(inner[c]);
                    });
                });

                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
            });
        }), py::arg("sequence"))
        .def(py::init([](const py::array array) -> Py_DenseMatrix {
            const auto [dt, et, size, nestedSize] = get_array_info_2d(array);

            if (et != EType::scalar) {
                throw py::type_error("Cannot construct dense matrix from 2d array of etype: " + to_string(et) + " (should be scalar)");
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                py::detail::unchecked_reference<T, 2> unchecked = array.unchecked<T, 2>();

                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t r) {
                    return std::views::iota(0u, nestedSize) | std::views::transform([&](const std::size_t c) -> T {
                        return unchecked(r, c);
                    });
                });

                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
            });
        }), py::arg("array"))
        .def(py::init([](const py::dtype dt, const py::sequence sequence) -> Py_DenseMatrix {
            const auto [sequenceDt, sequenceEt, size, nestedSize] = get_sequence_info_2d(sequence);

            if (sequenceEt != EType::scalar) {
                throw py::type_error("Cannot construct dense matrix from 2d sequence of etype: " + to_string(sequenceEt) + " (should be scalar)");
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return dispatch_dt(sequenceDt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t r) {
                            const py::sequence inner = sequence[r];

                            return std::views::iota(0u, nestedSize) | std::views::transform([inner](const std::size_t c) -> T {
                                return py::cast<T>(inner[c]);
                            });
                        });

                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
                    }
                    else {
                        throw py::type_error("Cannot convert sequence dt to specified dt while constructing dense matrix from 2d sequence");
                    }
                });
            });
        }), py::arg("dt"), py::arg("sequence"))
        .def(py::init([](const py::dtype dt, const py::array array) -> Py_DenseMatrix {
            const auto [arrayDt, arrayEt, size, nestedSize] = get_array_info_2d(array);

            if (arrayEt != EType::scalar) {
                throw py::type_error();
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return dispatch_dt(arrayDt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        py::detail::unchecked_reference<U, 2> unchecked = array.unchecked<U, 2>();

                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t r) {
                            return std::views::iota(0u, nestedSize) | std::views::transform([&](const std::size_t c) -> T {
                                return static_cast<T>(unchecked(r, c));
                            });
                        });

                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
                    }
                    else {
                        throw py::type_error("Cannot convert array dt to specified dt while constructing dense matrix from 2d array");
                    }
                });
            });
        }), py::arg("dt"), py::arg("array"))
        .def_static("copy", [](const Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([]<typename T>(const DenseMatrix<T>& otherMat) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, otherMat);
            }, other);
        }, py::arg("other"))
        .def_static("copy", [](const py::dtype dt, const Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([&]<typename T>(const DenseMatrix<T>& otherMat) -> Py_DenseMatrix {
                return dispatch_dt(dt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<T, U>) {
                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<U>>, otherMat);
                    }
                    else {
                        throw py::type_error("Cannot copy construct a dense matrix from another with non convertible type");
                    }
                });
            }, other);
        }, py::arg("dt"), py::arg("other"))
        .def_static("copy", [](const py::object other) -> Py_DenseMatrix {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error("Cannot copy construct dense matrix from object that doesn't derive from DenseMatrixLike");
            }

            const py::dtype dt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                DenseMatrixLikePyWrapper<T> wrapper = DenseMatrixLikePyWrapper<T>(other);
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
            });
        }, py::arg("other"))
        .def_static("copy", [](const py::dtype dt, const py::object other) -> Py_DenseMatrix {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error("Cannot copy construct dense matrix from object that doesn't derive from DenseMatrixLike");
            }

            const py::dtype otherDt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        DenseMatrixLikePyWrapper<U> wrapper = DenseMatrixLikePyWrapper<U>(other);
                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
                    }
                    else {
                        throw py::type_error("Cannot copy construct a dense matrix from dense matrix like with non convertible type");
                    }
                });
            });
        }, py::arg("dt"), py::arg("other"))
        .def_static("move", [](Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([]<typename T>(DenseMatrix<T>& otherMat) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, std::move(otherMat));
            }, other);
        }, py::arg("other"))
        .def("dtype", [](Py_DenseMatrix& self) -> py::dtype {
            return std::visit([]<typename T>(const DenseMatrix<T>&) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        })
        .def("as_type", [](Py_DenseMatrix& self, const py::dtype dt) -> Py_DenseMatrix {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> Py_DenseMatrix {
                return dispatch_dt(dt, [&]<scalar U>() -> Py_DenseMatrix {
                    return Py_DenseMatrix(std::in_place_type<DenseMatrix<U>>, mat.template as_type<U>());
                });
            }, self);
        }, py::arg("dt"))
        .def("columns", [](Py_DenseMatrix& self) -> std::size_t {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> std::size_t {
                return mat.columns();
            }, self);
        })
        .def("rows", [](Py_DenseMatrix& self) -> std::size_t {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> std::size_t {
                return mat.rows();
            }, self);
        })
        .def("is_complex", [](Py_DenseMatrix& self) -> bool {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> bool {
                return DenseMatrix<T>::isComplex;
            }, self);
        })
        .def("get", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c) -> py::object {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> py::object {
                 return py::cast(mat.get(r, c));
             }, self);
        }, py::arg("r"), py::arg("c"))
        .def("set", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c, const py::object v) -> void {
            const py::dtype dt = get_dtype(v);

            dispatch_dt(dt, [&]<typename T>() -> void {
                return std::visit([&]<typename U>(DenseMatrix<U>& mat) -> void {
                    if constexpr (std::is_convertible_v<T, U>) {
                        mat.set(r, c, py::cast<U>(v));
                    }
                    else {
                        throw py::type_error("Cannot assign to DenseMatrix element with incomatible arg type");
                    }
                }, self);
            });
        }, py::arg("r"), py::arg("c"), py::arg("v"))
        .def("__getitem__", [](Py_DenseMatrix& self, const std::pair<std::size_t, std::size_t>& indices) -> py::object {
            const std::size_t r = indices.first;
            const std::size_t c = indices.second;

            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> py::object {
                 return py::cast(mat[r, c]);
             }, self);
        }, py::arg("indices"))
        .def("__setitem__", [](Py_DenseMatrix& self, const std::pair<std::size_t, std::size_t>& indices, const py::object v) -> void {
            const std::size_t r = indices.first;
            const std::size_t c = indices.second;

            const py::dtype dt = get_dtype(v);

            dispatch_dt(dt, [&]<typename T>() -> void {
                std::visit([&]<typename U>(DenseMatrix<U>& mat) -> void {
                    if constexpr (std::is_convertible_v<T, U>) {
                        mat[r, c] = py::cast<U>(v);
                    }
                    else {
                        throw py::type_error("Cannot assign to matrix element with non convertible dt");
                    }
                }, self);
            });
        }, py::arg("indices"), py::arg("v"))
        .def("reshape", [](Py_DenseMatrix& self, const std::size_t newRows, const std::size_t newColumns, const bool preserve) {
            return std::visit([&]<typename T>(DenseMatrix<T>& mat) {
                mat.reshape(newRows, newColumns, preserve);
            }, self);
        }, py::arg("newRows"), py::arg("newColumns"), py::arg("preserve"))
        .def("reshape", [](Py_DenseMatrix& self, const std::size_t newRows, const std::size_t newColumns, const bool preserve, const py::object value) {
            const py::dtype dt = get_dtype(value);

            return dispatch_dt(dt, [&]<typename T>() {
                return std::visit([&]<typename U>(DenseMatrix<U>& mat) {
                    if constexpr (lossless_convertible<T, U>) {
                        mat.reshape(newRows, newColumns, preserve, py::cast<U>(value));
                    }
                    else {
                        throw py::type_error("Cannot reshape with value of non convertible dtype");
                    }
                }, self);
            });
        }, py::arg("newRows"), py::arg("newColumns"), py::arg("preserve"), py::arg("value"));
}
