import mathpy
import numpy
import pytest


def test_Precision_constructor_and_dtype_and_value_read():
    # arrange / act
    a = mathpy.Precision(1)
    # assert
    assert a.dtype == numpy.dtypes.UInt8DType()
    # arrange / act
    b = mathpy.Precision(-130)
    # assert
    assert b.dtype == numpy.dtypes.Int16DType()
    # arrange / act
    c = mathpy.Precision(numpy.float32(3.14))
    # assert
    assert c.dtype == numpy.dtypes.Float32DType()
    # arrange / act
    d = mathpy.Precision(2.0)
    # assert
    assert d.dtype == numpy.dtypes.Float64DType()
    # arrange / act / assert
    with pytest.raises(TypeError):
        mathpy.Precision(1 + 2j)
    # arrange / act / assert
    with pytest.raises(TypeError):
        mathpy.Precision(numpy.complex64())
    # arrange
    e = mathpy.Precision(4264)
    # act
    e_value = e.value
    # assert
    assert e_value == 4264
    # arrange
    f = mathpy.Precision(-5.25)
    # act
    f_value = f.value
    # assert
    assert f_value == -5.25

def test_Precision_value_write():
    # arrange
    a = mathpy.Precision(3.14)
    # act
    a.value = -21
    # assert
    assert a.dtype == numpy.dtypes.Float64DType()
    assert a.value == numpy.float64(-21)
    # arrange
    b = mathpy.Precision(6)
    # act / assert
    with pytest.raises(TypeError):
        b.value = -1
    # arrange
    c = mathpy.Precision(6)
    # act / assert
    with pytest.raises(TypeError):
        c.value = 256

def test_Precision_as_type():
    # arrange
    a = mathpy.Precision(4)
    # act
    a_as_float = a.astype(numpy.dtypes.Float32DType())
    # assert
    assert a_as_float.dtype == numpy.dtypes.Float32DType()
    assert a_as_float.value == numpy.float32(4.0)
    # arrange
    b = mathpy.Precision(-3.14)
    # act
    b_as_int16 = b.astype(numpy.dtypes.Int16DType())
    # assert
    assert b_as_int16.dtype == numpy.dtypes.Int16DType()
    assert b_as_int16.value == numpy.int16(-3)
    # arrange
    b = mathpy.Precision(0.67)
    # act / assert
    with pytest.raises(TypeError):
        b.astype(numpy.dtypes.Complex64DType())