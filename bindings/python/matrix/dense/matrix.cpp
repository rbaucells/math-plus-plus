#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "mathpp/implementation/matrix/dense/matrix.h"
#include "mathpp/implementation/common/traits.h"
#include "../../main.h"
#include "matrix.h"

#include "like.h"

#include <ranges>

void dense_matrix_bindings(py::module_& m) {
    py::class_<Py_DenseMatrix, DenseMatrixLikeBase>(m, "DenseMatrix")
        .def(py::init([](const py::dtype& dt) -> Py_DenseMatrix {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>);
            });
        }), py::arg("dt"))
        .def(py::init([](const py::dtype& dt, const std::size_t rows, const std::size_t columns, const bool fill) -> Py_DenseMatrix {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, rows, columns, fill);
            });
        }), py::arg("dt"), py::arg("rows"), py::arg("columns"), py::arg("fill") = true)
        .def(py::init([](const py::sequence& sequence) -> Py_DenseMatrix {
            const auto [dt, et, size, nestedSize] = get_sequence_info_2d(sequence);

            if (et != EType::scalar) {
                throw py::type_error();
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t r) {
                    const py::object inner = sequence[r];

                    if (!py::isinstance<py::sequence>(inner)) {
                        throw py::type_error("nested sequence to initialize matrix must be nested sequences");
                    }

                    const py::sequence innerSequence = inner;

                    return std::views::iota(0u, nestedSize) | std::views::transform([innerSequence](const std::size_t c) -> T {
                        return py::cast<T>(innerSequence[c]);
                    });
                });

                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
            });
        }), py::arg("rows"))
        .def(py::init([](const py::array& array) -> Py_DenseMatrix {
            const auto [dt, et, size, nestedSize] = get_array_info_2d(array);

            if (et != EType::scalar) {
                throw py::type_error();
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
        }), py::arg("rows"))
        .def(py::init([](const py::dtype& dt, const py::sequence& sequence) -> Py_DenseMatrix {
            const auto [sequenceDt, sequenceEt, size, nestedSize] = get_sequence_info_2d(sequence);

            if (sequenceEt != EType::scalar) {
                throw py::type_error();
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return dispatch_dt(sequenceDt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t r) {
                            const py::object inner = sequence[r];

                            if (!py::isinstance<py::sequence>(inner)) {
                                throw py::type_error("nested sequence to initialize matrix must be nested sequences");
                            }

                            const py::sequence innerSequence = inner;

                            return std::views::iota(0u, nestedSize) | std::views::transform([innerSequence](const std::size_t c) -> T {
                                return py::cast<T>(innerSequence[c]);
                            });
                        });

                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
                    }
                    else {
                        throw py::type_error();
                    }
                });
            });
        }), py::arg("dt"), py::arg("rows"))
        .def(py::init([](const py::dtype& dt, const py::array& array) -> Py_DenseMatrix {
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
                        throw py::type_error();
                    }
                });
            });
        }), py::arg("dt"), py::arg("rows"))
        .def_static("copy", [](const Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([](const auto& otherMat) -> Py_DenseMatrix {
                using U = std::decay_t<decltype(otherMat)>::ValueType;
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<U>>, otherMat);
            }, other);
        }, py::arg("other"))
        .def_static("copy", [](const py::dtype& dt, const Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([&](const auto& otherMat) -> Py_DenseMatrix {
                using U = std::decay_t<decltype(otherMat)>::ValueType;

                return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, otherMat);
                    }
                    else {
                        throw py::type_error("Cannot copy construct a Dense Matrix from another with non convertible type");
                    }
                });
            }, other);
        }, py::arg("dt"), py::arg("other"))
        .def_static("copy", [](const py::object& other) -> Py_DenseMatrix {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error("Cannot copy construct from object that doesn't derive from DenseMatrixLike");
            }

            const py::dtype dt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                DenseMatrixLikePyWrapper<T> wrapper = DenseMatrixLikePyWrapper<T>(other);
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
            });
        }, py::arg("other"))
        .def_static("copy", [](const py::dtype& dt, const py::object& other) -> Py_DenseMatrix {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error("Cannot copy construct from object that doesn't derive from DenseMatrixLike");
            }

            const py::dtype otherDt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        DenseMatrixLikePyWrapper<U> wrapper = DenseMatrixLikePyWrapper<U>(other);
                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
                    }
                    else {
                        throw py::type_error("Cannot copy construct a Dense Matrix from dense matrix like with non convertible type");
                    }
                });
            });
        }, py::arg("dt"), py::arg("other"))
        .def_static("move", [](Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([](auto& otherMat) -> Py_DenseMatrix {
                using U = std::decay_t<decltype(otherMat)>::ValueType;
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<U>>, std::move(otherMat));
            }, other);
        }, py::arg("other"))
        .def("dtype", [](Py_DenseMatrix& self) -> py::dtype {
            return std::visit([](const auto& mat) -> py::dtype {
                using T = std::decay_t<decltype(mat)>::ValueType;
                return py::dtype::of<T>();
            }, self);
        })
        .def("as_type", [](Py_DenseMatrix& self, const py::dtype& dt) -> Py_DenseMatrix {
            return std::visit([&](const auto& mat) -> Py_DenseMatrix {
                return dispatch_dt(dt, [&]<scalar T>() -> Py_DenseMatrix {
                    // TODO: This likely moves the constructed rvalue into the variant
                    return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, mat.template as_type<T>());
                });
            }, self);
        }, py::arg("dt"))
        .def("columns", [](Py_DenseMatrix& self) -> std::size_t {
            return std::visit([&](const auto& mat) -> std::size_t {
                return mat.columns();
            }, self);
        })
        .def("rows", [](Py_DenseMatrix& self) -> std::size_t {
            return std::visit([&](const auto& mat) -> std::size_t {
                return mat.rows();
            }, self);
        })
        .def("is_complex", [](Py_DenseMatrix& self) -> bool {
            return std::visit([&](const auto& mat) -> bool {
                using U = std::decay_t<decltype(mat)>;
                return U::isComplex;
            }, self);
        })
        .def("get", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c) -> py::object {
            return std::visit([&](const auto& mat) -> py::object {
                 return py::cast(mat.get(r, c));
             }, self);
        }, py::arg("c"), py::arg("r"))
        .def("set", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c, const py::object& v) -> void {
            const py::dtype dt = get_dtype(v);

            dispatch_dt(dt, [&]<typename T>() -> void {
                return std::visit([&](auto& mat) -> void {
                    using U = std::decay_t<decltype(mat)>::ValueType;

                    if (std::is_convertible_v<T, U>) {
                        mat.set(r, c, py::cast<U>(v));
                    }
                    else {
                        throw py::type_error("Cannot assign to DenseMatrix element with incomatible arg type");
                    }
                }, self);
            });
        }, py::arg("c"), py::arg("r"), py::arg("v"))
        .def("__getitem__", [](Py_DenseMatrix& self, const std::pair<std::size_t, std::size_t>& indices) -> py::object {
            const std::size_t r = indices.first;
            const std::size_t c = indices.second;

            return std::visit([&](const auto& mat) -> py::object {
                 return py::cast(mat[r, c]);
             }, self);
        }, py::arg("indices"))
        .def("__setitem__", [](Py_DenseMatrix& self, const std::pair<std::size_t, std::size_t>& indices, const py::object& v) -> void {
            const std::size_t r = indices.first;
            const std::size_t c = indices.second;

            const py::dtype dt = get_dtype(v);

            dispatch_dt(dt, [&]<typename T>() -> void {
                std::visit([&](auto& mat) -> void {
                    using U = std::decay_t<decltype(mat)>::ValueType;

                    if constexpr (std::is_convertible_v<T, U>) {
                        mat[r, c] = py::cast<T>(v);
                    }
                    else {
                        throw py::type_error("Cannot assign to matrix element with non convertible dt");
                    }
                }, self);
            });
        }, py::arg("indices"), py::arg("v"))
        .def("reshape", [](Py_DenseMatrix& self, const std::size_t newRows, const std::size_t newColumns, const bool preserve) {
            return std::visit([&](auto& mat) {
                mat.reshape(newRows, newColumns, preserve);
            }, self);
        }, py::arg("newRows"), py::arg("newColumns"), py::arg("preserve"))
        .def("reshape", [](Py_DenseMatrix& self, const std::size_t newRows, const std::size_t newColumns, const bool preserve, const py::object& value) {
            const py::dtype dt = get_dtype(value);

            return dispatch_dt(dt, [&]<typename T>() {
                return std::visit([&](auto& mat) {
                    using U = std::decay_t<decltype(mat)>::ValueType;

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
