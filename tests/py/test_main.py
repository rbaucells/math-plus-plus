import mathpy
import numpy
import pytest

def test_get_py_int_dtype():
    # act / assert
    assert mathpy.detail.get_py_int_dtype(25) == numpy.dtypes.UInt8DType()
    assert mathpy.detail.get_py_int_dtype(-25) == numpy.dtypes.Int8DType()
    assert mathpy.detail.get_py_int_dtype(300) == numpy.dtypes.UInt16DType()
    assert mathpy.detail.get_py_int_dtype(-130) == numpy.dtypes.Int16DType()
    assert mathpy.detail.get_py_int_dtype(70000) == numpy.dtypes.UInt32DType()
    assert mathpy.detail.get_py_int_dtype(-35000) == numpy.dtypes.Int32DType()
    assert mathpy.detail.get_py_int_dtype(5000000000) == numpy.dtypes.UInt64DType()
    assert mathpy.detail.get_py_int_dtype(-3000000000) == numpy.dtypes.Int64DType()

def test_get_dtype():
    # act / assert
    assert mathpy.detail.get_dtype(25) == numpy.dtypes.UInt8DType()
    assert mathpy.detail.get_dtype(-25) == numpy.dtypes.Int8DType()
    assert mathpy.detail.get_dtype(300) == numpy.dtypes.UInt16DType()
    assert mathpy.detail.get_dtype(-130) == numpy.dtypes.Int16DType()
    assert mathpy.detail.get_dtype(70000) == numpy.dtypes.UInt32DType()
    assert mathpy.detail.get_dtype(-35000) == numpy.dtypes.Int32DType()
    assert mathpy.detail.get_dtype(5000000000) == numpy.dtypes.UInt64DType()
    assert mathpy.detail.get_dtype(-3000000000) == numpy.dtypes.Int64DType()
    assert mathpy.detail.get_dtype(3.12) == numpy.dtypes.Float64DType()
    assert mathpy.detail.get_dtype(float(12000)) == numpy.dtypes.Float64DType()
    assert mathpy.detail.get_dtype(numpy.int32(12)) == numpy.dtypes.Int32DType()
    assert mathpy.detail.get_dtype(numpy.uint64(32456)) == numpy.dtypes.UInt64DType()
    assert mathpy.detail.get_dtype(numpy.float32(6.7)) == numpy.dtypes.Float32DType()
    assert mathpy.detail.get_dtype(numpy.complex64(6.7 + 113j)) == numpy.dtypes.Complex64DType()

def test_get_sequence_info():
    # arrange
    a = [25, -25, 25]
    aExpected = (numpy.dtypes.Int16DType(), mathpy.detail.EType.scalar, 3)
    # act
    aResult = mathpy.detail.get_sequence_info(a)
    # assert
    assert aResult == aExpected
    # arrange
    b = [3, -3, 2.6, 4]
    bExpected = (numpy.dtypes.Float64DType(), mathpy.detail.EType.scalar, 4)
    # act
    bResult = mathpy.detail.get_sequence_info(b)
    # assert
    assert bResult == bExpected
    # arrange
    c = [mathpy.DenseMatrix(numpy.dtypes.Int32DType(), 3, 3), mathpy.DenseMatrix(numpy.dtypes.UInt32DType(), 4, 2)]
    cExpected = (numpy.dtypes.Int64DType(), mathpy.detail.EType.dense_matrix_like, 2)
    # act
    cResult = mathpy.detail.get_sequence_info(c)
    # assert
    assert cResult == cExpected
    # arrange
    d = [[1, 2], [5, 3]]
    # act / assert
    with pytest.raises(TypeError):
        mathpy.detail.get_sequence_info(d)
    # arrange
    e = [2, 4 + 3j]
    eExpected = (numpy.dtypes.Complex128DType(), mathpy.detail.EType.scalar, 2)
    # act
    eResult = mathpy.detail.get_sequence_info(e)
    # assert
    assert eResult == eExpected
    # arrange
    f = [3, mathpy.DenseMatrix(numpy.dtypes.UInt8DType())]
    fExpected = (numpy.dtypes.UInt8DType(), mathpy.detail.EType.invalid, 2)
    # act
    fResult = mathpy.detail.get_sequence_info(f)
    # assert
    assert fResult == fExpected

