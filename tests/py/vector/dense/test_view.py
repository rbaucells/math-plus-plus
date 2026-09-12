from mathpy import *
import numpy
import pytest

from .simple_dense_vector_like import SimpleDenseVectorLike
from ... import telemetry_tests


def test_DenseVectorView_constructor():
    # arrange
    owner = DenseVector([1, 2, 3, 4, 5])
    # act
    telemetry_tests.start()
    view = DenseVectorView(owner, 3, 1)
    telemetry_tests.end()
    # assert
    assert view.n() == 3
    assert view.offset() == 1
    assert view.dtype() == numpy.dtypes.UInt8DType()
    assert not view.is_complex()
    assert view[0] == 2
    assert view[1] == 3
    assert view[2] == 4
    telemetry_tests.asserts(TelemetryStats())

def test_DenseVectorView_dtype():
    # arrange
    vec_a = DenseVector([1, 2, 3, 4])
    view_a = DenseVectorView(vec_a, 2, 1)
    # act
    a_dt = view_a.dtype()
    # assert
    assert a_dt == numpy.dtypes.UInt8DType()
    # arrange
    vec_b = DenseVector(numpy.dtypes.Complex128DType(), [1, 2, 3, 4])
    view_b = DenseVectorView(vec_b, 2, 1)
    # act
    b_dt = view_b.dtype()
    # assert
    assert b_dt == numpy.dtypes.Complex128DType()

def test_DenseVectorView_n():
    # arrange
    owner = DenseVector([1, 2, 3, 4, 5])
    view = DenseVectorView(owner, 3, 1)
    # act
    n = view.n()
    # assert
    assert n == 3

def test_DenseVectorView_offset():
    # arrange
    owner = DenseVector([1, 2, 3, 4, 5])
    view = DenseVectorView(owner, 2, 3)
    # act
    offset = view.offset()
    # assert
    assert offset == 3

def test_DenseVectorView_get():
    # arrange
    owner = DenseVector([10, 11, 12, 13, 14, 15])
    view = DenseVectorView(owner, 3, 2)
    # act
    telemetry_tests.start()
    val = view.get(1)
    telemetry_tests.end()
    # assert
    assert val == 13
    telemetry_tests.asserts(TelemetryStats())

    # act / assert
    with pytest.raises(ValueError):
        view.get(3)

def test_DenseVectorView_set():
    # arrange
    owner = DenseVector([1, 2, 3, 4])
    view = DenseVectorView(owner, 2, 1)
    # act / assert
    with pytest.raises(TypeError):
        view.set(0, 10)

def test_DenseVectorView_indexing_operator():
    # arrange
    owner = DenseVector([1, 2, 3, 4, 5])
    view = DenseVectorView(owner, 3, 1)
    # act
    telemetry_tests.start()
    val = view[1]
    telemetry_tests.end()
    # assert
    assert val == 3
    telemetry_tests.asserts(TelemetryStats())
    # act / assert
    with pytest.raises(TypeError):
        view[0] = 10


def test_DenseVectorView_is_complex():
    # arrange
    owner_real = DenseVector(numpy.dtypes.Float32DType(), 5)
    view_real = DenseVectorView(owner_real, 3, 1)
    # act
    real_is_complex = view_real.is_complex()
    # assert
    assert not real_is_complex
    # arrange
    owner_complex = DenseVector(numpy.dtypes.Complex64DType(), 5)
    view_complex = DenseVectorView(owner_complex, 3, 1)
    # act
    complex_is_complex = view_complex.is_complex()
    # assert
    assert complex_is_complex

def test_DenseVectorView_owner_lifetime_keep_alive():
    # arrange / act
    def create_view():
        # Temporary owner vector dropped when function exits
        temp_owner = DenseVector([1, 2, 3, 4])
        return DenseVectorView(temp_owner, 2, 1)

    view = create_view()

    # act
    telemetry_tests.start()
    val = view[1]
    telemetry_tests.end()

    # assert
    # Ensures keep_alive<1, 2> binding prevented garbage collection of underlying owner
    assert val == 3
    telemetry_tests.asserts(TelemetryStats())
