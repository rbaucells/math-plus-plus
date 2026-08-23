import mathpy
import numpy
import pytest
from ... import telemetry_tests


def test_DenseMatrix_empty_constructor():
    # act
    m = mathpy.DenseMatrix(numpy.dtypes.Float32DType())
    # assert
    assert m.rows() == 0
    assert m.columns() == 0
    assert m.dtype() == numpy.dtypes.Float32DType()
    assert not m.is_complex()

def test_DenseMatrix_sized_constructor():
    # act
    a = mathpy.DenseMatrix(numpy.dtypes.Complex64DType(), 3, 4, True)
    # assert
    assert a.rows() == 3
    assert a.columns() == 4
    assert a.dtype() == numpy.dtypes.Complex64DType()
    assert a.is_complex()

    for c in range(4):
        for r in range(3):
            assert a.get(r, c) == 0 + 0j

    # act
    b = mathpy.DenseMatrix(numpy.dtypes.Int32DType(), 2, 4, False)
    # assert
    assert b.rows() == 2
    assert b.columns() == 4
    assert b.dtype() == numpy.dtypes.Int32DType()
    assert not b.is_complex()

def test_DenseMatrix_copy_constructor():
    # arrange
    a = mathpy.DenseMatrix(numpy.dtypes.Int32DType(), 3, 4, True)
    a[1, 1] = 4
    a[0, 2] = 6
    a[2, 3] = 8
    telemetry_tests.start()
    # act
    b = mathpy.DenseMatrix.copy(a)
    telemetry_tests.end()
    # assert
    assert b.rows() == 3
    assert b.columns() == 4
    assert b.dtype() == numpy.dtypes.Int32DType()
    assert not b.is_complex()
    assert b.get(1, 1) == 4
    assert b[0, 2] == 6
    assert b.get(2, 3) == 8
    telemetry_tests.asserts(mathpy.TelemetryStats(copy_constructs=1, move_constructs=1, allocations=1))