def test_get_sequence_info_2d():
    # arrange
    a = [[4, -6], [10, 130], [4, 0]]
    aExpected = (numpy.dtypes.Int16DType(), mathpy.detail.EType.scalar, 3, 2)
    # act
    aResult = mathpy.detail.get_sequence_info_2d(a)
    # assert
    assert aResult == aExpected
    # arrange
    b = [[mathpy.DenseMatrix(numpy.dtypes.UInt8DType()), mathpy.DenseMatrix(numpy.dtypes.Int16DType())], [mathpy.DenseMatrix(numpy.dtypes.Float64DType()), mathpy.DenseMatrix(numpy.dtypes.UInt32DType())]]
    bExpected = (numpy.dtypes.Float64DType(), mathpy.detail.EType.dense_matrix_like, 2, 2)
    # act
    bResult = mathpy.detail.get_sequence_info_2d(b)
    # assert
    assert bResult == bExpected
    # arrange
    c = [[1, 2], [3, 4, 5]]
    # act / assert
    with pytest.raises(TypeError):
        mathpy.detail.get_sequence_info_2d(c)
    # arrange
    d = [44, -6, 2 + 3j]
    # act / assert
    with pytest.raises(TypeError):
        mathpy.detail.get_sequence_info_2d(d)
    # arrange
    e = [[1, 2], [[4, 5], [4, 1]]]
    # act / assert
    with pytest.raises(TypeError):
        mathpy.detail.get_sequence_info_2d(e)

def test_get_array_info():
    # dt is object - mixed scalar types
    a = numpy.array([25, -25, 3.5], dtype=object)
    aExpected = (numpy.dtypes.Float64DType(), mathpy.detail.EType.scalar, 3)
    # act
    aResult = mathpy.detail.get_array_info(a)
    # assert
    assert aResult == aExpected
    # dt is object - DenseMatrix
    b = numpy.array([mathpy.DenseMatrix(numpy.dtypes.Int32DType()), mathpy.DenseMatrix(numpy.dtypes.UInt32DType())], dtype=object)
    bExpected = (numpy.dtypes.Int64DType(), mathpy.detail.EType.dense_matrix_like, 2)
    # act
    bResult = mathpy.detail.get_array_info(b)
    # assert
    assert bResult == bExpected
    # dt is defined - int32 array
    c = numpy.array([25, -25, 25], dtype=numpy.int32)
    cExpected = (numpy.dtypes.Int32DType(), mathpy.detail.EType.scalar, 3)
    # act
    cResult = mathpy.detail.get_array_info(c)
    # assert
    assert cResult == cExpected
    # mixed scalars and matrices - invalid et
    d = numpy.array([2, mathpy.DenseMatrix(numpy.dtypes.UInt8DType())], dtype=object)
    dExpected = (numpy.dtypes.UInt8DType(), mathpy.detail.EType.invalid, 2)
    # act
    dResult = mathpy.detail.get_array_info(d)
    # assert
    assert dResult == dExpected
    # non-1d array raises
    e = numpy.array([[1, 2], [3, 4]])
    # act / assert
    with pytest.raises(TypeError):
        mathpy.detail.get_array_info(e)

def test_get_array_info_2d():
    # dt is object - 2D scalar array
    a = numpy.array([[4, -6], [10, 130], [4, 0]], dtype=object)
    aExpected = (numpy.dtypes.Int16DType(), mathpy.detail.EType.scalar, 3, 2)
    # act
    aResult = mathpy.detail.get_array_info_2d(a)
    # assert
    assert aResult == aExpected
    # dt is object - 2D DenseMatrix array
    b = numpy.array([
        [mathpy.DenseMatrix(numpy.dtypes.UInt8DType()), mathpy.DenseMatrix(numpy.dtypes.Int16DType())],
        [mathpy.DenseMatrix(numpy.dtypes.Float64DType()), mathpy.DenseMatrix(numpy.dtypes.UInt32DType())]
    ], dtype=object)
    bExpected = (numpy.dtypes.Float64DType(), mathpy.detail.EType.dense_matrix_like, 2, 2)
    # act
    bResult = mathpy.detail.get_array_info_2d(b)
    # assert
    assert bResult == bExpected
    # dt is defined - 2D int32 array
    c = numpy.array([[1, 2], [3, 4]], dtype=numpy.int32)
    cExpected = (numpy.dtypes.Int32DType(), mathpy.detail.EType.scalar, 2, 2)
    # act
    cResult = mathpy.detail.get_array_info_2d(c)
    # assert
    assert cResult == cExpected
    # mixed scalars and matrices - invalid et
    d = numpy.array([[2, mathpy.DenseMatrix(numpy.dtypes.UInt8DType())], [3, 4]], dtype=object)
    dExpected = (numpy.dtypes.UInt8DType(), mathpy.detail.EType.invalid, 2, 2)
    # act
    dResult = mathpy.detail.get_array_info_2d(d)
    # assert
    assert dResult == dExpected
    # non-2d array raises
    e = numpy.array([1, 2, 3])
    # act / assert
    with pytest.raises(TypeError):
        mathpy.detail.get_array_info_2d(e)