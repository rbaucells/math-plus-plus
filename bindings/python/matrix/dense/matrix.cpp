#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <ranges>
#include <cstddef>
#include <format>
#include <utility>
#include <type_traits>
#include <vector>
#include <variant>
#include <string>

#include "like.h"
#include "matrix.h"
#include "../../main.h"

namespace py = pybind11;

void matrix_dense_matrix_bindings(py::module_& m) {
    py::class_<Py_DenseMatrix, DenseMatrixLikeBase>(m, "DenseMatrix")
        .def(py::init([](const py::dtype dt) -> Py_DenseMatrix {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>);
            });
        }), py::arg("dt"), "Constructs an empty DenseMatrix whose elements are of dtype 'dt'")
        .def(py::init([](const py::dtype dt, const std::size_t rows, const std::size_t columns, const bool fill) -> Py_DenseMatrix {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, rows, columns, fill);
            });
        }), py::arg("dt"), py::arg("rows"), py::arg("columns"), py::arg("fill") = true, "Constructs a DenseMatrix whose elements are of dtype 'dt' of size 'rows'x'columns'. Elements will be set to zero if 'fill' is set, else it will be left uninitialized")
        .def(py::init([](const py::sequence sequence) -> Py_DenseMatrix {
            const auto [dt, et, size, nestedSize] = get_sequence_info_2d(sequence);

            if (et != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseMatrix. 2D sequence of '{}', expected 2D sequence of scalars", to_string(et)));
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
        }), py::arg("sequence"), "Constructs a DenseMatrix from a 2D sequence of numbers. Internal 'dt' is set to the common dtype of the 'sequence'")
        .def(py::init([](const py::array array) -> Py_DenseMatrix {
            const auto [dt, et, size, nestedSize] = get_array_info_2d(array);

            if (et != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseMatrix. 2D array of '{}', expected 2D array of scalars", to_string(et)));
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
        }), py::arg("array"), "Constructs a DenseMatrix from a 2D array of numbers. Internal 'dt' is set to the dtype of the 'array'")
        .def(py::init([](const py::dtype dt, const py::sequence sequence) -> Py_DenseMatrix {
            const auto [sequenceDt, sequenceEt, size, nestedSize] = get_sequence_info_2d(sequence);

            if (sequenceEt != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseMatrix. 2D sequence of '{}', expected 2D sequence of scalars", to_string(sequenceEt)));
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
                        throw py::type_error(std::format("Cannot construct DenseMatrix. Sequence elements of dtype '{}' cannot convert to matrix dtype '{}'", py::cast<std::string>(py::str(sequenceDt)), py::cast<std::string>(py::str(dt))));
                    }
                });
            });
        }), py::arg("dt"), py::arg("sequence"), "Constructs a DenseMatrix from a 2D sequence. Internal 'dt' is set to 'dt'. Elements of 'sequence' must be able to fit in the specified 'dt'")
        .def(py::init([](const py::dtype dt, const py::array array) -> Py_DenseMatrix {
            const auto [arrayDt, arrayEt, size, nestedSize] = get_array_info_2d(array);

            if (arrayEt != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseMatrix. 2D array of '{}', expected 2D array of scalars", to_string(arrayEt)));
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
                        throw py::type_error(std::format("Cannot construct DenseMatrix. Array elements of dtype '{}' cannot convert to matrix dtype '{}'", py::cast<std::string>(py::str(arrayDt)), py::cast<std::string>(py::str(dt))));
                    }
                });
            });
        }), py::arg("dt"), py::arg("array"), "Constructs a DenseMatrix from a 2D array. Internal 'dt' is set to 'dt'. Elements of 'array' must be able to fit in the specified 'dt'")
        .def_static("copy", [](const Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([]<typename T>(const DenseMatrix<T>& otherMat) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, otherMat);
            }, other);
        }, py::arg("other"), "Returns a copy of the 'other' Densematrix")
        .def_static("copy", [](const py::dtype dt, const Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([&]<typename T>(const DenseMatrix<T>& otherMat) -> Py_DenseMatrix {
                return dispatch_dt(dt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<T, U>) {
                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<U>>, otherMat);
                    }
                    else {
                        throw py::type_error(std::format("Cannot copy DenseMatrix. Other DenseMatrix dtype '{}' cannot convert to matrix dtype '{}'", py::cast<std::string>(py::str(py::dtype::of<T>())), py::cast<std::string>(py::str(dt))));
                    }
                });
            }, other);
        }, py::arg("dt"), py::arg("other"), "Returns a copy of the 'other' Densematrix. Copy's dtype is 'dt'. Dtype of 'other' must be able to convert to 'dt'")
        .def_static("copy", [](const PyDenseMatrixLike other) -> Py_DenseMatrix {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error(std::format("Cannot copy DenseMatrix. Got '{}' expected a DenseMatrixLike", py::cast<std::string>(py::str(other))));
            }

            const py::dtype dt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                DenseMatrixLikePyWrapper<T> wrapper = DenseMatrixLikePyWrapper<T>(other);
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
            });
        }, py::arg("other"), "Returns a copy of the 'other' DenseMatrixLike")
        .def_static("copy", [](const py::dtype dt, const PyDenseMatrixLike other) -> Py_DenseMatrix {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error(std::format("Cannot copy DenseMatrix. Got '{}' expected a DenseMatrixLike", py::cast<std::string>(py::str(other))));
            }

            const py::dtype otherDt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseMatrix {
                return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseMatrix {
                    if constexpr (lossless_convertible<U, T>) {
                        DenseMatrixLikePyWrapper<U> wrapper = DenseMatrixLikePyWrapper<U>(other);
                        return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, wrapper);
                    }
                    else {
                        throw py::type_error(std::format("Cannot copy DenseMatrix. Other DenseMatrixLike dtype '{}' cannot convert to matrix dtype '{}'", py::cast<std::string>(py::str(dt)), py::cast<std::string>(py::str(otherDt))));
                    }
                });
            });
        }, py::arg("dt"), py::arg("other"), "Returns a copy of the 'other' DenseMatrixLike. Copy's dtype is 'dt'. Dtype of 'other' must be able to convert to 'dt'")
        .def_static("move", [](Py_DenseMatrix& other) -> Py_DenseMatrix {
            return std::visit([]<typename T>(DenseMatrix<T>& otherMat) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<T>>, std::move(otherMat));
            }, other);
        }, py::arg("other"), "Returns a DenseMatrix constructed by moving from the 'other' matrix. 'other' matrix is left in empty yet valid state. Does not copy memory")
        .def("dtype", [](Py_DenseMatrix& self) -> py::dtype {
            return std::visit([]<typename T>(const DenseMatrix<T>&) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        }, "Returns the dtype that represents the matrix's elements")
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
        }, "Returns the number of columns in the matrix")
        .def("rows", [](Py_DenseMatrix& self) -> std::size_t {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> std::size_t {
                return mat.rows();
            }, self);
        }, "Returns the number of rows in the matrix")
        .def("is_complex", [](Py_DenseMatrix& self) -> bool {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> bool {
                return DenseMatrix<T>::isComplex;
            }, self);
        }, "Returns whether the matrix's elements are complex or real")
        .def("get", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c) -> AnyNumber {
            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> AnyNumber {
                 return py::cast(mat.get(r, c));
             }, self);
        }, py::arg("r"), py::arg("c"), "Returns the element at row 'r' and column 'c'. Checks 'r' and 'c' are within bounds")
        .def("set", [](Py_DenseMatrix& self, const std::size_t r, const std::size_t c, const AnyNumber v) -> void {
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
        }, py::arg("r"), py::arg("c"), py::arg("v"), "Sets the matrix's element at row 'r' and columns 'c' to 'v'. Checks 'r' and c' are within bounds")
        .def("__getitem__", [](Py_DenseMatrix& self, const std::pair<std::size_t, std::size_t>& indices) -> AnyNumber {
            const std::size_t r = indices.first;
            const std::size_t c = indices.second;

            return std::visit([&]<typename T>(const DenseMatrix<T>& mat) -> AnyNumber {
                 return py::cast(mat[r, c]);
             }, self);
        }, py::arg("indices"), "Returns the element in the matrix at 'indices' ([0] = row, [1] = col). Does not check bounds of 'indices'")
        .def("__setitem__", [](Py_DenseMatrix& self, const std::pair<std::size_t, std::size_t>& indices, const AnyNumber v) -> void {
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
        }, py::arg("indices"), py::arg("v"), "Sets the element in the matrix at 'indices' ([0] = row, [1] = col) to 'v'. Does not check bounds of 'indices'")
        .def("reshape", [](Py_DenseMatrix& self, const std::size_t newRows, const std::size_t newColumns, const bool preserve) -> void {
            std::visit([&]<typename T>(DenseMatrix<T>& mat) -> void {
                mat.reshape(newRows, newColumns, preserve);
            }, self);
        }, py::arg("newRows"), py::arg("newColumns"), py::arg("preserve"), "Reshapes the matrix to be 'newRows x newColumns' in size. Leaves elements uninitialized if 'preserve' is false, if true elements is copied over")
        .def("reshape", [](Py_DenseMatrix& self, const std::size_t newRows, const std::size_t newColumns, const bool preserve, const AnyNumber value) -> void {
            const py::dtype dt = get_dtype(value);

            dispatch_dt(dt, [&]<typename T>() -> void {
                std::visit([&]<typename U>(DenseMatrix<U>& mat) -> void {
                    if constexpr (lossless_convertible<T, U>) {
                        mat.reshape(newRows, newColumns, preserve, py::cast<U>(value));
                    }
                    else {
                        throw py::type_error("Cannot reshape with value of non convertible dtype");
                    }
                }, self);
            });
        }, py::arg("newRows"), py::arg("newColumns"), py::arg("preserve"), py::arg("value"), "Reshapes the matrix to be 'newRows x newColumns' in size. Sets elements to 'value' if 'preserve' is false, if true elements is copied over")
        .def("data", [](Py_DenseMatrix& self) -> py::array {
            return std::visit([]<typename T>(DenseMatrix<T>& m) -> py::array {
                size_t total_elements = m.rows() * m.columns();

                py::capsule base(m.data(), [](void* /* p */) {});

                std::vector<size_t> shape = { total_elements };
                std::vector<size_t> strides = { sizeof(T) };

                return py::array_t<T>(shape, strides, m.data(), base);
            }, self);
        }, "Returns a ndarray to represent 'data' pointer inside the DenseMatrix");
}
