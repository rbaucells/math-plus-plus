from mathpy import *
import numpy
import pytest

from .simple_dense_vector_like import SimpleDenseVectorLike
from ... import telemetry_tests


def test_DenseVector_empty_constructor():
    # act
    telemetry_tests.start()
    m = DenseVector(numpy.dtypes.Float32DType())
    telemetry_tests.end()
    # assert
    assert m.n() == 0
    assert m.dtype() == numpy.dtypes.Float32DType()
    assert not m.is_complex()
    telemetry_tests.asserts(TelemetryStats(move_constructs=1))
    # TODO: Check if data is nullptr

def test_DenseVector_sized_constructor():
    # act
    telemetry_tests.start()
    a = DenseVector(numpy.dtypes.Complex64DType(), 3, True)
    telemetry_tests.end()
    # assert
    assert a.n() == 3
    assert a.dtype() == numpy.dtypes.Complex64DType()
    assert a.is_complex()
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    for i in range(3):
        assert a.get(i) == 0 + 0j

    # act
    telemetry_tests.start()
    b = DenseVector(numpy.dtypes.Int32DType(), 4, False)
    telemetry_tests.end()
    # assert
    assert b.n() == 4
    assert b.dtype() == numpy.dtypes.Int32DType()
    assert not b.is_complex()
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))
    # TODO: Check if data is not nullptr

def test_DenseVector_list_constructor():
    # act
    telemetry_tests.start()
    a = DenseVector([1, 2, 3])
    telemetry_tests.end()
    # assert
    assert a.n() == 3
    assert a.dtype() == numpy.dtypes.UInt8DType()
    assert not a.is_complex()
    # TODO: Replace with compare
    assert a[0] == 1
    assert a[1] == 2
    assert a[2] == 3

    # act
    telemetry_tests.start()
    b = DenseVector(numpy.array([1, 4], dtype=numpy.float32))
    telemetry_tests.end()
    # assert
    assert b.n() == 2
    assert b.dtype() == numpy.dtypes.Float32DType()
    assert not b.is_complex()
    # TODO: Replace with compare
    assert b[0] == 1
    assert b[1] == 4
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    # act
    telemetry_tests.start()
    c = DenseVector(numpy.dtypes.Float32DType(), [1, 2, 3, 4])
    telemetry_tests.end()
    # assert
    assert c.n() == 4
    assert c.dtype() == numpy.dtypes.Float32DType()
    assert not c.is_complex()
    # TODO: Replace with compare
    assert c[0] == 1
    assert c[1] == 2
    assert c[2] == 3
    assert c[3] == 4
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    # act
    telemetry_tests.start()
    d = DenseVector(numpy.dtypes.Float64DType(), numpy.array([4, 5, 6], dtype=numpy.float32))
    telemetry_tests.end()
    # assert
    assert d.n() == 3
    assert d.dtype() == numpy.dtypes.Float64DType()
    assert not d.is_complex()
    # TODO: Replace with compare
    assert d[0] == 4
    assert d[1] == 5
    assert d[2] == 6
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    # act / assert
    with pytest.raises(TypeError):
        DenseVector(numpy.dtypes.Int32DType(), [4, 5, 6 + 4j])

def test_DenseVector_copy_constructor_from_same_type():
    # arrange
    a = DenseVector(numpy.dtypes.Int32DType(), [6, -65, 12, 99])
    # act
    telemetry_tests.start()
    b = DenseVector.copy(a)
    telemetry_tests.end()
    # assert
    assert b.n() == 4
    assert b.dtype() == numpy.dtypes.Int32DType()
    assert not b.is_complex()
    # TODO: Replace with compare
    assert b[0] == 6
    assert b[1] == -65
    assert b[2] == 12
    assert b[3] == 99
    telemetry_tests.asserts(TelemetryStats(copy_constructs=1, move_constructs=1, allocations=1))

