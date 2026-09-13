from mathpy import *
import numpy
import pytest

from .simple_vector_like import SimpleVectorLike

def test_assert_same_size():
    # arrange
    a = SimpleVectorLike(3, numpy.dtypes.Float32DType())
    b = SimpleVectorLike(3, numpy.dtypes.Int16DType())
    c = SimpleVectorLike(3, numpy.dtypes.Complex128DType())
    # act / assert
    assert_same_size(a, b, c)
    # arrange
    d = SimpleVectorLike(3, numpy.dtypes.Float32DType())
    e = SimpleVectorLike(2, numpy.dtypes.Int16DType())
    f = SimpleVectorLike(3, numpy.dtypes.Complex128DType())
    # act / assert
    with pytest.raises(ValueError):
        assert_same_size(d, e, f)
