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
#include "vector.h"

#include "../../main.h"

void dense_vector_view_bindings(py::module_& m) {
    py::class_<Py_DenseVectorView, DenseVectorLikeBase>(m, "DenseVectorView")
        .def(py::init([](const Py_DenseVector& owner, const std::size_t n, const std::size_t offset) -> Py_DenseVectorView {
            return std::visit([&]<typename T>(const DenseVector<T>& vec) -> Py_DenseVectorView {
                return Py_DenseVectorView(std::in_place_type<std::shared_ptr<const DenseVectorView<T>>>, std::make_shared<DenseVectorView<T>>(vec, n, offset));
            }, owner);
        }), py::arg("owner"), py::arg("n"), py::arg("offset"), py::keep_alive<1, 2>())
        .def("dtype", [](Py_DenseVectorView& self) -> py::dtype {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> py::dtype {
                return py::dtype::of<T>();
            }, self);
        })
        .def("is_complex", [](Py_DenseVectorView& self) -> bool {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> bool {
                return DenseVectorView<T>::isComplex;
            }, self);
        })
        .def("n", [](Py_DenseVectorView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> std::size_t {
                return v->n();
            }, self);
        })
        .def("offset", [](Py_DenseVectorView& self) -> std::size_t {
            return std::visit([]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> std::size_t {
                return v->offset();
            }, self);
        })
        .def("get", [](Py_DenseVectorView& self, const std::size_t i) -> py::object {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> py::object {
                return py::cast(v->get(i));
            }, self);
        }, py::arg("i"))
        .def("set", [](Py_DenseVectorView&, const std::size_t, py::handle) -> void {
            throw py::type_error("Cannot set on dense vector view");
        })
        .def("__getitem__", [](Py_DenseVectorView& self, std::size_t i) -> py::object {
            return std::visit([&]<typename T>(const std::shared_ptr<const DenseVectorView<T>>& v) -> py::object {
                return py::cast(v->operator[](i));
            }, self);
        }, py::arg("i"))
        .def("__setitem__", [](Py_DenseVectorView&, std::size_t&, py::handle) -> void {
            throw py::type_error("Cannot set on dense vector view");
        });
}
