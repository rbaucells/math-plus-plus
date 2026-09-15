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
#include "vector.h"

#include "../../main.h"

void dense_vector_view_bindings(py::module_& m) {
    py::class_<Py_DenseVectorView, DenseVectorLikeBase>(m, "DenseVectorView")
        .def(py::init([](const Py_DenseVector& owner, const std::size_t n, const std::size_t offset) -> Py_DenseVectorView {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> Py_DenseVectorView {
                return Py_DenseVectorView(std::in_place_type<std::shared_ptr<const DenseVectorView<T>>>, std::make_shared<DenseVectorView<T>>(vec, n, offset));
            }, owner);
        }), py::arg("owner"), py::arg("n"), py::arg("offset"), py::keep_alive<1, 2>(), "Constructs a DenseVectorView on another DenseVector with a specified 'n' size with an 'offset' relative to the DenseVector parent")
        .def("dtype", [](Py_DenseVectorView& self) -> py::dtype {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        }, "Returns the dtype that represents the view's elements")
        .def("is_complex", [](Py_DenseVectorView& self) -> bool {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> bool {
                return DenseVectorView<T>::isComplex;
            }, self);
        }, "Returns whether the view's elements are complex or real")
        .def("n", [](Py_DenseVectorView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> std::size_t {
                return v->n();
            }, self);
        }, "Returns the number of elements in the view")
        .def("offset", [](Py_DenseVectorView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> std::size_t {
                return v->offset();
            }, self);
        }, "Returns the number of elements the view is offset from its parent")
        .def("get", [](Py_DenseVectorView& self, const std::size_t i) -> AnyNumber {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> AnyNumber {
                return py::cast(v->get(i));
            }, self);
        }, py::arg("i"), "Returns the element at index 'i' of the view. Checks 'i' is within bounds of the view and of the parent")
        .def("set", [](Py_DenseVectorView&, const std::size_t, AnyNumber) -> void {
            throw py::type_error("Cannot set on dense vector view");
        }, py::arg("i"), py::arg("v"), "Sets the view's element at index 'i' to 'v'. Checks 'i' is within bounds of the view and parent")
        .def("__getitem__", [](Py_DenseVectorView& self, std::size_t i) -> AnyNumber {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> AnyNumber {
                return py::cast(v->operator[](i));
            }, self);
        }, py::arg("i"), "Returns the element in the view at 'i'. Does not check bounds of 'i'")
        .def("__setitem__", [](Py_DenseVectorView&, std::size_t, AnyNumber) -> void {
            throw py::type_error("Cannot set on dense vector view");
        }, py::arg("i"), py::arg("v"), "Sets the element in the view at 'i' to 'v'. Does not check bounds of 'i'");
}
