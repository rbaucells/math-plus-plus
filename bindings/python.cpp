#include <pybind11/pybind11.h>
#include <pybind11/native_enum.h>
#include <pybind11/stl.h>
#include "math++/math.h"

namespace py = pybind11;

PYBIND11_MODULE(mathpy, m) {
    // 1. Define the enum
    py::native_enum<RotationType>(m, "RotationType", "enum.Enum")
        .value("radians", RotationType::radians)
        .value("degrees", RotationType::degrees)
        .export_values()
        .finalize();

    m.def("convert", [](const RotationType from, const RotationType to, const float rotation) -> float {
        return convert<float>(from, to, rotation);
    }, py::arg("from"), py::arg("to"), py::arg("rotation"));

    m.def("convert", [](const RotationType from, const RotationType to, const double rotation) -> double {
        return convert<double>(from, to, rotation);
    }, py::arg("from"), py::arg("to"), py::arg("rotation"));

    py::class_<Matrix<3, 3, float>>(m, "Matrix3f")
        .def(py::init([](const std::vector<std::vector<float>>& list) {
            auto* matrix = new Matrix<3, 3, float>();

            // number of rows in initializer list
            if (list.size() != 3)
                throw InvalidDimensionException("Incorrect number of rows in initializer list");
            // row-major order in initializer list
            int r = 0;
            // loop over each row
            for (const auto& row : list) {
                // check correct number of elements in row
                if (row.size() != 3)
                    throw InvalidDimensionException("Incorrect number of columns in initializer list");
                // column index
                int c = 0;
                // loop over each element in the row
                for (const auto element : row) {
                    // store in column-major order
                    matrix->data[c][r] = element;
                    // advance column
                    c++;
                }
                // advance row
                r++;
            }

            return matrix;
        }))
        .def("transpose", &Matrix<3, 3, float>::transpose)
        .def("toString", &Matrix<3, 3, float>::toString)
        .def("addEquals", [](Matrix<3, 3, float>& self, const Matrix<3, 3, float>& other) {
            self.addEquals(other);
        }, py::arg("other"));
}
