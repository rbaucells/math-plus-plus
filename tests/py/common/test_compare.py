import mathpy
import numpy
import pytest

def test_precision_and_args_compare():
    # arrange
    a = 1.0
    b = 0.9
    c = 1
    # act
    abcResult = mathpy.compare(mathpy.Precision(0.1), a, b, c)
    # assert
    assert abcResult
    # arrange
    d = -2
    e = 2
    f = 0
    # act
    defResult = mathpy.compare(mathpy.Precision(numpy.uint8(4)), d, e, f)
    # assert
    assert defResult
    # arrange
    g = numpy.complex64(2 - 4j)
    h = numpy.complex64(1.9 - 3.9j)
    # act
    # 1.000001 because of float imprecision
    ghResult = mathpy.compare(mathpy.Precision(numpy.float32(0.100001)), g, h)
    # assert
    assert ghResult
    # arrange
    i = numpy.int32(3)
    j = numpy.float32(6.92)
    # act
    ijResult = mathpy.compare(mathpy.Precision(numpy.float64(0.001)), i, j)
    # assert
    assert not ijResult
    # arrange
    k = 255
    l = 255.4
    # act
    klResult = mathpy.compare(mathpy.Precision(0.3), k, l)
    # assert
    assert not klResult
    # arrange
    m = numpy.int8(-2)
    n = numpy.uint8(2)
    o = numpy.uint8(0)
    # act
    with pytest.raises(TypeError):
        mathpy.compare(mathpy.Precision(numpy.uint16(4)), m, n, o)

def test_precision_and_iterable_compare():
    # arrange
    a = 1.0
    b = 0.9
    c = 1
    # act
    abcResult = mathpy.compare(mathpy.Precision(0.1), [a, b, c])
    # assert
    assert abcResult
    # arrange
    d = -2
    e = 2
    f = 0
    # act / assert
    with pytest.raises(TypeError):
        mathpy.compare(mathpy.Precision(numpy.uint8(4)), numpy.array([d, e, f]))
    # arrange
    g = numpy.complex64(2 - 4j)
    h = numpy.complex64(1.9 - 3.9j)
    # act
    # 1.000001 because of float imprecision
    ghResult = mathpy.compare(mathpy.Precision(numpy.float32(0.100001)), numpy.array([g, h]))
    # assert
    assert ghResult
    # arrange
    i = numpy.int32(3)
    j = numpy.float32(6.92)
    # act
    ijResult = mathpy.compare(mathpy.Precision(numpy.float64(0.001)), [i, j])
    # assert
    assert not ijResult
    # arrange
    k = 255
    l = 255.4
    # act
    klResult = mathpy.compare(mathpy.Precision(0.3), [k, l])
    # assert
    assert not klResult
    # arrange
    m = numpy.int8(-2)
    n = numpy.uint8(2)
    o = numpy.uint8(0)
    # act
    with pytest.raises(TypeError):
        mathpy.compare(mathpy.Precision(numpy.uint8(4)), numpy.array([m, n, o]))

def test_args_compare():
    # arrange
    a = 1.0
    b = 1.0
    # act
    abResult = mathpy.compare(a, b)
    # assert
    assert abResult
    # arrange
    c = numpy.float64(1.0)
    d = 1.0
    # act
    cdResult = mathpy.compare(c, d)
    # assert
    assert cdResult
    # arrange
    e = 1.0
    f = 0.9
    # act
    efResult = mathpy.compare(e, f)
    # assert
    assert not efResult
    # arrange
    g = numpy.complex128(2 - 4j)
    h = numpy.complex64(2 - 4j)
    # act
    ghResult = mathpy.compare(g, h)
    # assert
    assert ghResult
    # arrange
    i = numpy.complex64(2 - 4j)
    j = numpy.complex64(1.9 - 3.9j)
    # act
    ijResult = mathpy.compare(i, j)
    # assert
    assert not ijResult
    # arrange
    k = 1
    l = numpy.uint16(1)
    # act
    klResult = mathpy.compare(k, l)
    # assert
    assert klResult
    # arrange
    m = 1
    n = 2
    o = 3
    # act
    mnoResult = mathpy.compare(m, n, o)
    # assert
    assert not mnoResult
    # arrange
    p = 1
    q = 1.0
    r = 1 + 0j
    # act
    pqrResult = mathpy.compare(p, q, r)
    # assert
    assert pqrResult
    # arrange / act / assert
    with pytest.raises(TypeError):
        mathpy.compare("hello", 1.0)

def test_iterable_compare():
    # arrange
    a = 1.0
    b = 1.0
    # act
    abResult = mathpy.compare([a, b])
    # assert
    assert abResult
    # arrange
    c = numpy.float64(1.0)
    d = numpy.int64(1)
    # act
    cdResult = mathpy.compare(numpy.array([c, d]))
    # assert
    assert cdResult
    # arrange
    e = 1.0
    f = 0.9
    # act
    efResult = mathpy.compare([e, f])
    # assert
    assert not efResult
    # arrange
    g = numpy.complex64(2 - 4j)
    h = numpy.complex128(2 - 4j)
    # act
    ghResult = mathpy.compare(numpy.array([g, h]))
    # assert
    assert ghResult
    # arrange
    i = numpy.complex64(2 - 4j)
    j = numpy.complex64(1.9 - 3.9j)
    # act
    ijResult = mathpy.compare(numpy.array([i, j]))
    # assert
    assert not ijResult
    # arrange
    k = 1
    l = numpy.uint32(1)
    # act
    klResult = mathpy.compare([k, l])
    # assert
    assert klResult
    # arrange
    m = 1
    n = 2
    o = 3
    # act
    mnoResult = mathpy.compare([m, n, o])
    # assert
    assert not mnoResult
    # arrange
    p = 1
    q = 1.0
    r = 1 + 0j
    # act
    pqrResult = mathpy.compare([p, q, r])
    # assert
    assert pqrResult
    # arrange / act / assert
    with pytest.raises(TypeError):
        mathpy.compare(["hello", 1.0])