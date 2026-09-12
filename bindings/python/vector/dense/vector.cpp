#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <ranges>
#include <cstddef>
#include <ranges>

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
        }), py::arg("dt"))
        .def(py::init([](const py::dtype dt, const std::size_t n, const bool fill) -> Py_DenseVector {
            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, n, fill);
            });
        }), py::arg("dt"), py::arg("n"), py::arg("fill") = true)
        .def(py::init([](const py::sequence sequence) -> Py_DenseVector {
            const auto [dt, et, size] = get_sequence_info(sequence);

            if (et != EType::scalar) {
                throw py::type_error("Cannot construct dense vector from sequence of etype: " + to_string(et) + " (should be scalar)");
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                    return py::cast<T>(sequence[i]);
                });

                return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
            });
        }), py::arg("sequence"))
        .def(py::init([](const py::array array) -> Py_DenseVector {
            const auto [dt, et, size] = get_array_info(array);

            if (et != EType::scalar) {
                throw py::type_error("Cannot construct dense vector from array of etype: " + to_string(et) + " (should be scalar)");
            }

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                py::detail::unchecked_reference<T, 1> unchecked = array.unchecked<T, 1>();

                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T{
                    return unchecked(i);
                });

                return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
            });
        }), py::arg("array"))
        .def(py::init([](const py::dtype dt, const py::sequence sequence) -> Py_DenseVector {
            const auto [sequenceDt, sequenceEt, size] = get_sequence_info(sequence);

            if (sequenceEt != EType::scalar) {
                throw py::type_error("Cannot construct dense vector from sequence of etype: " + to_string(sequenceEt) + " (should be scalar)");
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
                        throw py::type_error("Cannot convert sequence dt to specified dt while constructing dense vector from sequence");
                    }
                });
            });
        }), py::arg("dt"), py::arg("sequence"))
        .def(py::init([](const py::dtype dt, const py::array array) -> Py_DenseVector {
            const auto [arrayDt, arrayEt, size] = get_array_info(array);

            if (arrayEt != EType::scalar) {
                throw py::type_error();
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
                        throw py::type_error("Cannot convert array dt to specified dt while constructing dense vector from array");
                    }
                });
            });
        }), py::arg("dt"), py::arg("array"))
        .def_static("copy", [](const Py_DenseVector& other) -> Py_DenseVector {
            return std::visit([]<typename T>(const DenseVector<T>& otherMat) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, otherMat);
            }, other);
        }, py::arg("other"))
        .def_static("copy", [](const py::dtype dt, const Py_DenseVector& other) -> Py_DenseVector {
            return std::visit([&]<typename T>(const DenseVector<T>& otherMat) -> Py_DenseVector {
                return dispatch_dt(dt, [&]<typename U>() -> Py_DenseVector {
                    if constexpr (lossless_convertible<T, U>) {
                        return Py_DenseVector(std::in_place_type<DenseVector<U>>, otherMat);
                    }
                    else {
                        throw py::type_error("Cannot copy construct a dense vector from another with non convertible type");
                    }
                });
            }, other);
        }, py::arg("dt"), py::arg("other"))
        .def_static("copy", [](const py::object other) -> Py_DenseVector {
            if (!py::isinstance<DenseVectorLikeBase>(other)) {
                throw py::type_error("Cannot copy construct dense vector from object that doesn't derive from DenseVectorLike");
            }

            const py::dtype dt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                DenseVectorLikePyWrapper<T> wrapper = DenseVectorLikePyWrapper<T>(other);
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
            });
        }, py::arg("other"))
        .def_static("copy", [](const py::dtype dt, const py::object other) -> Py_DenseVector {
            if (!py::isinstance<DenseVectorLikeBase>(other)) {
                throw py::type_error("Cannot copy construct dense vector from object that doesn't derive from DenseVectorLike");
            }

            const py::dtype otherDt = getattr(other, "dtype")();

            return dispatch_dt(dt, [&]<typename T>() -> Py_DenseVector {
                return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseVector {
                    if constexpr (lossless_convertible<U, T>) {
                        DenseVectorLikePyWrapper<U> wrapper = DenseVectorLikePyWrapper<U>(other);
                        return Py_DenseVector(std::in_place_type<DenseVector<T>>, wrapper);
                    }
                    else {
                        throw py::type_error("Cannot copy construct a dense vector from dense vector like with non convertible type");
                    }
                });
            });
        }, py::arg("dt"), py::arg("other"))
        .def_static("move", [](Py_DenseVector& other) -> Py_DenseVector {
            return std::visit([]<typename T>(DenseVector<T>& otherMat) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<T>>, std::move(otherMat));
            }, other);
        }, py::arg("other"))
        .def("dtype", [](Py_DenseVector& self) -> py::dtype {
            return std::visit([]<typename T>(const DenseVector<T>&) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        })
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
        })
        .def("is_complex", [](Py_DenseVector& self) -> bool {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> bool {
                return DenseVector<T>::isComplex;
            }, self);
        })
        .def("get", [](Py_DenseVector& self, const std::size_t i) -> py::object {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> py::object {
                 return py::cast(vec.get(i));
             }, self);
        }, py::arg("i"))
        .def("set", [](Py_DenseVector& self, const std::size_t i, const py::object v) -> void {
            const py::dtype dt = get_dtype(v);

            dispatch_dt(dt, [&]<typename T>() -> void {
                std::visit([&]<typename U>(DenseVector<U>& vec) -> void {
                    if constexpr (std::is_convertible_v<T, U>) {
                        vec.set(i, py::cast<U>(v));
                    }
                    else {
                        throw py::type_error("Cannot assign to DenseVector element with incovecible arg type");
                    }
                }, self);
            });
        }, py::arg("i"), py::arg("v"))
        .def("__getitem__", [](Py_DenseVector& self, std::size_t i) -> py::object {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> py::object {
                 return py::cast(vec[i]);
             }, self);
        }, py::arg("i"))
        .def("__setitem__", [](Py_DenseVector& self, std::size_t i, const py::object v) -> void {
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
        }, py::arg("i"), py::arg("v"))
        .def("reshape", [](Py_DenseVector& self, const std::size_t newN, const bool preserve) {
            return std::visit([&]<typename T>(DenseVector<T>& vec) {
                vec.reshape(newN, preserve);
            }, self);
        }, py::arg("newN"), py::arg("preserve"))
        .def("reshape", [](Py_DenseVector& self, const std::size_t newN, const bool preserve, const py::object value) {
            const py::dtype dt = get_dtype(value);

            return dispatch_dt(dt, [&]<typename T>() {
                return std::visit([&]<typename U>(DenseVector<U>& vec) {
                    if constexpr (lossless_convertible<T, U>) {
                        vec.reshape(newN, preserve, py::cast<U>(value));
                    }
                    else {
                        throw py::type_error("Cannot reshape with value of non convertible dtype");
                    }
                }, self);
            });
        }, py::arg("newN"), py::arg("preserve"), py::arg("value"))
        .def("data", [](Py_DenseVector& self) -> py::object {
            return std::visit([]<typename T>(DenseVector<T>& v) -> py::object {
                py::capsule base(v.data(), [](void* /* p */) {});

                std::vector<size_t> shape = { v.n() };
                std::vector<size_t> strides = { sizeof(T) };

                return py::array_t<T>(shape, strides, v.data(), base);
            }, self);
        });
}
