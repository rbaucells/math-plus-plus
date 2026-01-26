#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/native_enum.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include "math++/math.h"

namespace py = pybind11;

PYBIND11_MODULE(mathpy, m) {
    py::native_enum<DotProductConjugationBehavior>(m, "DotProductConjugationBehavior", "enum.Enum")
        .value("first_argument", DotProductConjugationBehavior::first_argument)
        .value("neither", DotProductConjugationBehavior::neither)
        .value("second_argument", DotProductConjugationBehavior::second_argument)
        .export_values()
        .finalize();

    py::class_<Vector<3>>(m, "Vector3f")
        .def(py::init())
        .def(py::init([](const std::vector<float>& elements) {
            auto* vec = new Vector<3>();

            for (int i = 0; i < 3; i++) {
                vec->data[i] = elements[i];
            }

            return vec;
        }), py::arg("elements"))
        .def(py::init([](const Vector<3>& other) -> Vector<3>* {
            return new Vector<3>(other);
        }))

        .def_static("random", [](const float min, const float max) -> Vector<3> {
            return Vector<3>::random(min, max);
        }, py::arg("min") = -1, py::arg("max") = 1)

        .def(py::self == py::self)
        .def("equals", [](const Vector<3>& self, const Vector<3>& other, const float precision) -> bool {
            return self.equals(other, precision);
        }, py::arg("other"), py::arg("precision") = epsilon<float>())

        .def(py::self + py::self)
        .def("add", [](const Vector<3>& self, const Vector<3>& other) -> Vector<3> {
            return self.add(other);
        }, py::arg("other"))

        .def(py::self - py::self)
        .def("subtract", [](const Vector<3>& self, const Vector<3>& other) -> Vector<3> {
            return self.subtract(other);
        }, py::arg("other"))

        .def(py::self / float())
        .def("divide", [](const Vector<3>& self, const float scalar) -> Vector<3> {
            return self.divide(scalar);
        }, py::arg("scalar"))

        .def(py::self * float())
        .def("multiply", [](const Vector<3>& self, const float scalar) -> Vector<3> {
            return self.multiply(scalar);
        }, py::arg("scalar"))

        .def(float() * py::self)

        // different types

        .def("__eq__", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other) -> bool {
            return self == other;
        }, py::is_operator())
        .def("equals", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other, const float precision) -> bool {
            return self.equals(other, precision);
        }, py::arg("other"), py::arg("precision") = epsilon<float>())

        .def("__add__", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>> {
            return self + other;
        }, py::is_operator())
        .def("add", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>> {
            return self.add(other);
        }, py::arg("other"))

        .def("__sub__", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>> {
            return self - other;
        }, py::is_operator())
        .def("subtract", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>> {
            return self.subtract(other);
        }, py::arg("other"))

        .def(py::self / std::complex<float>())
        .def("divide", [](const Vector<3>& self, const std::complex<float> scalar) -> Vector<3, std::complex<float>> {
            return self.divide(scalar);
        }, py::arg("scalar"))

        .def(py::self * std::complex<float>())
        .def("multiply", [](const Vector<3>& self, const std::complex<float> scalar) -> Vector<3, std::complex<float>> {
            return self.multiply(scalar);
        }, py::arg("scalar"))

        .def(std::complex<float>() * py::self)


        .def(py::self += py::self)
        .def("add_equals", [](Vector<3>& self, const Vector<3>& other) -> Vector<3>& {
            return self.addEquals(other);
        }, py::arg("other"))

        .def(py::self -= py::self)
        .def("subtract_equals", [](Vector<3>& self, const Vector<3>& other) -> Vector<3>& {
            return self.subtractEquals(other);
        }, py::arg("other"))

        .def(py::self *= float())
        .def("multiply_equals", [](Vector<3>& self, const float scalar) -> Vector<3>& {
            return self.multiplyEquals(scalar);
        }, py::arg("scalar"))

        .def(py::self /= float())
        .def("divide_equals", [](Vector<3>& self, const float scalar) -> Vector<3>& {
            return self.divideEquals(scalar);
        }, py::arg("scalar"))

        .def(-py::self)
        .def("conjugate", &Vector<3>::conjugate)
        .def("taxicab_norm", &Vector<3>::taxicabNorm)
        .def("euclidian_norm", &Vector<3>::euclidianNorm)
        .def("euclidian_norm_squared", &Vector<3>::euclidianNormSquared)
        .def("max_norm", &Vector<3>::maxNorm)
        .def("to_string", [](const Vector<3>& self, const int precision) -> std::string {
            return self.toString(precision);
        }, py::arg("precision") = 2)
        .def(py::self * py::self)
        .def("dot", [](const Vector<3>& self, const Vector<3>& other, const DotProductConjugationBehavior behavior) -> float {
            return self.dot(other, behavior);
        }, py::arg("other"), py::arg("behavior") = DotProductConjugationBehavior::first_argument)
        // different types
        .def("__mul__", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other) -> std::complex<float> {
            return self * other;
        }, py::is_operator())
        .def("dot", [](const Vector<3>& self, const Vector<3, std::complex<float>>& other, const DotProductConjugationBehavior behavior) -> std::complex<float> {
            return self.dot(other, behavior);
        });

    py::class_<Vector<3, std::complex<float>>>(m, "Vector3cf")
        .def(py::init())
        .def(py::init([](const std::vector<std::complex<float>>& elements) {
            auto* vec = new Vector<3, std::complex<float>>();

            for (int i = 0; i < 3; i++) {
                vec->data[i] = elements[i];
            }

            return vec;
        }), py::arg("elements"))
        .def(py::init([](const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>>* {
            return new Vector<3, std::complex<float>>(other);
        }))

        .def_static("random", [](const float min, const float max) -> Vector<3, std::complex<float>> {
            return Vector<3, std::complex<float>>::random(min, max);
        }, py::arg("min") = -1, py::arg("max") = 1)

        .def(py::self == py::self)
        .def("equals", [](const Vector<3, std::complex<float>>& self, const Vector<3, std::complex<float>>& other, const float precision) {
            return self.equals(other, precision);
        }, py::arg("other"), py::arg("precision") = epsilon<float>())

        .def(py::self + py::self)
        .def("add", [](const Vector<3, std::complex<float>>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>> {
            return self.add(other);
        }, py::arg("other"))

        .def(py::self - py::self)
        .def("subtract", [](const Vector<3, std::complex<float>>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>> {
            return self.subtract(other);
        }, py::arg("other"))

        .def(py::self / std::complex<float>())
        .def("divide", [](const Vector<3, std::complex<float>>& self, const std::complex<float> scalar) -> Vector<3, std::complex<float>> {
            return self.divide(scalar);
        }, py::arg("scalar"))

        .def(py::self * std::complex<float>())
        .def("multiply", [](const Vector<3, std::complex<float>>& self, const std::complex<float> scalar) -> Vector<3, std::complex<float>> {
            return self.multiply(scalar);
        }, py::arg("scalar"))

        .def(std::complex<float>() * py::self)
        .def(py::self += py::self)
        .def("add_equals", [](Vector<3, std::complex<float>>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>>& {
            return self.addEquals(other);
        }, py::arg("other"))

        .def(py::self -= py::self)
        .def("subtract_equals", [](Vector<3, std::complex<float>>& self, const Vector<3, std::complex<float>>& other) -> Vector<3, std::complex<float>>& {
            return self.subtractEquals(other);
        }, py::arg("other"))

        .def(py::self *= std::complex<float>())
        .def("multiply_equals", [](Vector<3, std::complex<float>>& self, const std::complex<float> scalar) -> Vector<3, std::complex<float>>& {
            return self.multiplyEquals(scalar);
        }, py::arg("scalar"))

        .def(py::self /= std::complex<float>())
        .def("divide_equals", [](Vector<3, std::complex<float>>& self, const std::complex<float> scalar) -> Vector<3, std::complex<float>>& {
            return self.divideEquals(scalar);
        }, py::arg("scalar"))

        // different types

        .def("__eq__", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other) -> bool {
            return self == other;
        }, py::is_operator())
        .def("equals", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other, const float precision) {
            return self.equals(other, precision);
        }, py::arg("other"), py::arg("precision") = epsilon<float>())

        .def("__add__", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>> {
            return self + other;
        }, py::is_operator())
        .def("add", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>> {
            return self.add(other);
        }, py::arg("other"))

        .def("__sub__", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>> {
            return self - other;
        }, py::is_operator())
        .def("subtract", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>> {
            return self.subtract(other);
        }, py::arg("other"))

        .def(py::self / float())
        .def("divide", [](const Vector<3, std::complex<float>>& self, const float scalar) -> Vector<3, std::complex<float>> {
            return self.divide(scalar);
        }, py::arg("scalar"))

        .def(py::self * float())
        .def("multiply", [](const Vector<3, std::complex<float>>& self, const float scalar) -> Vector<3, std::complex<float>> {
            return self.multiply(scalar);
        }, py::arg("scalar"))

        .def(float() * py::self)
        .def("__iadd__", [](Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>>& {
            return self += other;
        }, py::is_operator())
        .def("add_equals", [](Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>>& {
            return self.addEquals(other);
        }, py::arg("other"))

        .def("__isub__", [](Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>>& {
            return self -= other;
        }, py::is_operator())
        .def("subtract_equals", [](Vector<3, std::complex<float>>& self, const Vector<3>& other) -> Vector<3, std::complex<float>>& {
            return self.subtractEquals(other);
        }, py::arg("other"))

        .def(py::self *= float())
        .def("multiply_equals", [](Vector<3, std::complex<float>>& self, const float scalar) -> Vector<3, std::complex<float>>& {
            return self.multiplyEquals(scalar);
        }, py::arg("scalar"))

        .def(py::self /= float())
        .def("divide_equals", [](Vector<3, std::complex<float>>& self, const float scalar) -> Vector<3, std::complex<float>>& {
            return self.divideEquals(scalar);
        }, py::arg("scalar"))

        .def(-py::self)
        .def("conjugate", &Vector<3, std::complex<float>>::conjugate)
        .def("taxicab_norm", &Vector<3, std::complex<float>>::taxicabNorm)
        .def("euclidian_norm", &Vector<3, std::complex<float>>::euclidianNorm)
        .def("euclidian_norm_squared", &Vector<3, std::complex<float>>::euclidianNormSquared)
        .def("max_norm", &Vector<3, std::complex<float>>::maxNorm)
        .def("to_string", [](const Vector<3, std::complex<float>>& self, const int precision) -> std::string {
            return self.toString(precision);
        }, py::arg("precision") = 2)
        .def(py::self * py::self)
        .def("dot", [](const Vector<3, std::complex<float>>& self, const Vector<3, std::complex<float>>& other, const DotProductConjugationBehavior behavior) -> std::complex<float> {
            return self.dot(other, behavior);
        }, py::arg("other"), py::arg("behavior") = DotProductConjugationBehavior::first_argument)
        .def("__mul__", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other) -> std::complex<float> {
            return self * other;
        }, py::is_operator())
        .def("dot", [](const Vector<3, std::complex<float>>& self, const Vector<3>& other, const DotProductConjugationBehavior behavior) -> std::complex<float> {
            return self.dot(other, behavior);
        });
}
