from mathpy import *
import numpy
import pytest

from .simple_matrix_like import SimpleMatrixLike


def test_assert_square():
    # arrange
    a = SimpleMatrixLike(3, 3, numpy.dtypes.Float32DType())
    # act / assert
    assert_square(a)
    # arrange
    b = SimpleMatrixLike(3, 4, numpy.dtypes.Float64DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_square(b)
    # arrange
    c = SimpleMatrixLike(4, 3, numpy.dtypes.Float64DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_square(c)

def test_assert_wide():
    # arrange
    a = SimpleMatrixLike(3, 3, numpy.dtypes.Complex128DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_wide(a)
    # arrange
    b = SimpleMatrixLike(3, 4, numpy.dtypes.Complex64DType())
    # act / assert
    assert_wide(b)
    # arrange
    c = SimpleMatrixLike(4, 3, numpy.dtypes.Int32DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_wide(c)

def test_assert_tall():
    # arrange
    a = SimpleMatrixLike(3, 3, numpy.dtypes.Int64DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_tall(a)
    # arrange
    b = SimpleMatrixLike(3, 4, numpy.dtypes.Complex128DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_tall(b)
    # arrange
    c = SimpleMatrixLike(4, 3, numpy.dtypes.Float32DType())
    # act / assert
    assert_tall(c)


def test_assert_can_multiply():
    # arrange
    a = SimpleMatrixLike(4, 3, numpy.dtypes.Float32DType())
    b = SimpleMatrixLike(3, 4, numpy.dtypes.Complex128DType())
    # act / assert
    assert_can_multiply(a, b)
    # arrange
    c = SimpleMatrixLike(4, 3, numpy.dtypes.Complex64DType())
    d = SimpleMatrixLike(4, 4, numpy.dtypes.Int8DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_can_multiply(c, d)

def test_assert_same_dimensions():
    # arrange
    a = SimpleMatrixLike(3, 3, numpy.dtypes.Int8DType())
    b = SimpleMatrixLike(3, 3, numpy.dtypes.Int16DType())
    c = SimpleMatrixLike(3, 3, numpy.dtypes.Int32DType())
    # act / assert
    assert_same_dimensions(a, b, c)
    # arrange
    d = SimpleMatrixLike(3, 3, numpy.dtypes.Int8DType())
    e = SimpleMatrixLike(3, 3, numpy.dtypes.Int16DType())
    f = SimpleMatrixLike(2, 3, numpy.dtypes.Int32DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_same_dimensions(d, e, f)
