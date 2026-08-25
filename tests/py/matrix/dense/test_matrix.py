from mathpy import *
import numpy
import pytest
from ... import telemetry_tests


def test_DenseMatrix_empty_constructor():
    # act
    telemetry_tests.start()
    m = DenseMatrix(numpy.dtypes.Float32DType())
    telemetry_tests.end()
    # assert
    assert m.rows() == 0
    assert m.columns() == 0
    assert m.dtype() == numpy.dtypes.Float32DType()
    assert not m.is_complex()
    telemetry_tests.asserts(TelemetryStats(move_constructs=1))
    # TODO: Check if data is nullptr

def test_DenseMatrix_sized_constructor():
    # act
    telemetry_tests.start()
    a = DenseMatrix(numpy.dtypes.Complex64DType(), 3, 4, True)
    telemetry_tests.end()
    # assert
    assert a.rows() == 3
    assert a.columns() == 4
    assert a.dtype() == numpy.dtypes.Complex64DType()
    assert a.is_complex()
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    for c in range(4):
        for r in range(3):
            assert a.get(r, c) == 0 + 0j

    # act
    telemetry_tests.start()
    b = DenseMatrix(numpy.dtypes.Int32DType(), 2, 4, False)
    telemetry_tests.end()
    # assert
    assert b.rows() == 2
    assert b.columns() == 4
    assert b.dtype() == numpy.dtypes.Int32DType()
    assert not b.is_complex()
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))
    # TODO: Check if data is not nullptr

def test_DenseMatrix_list_constructor():
    # act
    telemetry_tests.start()
    a = DenseMatrix([[1, 2, 3], [4, 5, 6]])
    telemetry_tests.end()
    # assert
    assert a.rows() == 2
    assert a.columns() == 3
    assert a.dtype() == numpy.dtypes.UInt8DType()
    assert not a.is_complex()
    # TODO: Replace with compare
    assert a[0, 0] == 1
    assert a[0, 1] == 2
    assert a[0, 2] == 3
    assert a[1, 0] == 4
    assert a[1, 1] == 5
    assert a[1, 2] == 6

    # act
    telemetry_tests.start()
    b = DenseMatrix(numpy.array([[1, 2, 3], [4, 5, 6]], dtype=numpy.float32))
    telemetry_tests.end()
    # assert
    assert b.rows() == 2
    assert b.columns() == 3
    assert b.dtype() == numpy.dtypes.Float32DType()
    assert not b.is_complex()
    # TODO: Replace with compare
    assert b[0, 0] == 1
    assert b[0, 1] == 2
    assert b[0, 2] == 3
    assert b[1, 0] == 4
    assert b[1, 1] == 5
    assert b[1, 2] == 6
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    # act
    telemetry_tests.start()
    c = DenseMatrix(numpy.dtypes.Float32DType(), [[1, 2, 3], [4, 5, 6]])
    telemetry_tests.end()
    # assert
    assert c.rows() == 2
    assert c.columns() == 3
    assert c.dtype() == numpy.dtypes.Float32DType()
    assert not c.is_complex()
    # TODO: Replace with compare
    assert c[0, 0] == 1
    assert c[0, 1] == 2
    assert c[0, 2] == 3
    assert c[1, 0] == 4
    assert c[1, 1] == 5
    assert c[1, 2] == 6
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    # act
    telemetry_tests.start()
    d = DenseMatrix(numpy.dtypes.Float64DType(), numpy.array([[1, 2, 3], [4, 5, 6]], dtype=numpy.float32))
    telemetry_tests.end()
    # assert
    assert d.rows() == 2
    assert d.columns() == 3
    assert d.dtype() == numpy.dtypes.Float64DType()
    assert not d.is_complex()
    # TODO: Replace with compare
    assert d[0, 0] == 1
    assert d[0, 1] == 2
    assert d[0, 2] == 3
    assert d[1, 0] == 4
    assert d[1, 1] == 5
    assert d[1, 2] == 6
    telemetry_tests.asserts(TelemetryStats(allocations=1, move_constructs=1))

    # act / assert
    with pytest.raises(TypeError):
        DenseMatrix(numpy.dtypes.Int32DType(), [[1, 2.5, 3], [4, 5, 6 + 4j]])

    # act / assert
    with pytest.raises(TypeError):
        DenseMatrix([[1, 2.5, 3], [4, 5]])

def test_DenseMatrix_copy_constructor_from_same_type():
    # arrange
    a = DenseMatrix(numpy.dtypes.Int32DType(), [[1, 2, 6, 7], [2, 6, -5, 1], [6, -65, 12, 99]])
    # act
    telemetry_tests.start()
    b = DenseMatrix.copy(a)
    telemetry_tests.end()
    # assert
    assert b.rows() == 3
    assert b.columns() == 4
    assert b.dtype() == numpy.dtypes.Int32DType()
    assert not b.is_complex()
    # TODO: Replace with compare
    assert b[0, 0] == 1
    assert b[0, 1] == 2
    assert b[0, 2] == 6
    assert b[0, 3] == 7
    assert b[1, 0] == 2
    assert b[1, 1] == 6
    assert b[1, 2] == -5
    assert b[1, 3] == 1
    assert b[2, 0] == 6
    assert b[2, 1] == -65
    assert b[2, 2] == 12
    assert b[2, 3] == 99
    telemetry_tests.asserts(TelemetryStats(copy_constructs=1, move_constructs=1, allocations=1))

def test_DenseMatrix_copy_constructor_from_diff_type():
    # arrange
    a = DenseMatrix(numpy.dtypes.Int32DType(), [[1, 2, 6, 7], [2, 6, -5, 1], [6, -65, 12, 99]])
    # act
    telemetry_tests.start()
    b = DenseMatrix.copy(numpy.dtypes.Int64DType(), a)
    telemetry_tests.end()
    # assert
    assert b.rows() == 3
    assert b.columns() == 4
    assert b.dtype() == numpy.dtypes.Int64DType()
    assert not b.is_complex()
    # TODO: Replace with compare
    assert b[0, 0] == 1
    assert b[0, 1] == 2
    assert b[0, 2] == 6
    assert b[0, 3] == 7
    assert b[1, 0] == 2
    assert b[1, 1] == 6
    assert b[1, 2] == -5
    assert b[1, 3] == 1
    assert b[2, 0] == 6
    assert b[2, 1] == -65
    assert b[2, 2] == 12
    assert b[2, 3] == 99
    telemetry_tests.asserts(TelemetryStats(copy_constructs=1, move_constructs=1, allocations=1))
