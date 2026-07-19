import mathpy
import numpy

def test_get_py_int_dtype():
    # act / assert
    assert mathpy.get_py_int_dtype(25) == numpy.dtypes.UInt8DType()
    assert mathpy.get_py_int_dtype(-25) == numpy.dtypes.Int8DType()
    assert mathpy.get_py_int_dtype(300) == numpy.dtypes.UInt16DType()
    assert mathpy.get_py_int_dtype(-130) == numpy.dtypes.Int16DType()
    assert mathpy.get_py_int_dtype(70000) == numpy.dtypes.UInt32DType()
    assert mathpy.get_py_int_dtype(-35000) == numpy.dtypes.Int32DType()
    assert mathpy.get_py_int_dtype(5000000000) == numpy.dtypes.UInt64DType()
    assert mathpy.get_py_int_dtype(-3000000000) == numpy.dtypes.Int64DType()

def test_get_dtype():
    # act / assert
    assert mathpy.get_dtype(25) == numpy.dtypes.UInt8DType()
    assert mathpy.get_dtype(-25) == numpy.dtypes.Int8DType()
    assert mathpy.get_dtype(300) == numpy.dtypes.UInt16DType()
    assert mathpy.get_dtype(-130) == numpy.dtypes.Int16DType()
    assert mathpy.get_dtype(70000) == numpy.dtypes.UInt32DType()
    assert mathpy.get_dtype(-35000) == numpy.dtypes.Int32DType()
    assert mathpy.get_dtype(5000000000) == numpy.dtypes.UInt64DType()
    assert mathpy.get_dtype(-3000000000) == numpy.dtypes.Int64DType()
    assert mathpy.get_dtype(3.12) == numpy.dtypes.Float64DType()
    assert mathpy.get_dtype(float(12000)) == numpy.dtypes.Float64DType()
    assert mathpy.get_dtype(numpy.int32(12)) == numpy.dtypes.Int32DType()
    assert mathpy.get_dtype(numpy.uint64(32456)) == numpy.dtypes.UInt64DType()
    assert mathpy.get_dtype(numpy.float32(6.7)) == numpy.dtypes.Float32DType()
    assert mathpy.get_dtype(numpy.complex64(6.7 + 113j)) == numpy.dtypes.Complex64DType()

def test_get_common_dtype():
    # arrange
    a = [-25, 25]
    # act / assert
    assert mathpy.get_common_dtype(a) == numpy.dtypes.Int16DType()
    # arrange
    # b = numpy.array(numpy.int32(-12), numpy.uint32(12))
    b = [numpy.int32(-12), numpy.uint32(12)]
    # act / assert
    assert mathpy.get_common_dtype(b) == numpy.dtypes.Int64DType()
    # arrange
    c = [numpy.uint8(35), -5, 33000]
    # act / assert
    assert mathpy.get_common_dtype(c) == numpy.dtypes.Int32DType()
    # arrange
    d = [numpy.float32(3.14), -35000]
    # act / assert
    assert mathpy.get_common_dtype(d) == numpy.dtypes.Float64DType()
    # arrange
    e = [numpy.float64(3.14), 5]
    # act / assert
    assert mathpy.get_common_dtype(e) == numpy.dtypes.Float64DType()
    # arrange
    f = [float(3.14), numpy.float32(24.12)]
    # act / assert
    assert mathpy.get_common_dtype(f) == numpy.dtypes.Float64DType()
    # arrange
    g = [numpy.float32(3.14), numpy.complex64(12 + 3.14j)]
    # act / assert
    assert mathpy.get_common_dtype(g) == numpy.dtypes.Complex64DType()
    # arrange
    h = [numpy.float64(3.14), numpy.complex64(12 + 3.14j)]
    # act / assert
    assert mathpy.get_common_dtype(h) == numpy.dtypes.Complex128DType()
    # arrange
    i = [5, numpy.complex64(12 + 3.14j)]
    # act / assert
    assert mathpy.get_common_dtype(i) == numpy.dtypes.Complex64DType()
    # arrange
    j = [-35000, numpy.complex64(12 + 3.14j)]
    # act / assert
    assert mathpy.get_common_dtype(j) == numpy.dtypes.Complex128DType()
    # arrange
    k = [2, complex(12 + 3.14j)]
    # act / assert
    assert mathpy.get_common_dtype(k) == numpy.dtypes.Complex128DType()
    # arrange
    l = numpy.array([numpy.int32(-14), numpy.float32(4.13)])
    # act / assert
    assert mathpy.get_common_dtype(l) == numpy.dtypes.Float64DType()
    # arrange
    m = numpy.array([numpy.int32(-14), numpy.float32(4.13)], dtype=numpy.complex128)
    # act / assert
    assert mathpy.get_common_dtype(m) == numpy.dtypes.Complex128DType()