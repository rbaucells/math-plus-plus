import mathpy
import numpy

def test_radians_to_degrees():
    # arrange
    expected_real = 45.0
    radians_real = numpy.pi / 4
    # act
    degrees_real = mathpy.radians_to_degrees(radians_real)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), degrees_real, expected_real)
    # arrange
    expected_complex = numpy.complex128(45 + 90j)
    radians_complex = numpy.complex128(numpy.pi / 4 + numpy.pi / 2 * 1j)
    # act
    degrees_complex = mathpy.radians_to_degrees(radians_complex)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), degrees_complex, expected_complex)

def test_degrees_to_radians():
    # arrange
    expected_real = numpy.pi / 4
    degrees_real = 45.0
    # act
    radians_real = mathpy.degrees_to_radians(degrees_real)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), radians_real, expected_real)
    # arrange
    expected_complex = numpy.complex128(numpy.pi / 4 + numpy.pi / 2 * 1j)
    degrees_complex = numpy.complex128(45 + 90j)
    # act
    radians_complex = mathpy.degrees_to_radians(degrees_complex)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), radians_complex, expected_complex)

def test_convert():
    # arrange
    expected = 45.0
    radians = numpy.pi / 4
    # act
    degrees = mathpy.convert(mathpy.RotationType.radians, mathpy.RotationType.degrees, radians)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), degrees, expected)
    # arrange
    expected = numpy.pi / 4
    # act
    radians = mathpy.convert(mathpy.RotationType.radians, mathpy.RotationType.radians, expected)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), radians, expected)
    # arrange
    expected = numpy.complex128(45 + 90j)
    radians = numpy.complex128(numpy.pi / 4 + numpy.pi / 2 * 1j)
    # act
    degrees = mathpy.convert(mathpy.RotationType.radians, mathpy.RotationType.degrees, radians)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), degrees, expected)
    # arrange
    expected = numpy.pi / 4
    degrees = 45.0
    # act
    radians = mathpy.convert(mathpy.RotationType.degrees, mathpy.RotationType.radians, degrees)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), radians, expected)
    # arrange
    expected = 90.0
    # act
    degrees = mathpy.convert(mathpy.RotationType.degrees, mathpy.RotationType.degrees, expected)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), degrees, expected)
    # arrange
    expected = numpy.complex128(numpy.pi / 4 + numpy.pi / 2 * 1j)
    degrees = numpy.complex128(45 + 90j)
    # act
    radians = mathpy.convert(mathpy.RotationType.degrees, mathpy.RotationType.radians, degrees)
    # assert
    assert mathpy.compare(mathpy.Precision(0.001), radians, expected)