def test_DenseVector_copy_constructor_from_diff_type():
    # arrange
    a = DenseVector(numpy.dtypes.Int32DType(), [1, 99, -6, 5])
    expected = DenseVector([1, 99, -6, 5])
    # act
    telemetry_tests.start()
    b = DenseVector.copy(numpy.dtypes.Int64DType(), a)
    telemetry_tests.end()
    # assert
    assert b.n() == 4
    assert b.dtype() == numpy.dtypes.Int64DType()
    assert not b.is_complex()
    assert compare(a, expected)
    telemetry_tests.asserts(TelemetryStats(copy_constructs=1, move_constructs=1, allocations=1))

def test_DenseVector_copy_constructor_from_like_of_same_type():
    # arrange
    a = SimpleDenseVectorLike([1, 2, 4])
    # act
    telemetry_tests.start()
    b = DenseVector.copy(a)
    telemetry_tests.end()
    # assert
    assert b.n() == 3
    assert b.dtype() == numpy.dtypes.UInt8DType()
    assert not b.is_complex()
    assert b[0] == 1
    assert b[1] == 2
    assert b[2] == 4
    telemetry_tests.asserts(TelemetryStats(copy_constructs=1, allocations=1, move_constructs=1))

def test_DenseVector_copy_constructor_from_like_of_diff_type():
    # arrange
    a = SimpleDenseVectorLike([1, 3, 4])
    # act
    telemetry_tests.start()
    b = DenseVector.copy(numpy.dtypes.Complex64DType(), a)
    telemetry_tests.end()
    # assert
    assert b.n() == 3
    assert b.dtype() == numpy.dtypes.Complex64DType()
    assert b.is_complex()
    assert b[0] == 1
    assert b[1] == 3
    assert b[2] == 4
    telemetry_tests.asserts(TelemetryStats(copy_constructs=1, allocations=1, move_constructs=1))

def test_DenseVector_move_constructor():
    # arrange
    a = DenseVector([5, 1, 6])
    # act
    telemetry_tests.start()
    b = DenseVector.move(a)
    telemetry_tests.end()
    # assert
    assert a.n() == 0
    # TODO: Assert a data is nullptr
    assert b.n() == 3
    assert b.dtype() == numpy.dtypes.UInt8DType()
    assert not b.is_complex()
    assert b[0] == 5
    assert b[1] == 1
    assert b[2] == 6

def test_DenseVector_dtype():
    # arrange
    a = DenseVector([1, 2, 3, 4])
    # act
    aDt = a.dtype()
    # assert
    assert aDt == numpy.dtypes.UInt8DType()
    # arrange
    b = DenseVector(numpy.dtypes.Complex128DType())
    # act
    bDt = b.dtype()
    # assert
    assert bDt == numpy.dtypes.Complex128DType()

def test_DenseVector_as_type():
    # arrange
    a = DenseVector([1, 2, 3, 4])
    # act
    b = a.as_type(numpy.dtypes.Float64DType())
    # assert
    assert b[0] == 1
    assert b[1] == 2
    assert b[2] == 3
    assert b[3] == 4
    assert b.dtype() == numpy.dtypes.Float64DType()
    # arrange
    c = DenseVector([4.2, 6.8, 2.1, 4 + 6j])
    # act
    d = c.as_type(numpy.dtypes.Int16DType())
    # assert
    assert d[0] == 4
    assert d[1] == 6
    assert d[2] == 2
    assert d[3] == 4
    assert d.dtype() == numpy.dtypes.Int16DType()

def test_DenseVector_rows():
    # arrange
    a = DenseVector(numpy.dtypes.Float32DType(), 3)
    # act
    n = a.n()
    # assert
    assert n == 3

def test_DenseVector_get():
    # arrange
    a = DenseVector([1, 2, 3, 4])
    # act
    telemetry_tests.start()
    val = a.get(2)
    telemetry_tests.end()
    # assert
    assert val == 3
    telemetry_tests.asserts(TelemetryStats())

    # arrange
    b = DenseVector(numpy.dtypes.Int32DType(), 4)
    # act / assert
    with pytest.raises(ValueError):
        b.get(4)
