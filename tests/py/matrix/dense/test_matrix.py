import mathpy
import numpy
import pytest

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

def test_DenseMatrix_set():
    # arrange
    a = mathpy.DenseMatrix(numpy.dtypes.Int32DType(), 3, 3)
    # act
    a.set(2, 2, 8)
    # assert
    assert a[2, 2] == 8
    assert a[2, 3] == 0
