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
#include "vector.h"
#include "../../main.h"

namespace py = pybind11;

void dense_vector_bindings(py::module_& m) {
    py::class_<Py_DenseVector, DenseVectorLikeBase>(m, "DenseVector")
        .def(py::init([](const py::dtype dt) -> Py_DenseVector {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<T>>);
            });
        }), py::arg("dt"), "Constructs an empty DenseVector whose elements are of dtype 'dt'")
        .def(py::init([](const py::dtype dt, const std::size_t n, const bool fill) -> Py_DenseVector {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, n, fill);
            });
        }), py::arg("dt"), py::arg("n"), py::arg("fill") = true, "Constructs a DenseVector whose elements are of dtype 'dt' of size 'n'. Elements will be set to zero if 'fill' is set, else it will be left uninitialized")
        .def(py::init([](const py::sequence sequence) -> Py_DenseVector {
            const auto [dt, et, size] = get_sequence_info(sequence);

            if (et != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseVector. Sequence of '{}', expected sequence of scalars", to_string(et)));
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                    return py::cast<T>(sequence[i]);
                });

                return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
            });
        }), py::arg("sequence"), "Constructs a DenseVector from a sequence of numbers. Internal 'dt' is set to the common dtype of the 'sequence'")
        .def(py::init([](const py::array array) -> Py_DenseVector {
            const auto [dt, et, size] = get_array_info(array);

            if (et != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseVector. Array of '{}', expected array of scalars", to_string(et)));
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                py::detail::unchecked_reference<T, 1> unchecked = array.unchecked<T, 1>();

                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                    return unchecked(i);
                });

                return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
            });
        }), py::arg("array"), "Constructs a DenseVector from an array of numbers. Internal 'dt' is set to the dtype of the 'array'")
        .def(py::init([](const py::dtype dt, const py::sequence sequence) -> Py_DenseVector {
            const auto [sequenceDt, sequenceEt, size] = get_sequence_info(sequence);

            if (sequenceEt != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseVector. Sequence of '{}', expected sequence of scalars", to_string(sequenceEt)));
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                return dispatch_dt(sequenceDt, [&]<typename U>() -> Py_DenseVector {
                    if constexpr (lossless_convertible<U, T>) {
                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                            return py::cast<T>(sequence[i]);
                        });

                        return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
                    }
                    else {
                        throw py::type_error(std::format("Cannot construct DenseVector. Sequence elements of dtype '{}' cannot convert to vector dtype '{}'", py::cast<std::string>(py::str(sequenceDt)), py::cast<std::string>(py::str(dt))));
                    }
                });
            });
        }), py::arg("dt"), py::arg("sequence"), "Constructs a DenseVector from a sequence. Internal 'dt' is set to 'dt'. Elements of 'sequence' must be able to fit in the specified 'dt'")
        .def(py::init([](const py::dtype dt, const py::array array) -> Py_DenseVector {
            const auto [arrayDt, arrayEt, size] = get_array_info(array);

            if (arrayEt != EType::scalar) {
                throw py::type_error(std::format("Cannot construct DenseVector. Array of '{}', expected array of scalars", to_string(arrayEt)));
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                return dispatch_dt(arrayDt, [&]<typename U>() -> Py_DenseVector {
                    if constexpr (lossless_convertible<U, T>) {
                        py::detail::unchecked_reference<U, 1> unchecked = array.unchecked<U, 1>();

                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) {
                            return static_cast<T>(unchecked(i));
                        });

                        return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
                    }
                    else {
                        throw py::type_error(std::format("Cannot construct DenseVector. Array elements of dtype '{}' cannot convert to vector dtype '{}'", py::cast<std::string>(py::str(arrayDt)), py::cast<std::string>(py::str(dt))));
                    }
                });
            });
        }), py::arg("dt"), py::arg("array"), "Constructs a DenseVector from an array. Internal 'dt' is set to 'dt'. Elements of 'array' must be able to fit in the specified 'dt'")
        .def_static("copy", [](const Py_DenseVector& other) -> Py_DenseVector {
            return std::visit([]<typename T>(const DenseVector<T>& otherVec) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, otherVec);
            }, other);
        }, py::arg("other"), "Returns a copy of the 'other' DenseVector")
        .def_static("copy", [](const py::dtype dt, const Py_DenseVector& other) -> Py_DenseVector {
            return std::visit([&]<typename T>(const DenseVector<T>& otherVec) -> Py_DenseVector {
                return dispatch_dt(dt, [&]<typename U>() -> Py_DenseVector {
                    if constexpr (lossless_convertible<T, U>) {
                        return Py_DenseVector(std::in_place_type<DenseVector<U>>, otherVec);
                    }
                    else {
                        throw py::type_error(std::format("Cannot copy DenseVector. Other DenseVector dtype '{}' cannot convert to vector dtype '{}'", py::cast<std::string>(py::str(py::dtype::of<T>())), py::cast<std::string>(py::str(dt))));
                    }
                });
            }, other);
        }, py::arg("dt"), py::arg("other"), "Returns a copy of the 'other' DenseVector. Copy's dtype is 'dt'. Dtype of 'other' must be able to convert to 'dt'")
        .def_static("copy", [](const PyDenseVectorLike other) -> Py_DenseVector {
            if (!py::isinstance<DenseVectorLikeBase>(other)) {
                throw py::type_error(std::format("Cannot copy DenseVector. Got '{}' expected a DenseVectorLike", py::cast<std::string>(py::str(other))));
            }

            const py::dtype dt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                DenseVectorLikePyWrapper<T> wrapper = DenseVectorLikePyWrapper<T>(other);
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
            });
        }, py::arg("other"), "Returns a copy of the 'other' DenseVectorLike")
        .def_static("copy", [](const py::dtype dt, const PyDenseVectorLike other) -> Py_DenseVector {
            if (!py::isinstance<DenseVectorLikeBase>(other)) {
                throw py::type_error(std::format("Cannot copy DenseVector. Got '{}' expected a DenseVectorLike", py::cast<std::string>(py::str(other))));
            }

            const py::dtype otherDt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseVector {
                    if constexpr (lossless_convertible<U, T>) {
                        DenseVectorLikePyWrapper<U> wrapper = DenseVectorLikePyWrapper<U>(other);
                        return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
                    }
                    else {
                        throw py::type_error(std::format("Cannot copy DenseVector. Other DenseVectorLike dtype '{}' cannot convert to vector dtype '{}'", py::cast<std::string>(py::str(dt)), py::cast<std::string>(py::str(otherDt))));
                    }
                });
            });
        }, py::arg("dt"), py::arg("other"), "Returns a copy of the 'other' DenseVectorLike. Copy's dtype is 'dt'. Dtype of 'other' must be able to convert to 'dt'")
        .def_static("move", [](Py_DenseVector& other) -> Py_DenseVector {
            return std::visit([]<typename T>(DenseVector<T>& otherVec) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, std::move(otherVec));
            }, other);
        }, py::arg("other"), "Returns a DenseVector constructed by moving from the 'other' vector. 'other' vector is left in empty yet valid state. Does not copy memory")
        .def("dtype", [](Py_DenseVector& self) -> py::dtype {
            return std::visit([]<typename T>(const DenseVector<T>&) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        }, "Returns the dtype that represents the vector's elements")
        .def("as_type", [](Py_DenseVector& self, const py::dtype dt) -> Py_DenseVector {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> Py_DenseVector {
                return dispatch_dt(dt, [&]<scalar U>() -> Py_DenseVector {
                    return Py_DenseVector(std::in_place_type<DenseVector<U>>, vec.template as_type<U>());
                });
            }, self);
        }, py::arg("dt"))
        .def("n", [](Py_DenseVector& self) -> std::size_t {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> std::size_t {
                return vec.n();
            }, self);
        }, "Returns the number of elements in the vector")
        .def("is_complex", [](Py_DenseVector& self) -> bool {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> bool {
                return DenseVector<T>::isComplex;
            }, self);
        }, "Returns whether the vector's elements are complex or real")
        .def("get", [](Py_DenseVector& self, const std::size_t i) -> AnyNumber {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> AnyNumber {
                 return py::cast(vec.get(i));
             }, self);
        }, py::arg("i"), "Returns the element at index 'i'. Checks 'i' is within bounds")
        .def("set", [](Py_DenseVector& self, const std::size_t i, const AnyNumber v) -> void {
            const py::dtype dt = get_dtype(v);

            dispatch_dt(dt, [&]<typename T>() -> void {
                return std::visit([&]<typename U>(DenseVector<U>& vec) -> void {
                    if constexpr (std::is_convertible_v<T, U>) {
                        vec.set(i, py::cast<U>(v));
                    }
                    else {
                        throw py::type_error("Cannot assign to DenseVector element with incompatible arg type");
                    }
                }, self);
            });
        }, py::arg("i"), py::arg("v"), "Sets the vector's element at index 'i' to 'v'. Checks 'i' is within bounds")
        .def("__getitem__", [](Py_DenseVector& self, std::size_t i) -> AnyNumber {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> AnyNumber {
                 return py::cast(vec[i]);
             }, self);
        }, py::arg("i"), "Returns the element in the vector at 'i'. Does not check bounds of 'i'")
        .def("__setitem__", [](Py_DenseVector& self, std::size_t i, const AnyNumber v) -> void {
            const py::dtype dt = get_dtype(v);

            dispatch_dt(dt, [&]<typename T>() -> void {
                std::visit([&]<typename U>(DenseVector<U>& vec) -> void {
                    if constexpr (std::is_convertible_v<T, U>) {
                        vec[i] = py::cast<U>(v);
                    }
                    else {
                        throw py::type_error("Cannot assign to vector element with non convertible dt");
                    }
                }, self);
            });
        }, py::arg("i"), py::arg("v"), "Sets the element in the vector at 'i' to 'v'. Does not check bounds of 'i'")
        .def("reshape", [](Py_DenseVector& self, const std::size_t newN, const bool preserve) -> void {
            std::visit([&]<typename T>(DenseVector<T>& vec) -> void {
                vec.reshape(newN, preserve);
            }, self);
        }, py::arg("newN"), py::arg("preserve"), "Reshapes the vector to be of size 'newN'. Leaves elements uninitialized if 'preserve' is false, if true elements is copied over")
        .def("reshape", [](Py_DenseVector& self, const std::size_t newN, const bool preserve, const AnyNumber value) -> void {
            const py::dtype dt = get_dtype(value);

            dispatch_dt(dt, [&]<typename T>() -> void {
                std::visit([&]<typename U>(DenseVector<U>& vec) -> void {
                    if constexpr (lossless_convertible<T, U>) {
                        vec.reshape(newN, preserve, py::cast<U>(value));
                    }
                    else {
                        throw py::type_error("Cannot reshape with value of non convertible dtype");
                    }
                }, self);
            });
        }, py::arg("newN"), py::arg("preserve"), py::arg("value"), "Reshapes the vector to be of size 'newN'. Sets elements to 'value' if 'preserve' is false, if true elements is copied over")
        .def("data", [](Py_DenseVector& self) -> py::array {
            return std::visit([]<typename T>(DenseVector<T>& v) -> py::array {
                size_t total_elements = v.n();

                py::capsule base(v.data(), [](void* /* p */) {});

                std::vector<size_t> shape = { total_elements };
                std::vector<size_t> strides = { sizeof(T) };

                return py::array_t<T>(shape, strides, v.data(), base);
            }, self);
        }, "Returns a ndarray to represent 'data' pointer inside the DenseVector");
}