def test_DenseVector_set():
    # arrange
    a = DenseVector([1, 2, 3, 4])
    # act
    telemetry_tests.start()
    a.set(2, 4)
    telemetry_tests.end()
    # assert
    assert a.get(2) == 4
    telemetry_tests.asserts(TelemetryStats())

    # arrange
    b = DenseVector(numpy.dtypes.Int32DType(), 4)
    # act / assert
    with pytest.raises(ValueError):
        b.set(4, 5)
def test_DenseVector_indexing_operator():
    # arrange
    a = DenseVector([1, 2, 3, 4])
    # act
    telemetry_tests.start()
    val = a[2]
    telemetry_tests.end()
    # assert
    assert val == 3
    a[2] = 4
    assert a[2] == 4
    telemetry_tests.asserts(TelemetryStats())

def test_DenseVector_reshape():
    # arrange
    a = DenseVector([1, 2, 3])
    expected = DenseVector([1, 2, 3])
    # act
    telemetry_tests.start()
    a.reshape(3, False)
    telemetry_tests.end()
    # assert
    assert compare(a, expected)
    telemetry_tests.asserts(TelemetryStats())
    # arrange
    b = DenseVector([1, 2, 3])
    expected = DenseVector([1, 2, 3])
    # act
    telemetry_tests.start()
    b.reshape(3, True)
    telemetry_tests.end()
    # assert
    assert compare(b, expected)
    telemetry_tests.asserts(TelemetryStats())
    # arrange
    c = DenseVector([1, 2, 3])
    expected = DenseVector([1, 2, 3])
    # act
    telemetry_tests.start()
    c.reshape(3, False, 67)
    telemetry_tests.end()
    # assert
    assert compare(c, expected)
    telemetry_tests.asserts(TelemetryStats())
    # arrange
    d = DenseVector([1, 2, 3])
    expected = DenseVector([1, 2, 3])
    # act
    telemetry_tests.start()
    d.reshape(3, True, 67)
    telemetry_tests.end()
    # assert
    assert compare(d, expected)
    telemetry_tests.asserts(TelemetryStats())
    # arrange
    e = DenseVector([1, 2, 3])
    expected = DenseVector([1, 2])
    # act
    telemetry_tests.start()
    e.reshape(2, True)
    telemetry_tests.end()
    # assert
    assert e.n() == 2
    assert compare(e, expected)
    telemetry_tests.asserts(TelemetryStats(allocations=1, deallocations=1))
    # arrange
    f = DenseVector([1, 2, 3])
    expected = DenseVector([67, 67])
    # act
    telemetry_tests.start()
    f.reshape(2, False, 67)
    telemetry_tests.end()
    # assert
    assert f.n() == 2
    assert compare(f, expected)
    telemetry_tests.asserts(TelemetryStats(allocations=1, deallocations=1))
    # arrange
    g = DenseVector([1, 2, 3])
    expected = DenseVector([1, 2, 3, 67])
    # act
    telemetry_tests.start()
    g.reshape(4, True, 67)
    telemetry_tests.end()
    # assert
    assert g.n() == 4
    assert compare(g, expected)
    telemetry_tests.asserts(TelemetryStats(allocations=1, deallocations=1))

def test_DenseVector_is_complex():
    # arrange
    a = DenseVector(numpy.dtypes.Float32DType(), 3)
    # act
    aComplex = a.is_complex()
    # assert
    assert not aComplex
    # arrange
    a = DenseVector(numpy.dtypes.Complex64DType(), 3)
    # act
    aComplex = a.is_complex()
    # assert
    assert aComplex

def test_DenseVector_data():
    # arrange
    a = DenseVector([1, 3, 2, 4])
    # act
    aData = a.data()
    # assert
    assert aData[0] == 1
    assert aData[1] == 3
    assert aData[2] == 2
    assert aData[3] == 4
    # arrange
    b = DenseVector([1 + 0.4j, 3j, 2 - 2j, 4])
    # act
    bData = b.data()
    # assert
    assert bData[0] == 1 + 0.4j
    assert bData[1] == 3j
    assert bData[2] == 2 - 2j
    assert bData[3] == 4