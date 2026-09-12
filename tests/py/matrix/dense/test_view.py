from mathpy import *
import numpy
import pytest

from .simple_dense_matrix_like import SimpleDenseMatrixLike
from ... import telemetry_tests


def test_DenseMatrixView_constructor():
    # arrange
    owner = DenseMatrix([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
    # act
    telemetry_tests.start()
    view = DenseMatrixView(owner, 2, 3, 1, 1)
    telemetry_tests.end()
    # assert
    assert view.rows() == 2
    assert view.columns() == 3
    assert view.row_offset() == 1
    assert view.col_offset() == 1
    assert view.dtype() == numpy.dtypes.UInt8DType()
    assert not view.is_complex()
    assert view[0, 0] == 6
    assert view[0, 1] == 7
    assert view[0, 2] == 8
    assert view[1, 0] == 10
    assert view[1, 1] == 11
    assert view[1, 2] == 12
    telemetry_tests.asserts(TelemetryStats())

def test_DenseMatrixView_dtype():
    # arrange
    mat_a = DenseMatrix([[1, 2], [3, 4]])
    view_a = DenseMatrixView(mat_a, 2, 2, 0, 0)
    # act
    a_dt = view_a.dtype()
    # assert
    assert a_dt == numpy.dtypes.UInt8DType()
    # arrange
    mat_b = DenseMatrix(numpy.dtypes.Complex128DType(), 3, 3, True)
    view_b = DenseMatrixView(mat_b, 2, 2, 0, 0)
    # act
    b_dt = view_b.dtype()
    # assert
    assert b_dt == numpy.dtypes.Complex128DType()


def test_DenseMatrixView_rows():
    # arrange
    owner = DenseMatrix(numpy.dtypes.Float32DType(), 5, 5)
    view = DenseMatrixView(owner, 3, 2, 1, 1)
    # act
    rows = view.rows()
    # assert
    assert rows == 3


def test_DenseMatrixView_columns():
    # arrange
    owner = DenseMatrix(numpy.dtypes.Float32DType(), 5, 5)
    view = DenseMatrixView(owner, 3, 2, 1, 1)
    # act
    cols = view.columns()
    # assert
    assert cols == 2


def test_DenseMatrixView_row_offset():
    # arrange
    owner = DenseMatrix(numpy.dtypes.Float32DType(), 5, 5)
    view = DenseMatrixView(owner, 2, 2, 3, 1)
    # act
    row_offset = view.row_offset()
    # assert
    assert row_offset == 3


def test_DenseMatrixView_col_offset():
    # arrange
    owner = DenseMatrix(numpy.dtypes.Float32DType(), 5, 5)
    view = DenseMatrixView(owner, 2, 2, 1, 4)
    # act
    col_offset = view.col_offset()
    # assert
    assert col_offset == 4


def test_DenseMatrixView_get():
    # arrange
    owner = DenseMatrix([[10, 11, 12], [13, 14, 15], [16, 17, 18]])
    view = DenseMatrixView(owner, 2, 2, 1, 1)
    # act
    telemetry_tests.start()
    val = view.get(1, 1)
    telemetry_tests.end()
    # assert
    assert val == 18
    telemetry_tests.asserts(TelemetryStats())

    # act / assert
    with pytest.raises(ValueError):
        view.get(2, 0)
    # act / assert
    with pytest.raises(ValueError):
        view.get(0, 2)


def test_DenseMatrixView_set():
    # arrange
    owner = DenseMatrix([[1, 2], [3, 4]])
    view = DenseMatrixView(owner, 2, 2, 0, 0)
    # act / assert
    with pytest.raises(TypeError):
        view.set(0, 0, 10)

def test_DenseMatrixView_indexing_operator():
    # arrange
    owner = DenseMatrix([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
    view = DenseMatrixView(owner, 2, 2, 1, 2)
    # act
    telemetry_tests.start()
    val = view[1, 1]
    telemetry_tests.end()
    # assert
    assert val == 12
    telemetry_tests.asserts(TelemetryStats())
    # act / assert
    with pytest.raises(TypeError):
        view[0, 0] = 10


def test_DenseMatrixView_is_complex():
    # arrange
    owner_real = DenseMatrix(numpy.dtypes.Float32DType(), 3, 4)
    view_real = DenseMatrixView(owner_real, 2, 2, 0, 0)
    # act
    real_is_complex = view_real.is_complex()
    # assert
    assert not real_is_complex

    # arrange
    owner_complex = DenseMatrix(numpy.dtypes.Complex64DType(), 3, 4)
    view_complex = DenseMatrixView(owner_complex, 2, 2, 0, 0)
    # act
    complex_is_complex = view_complex.is_complex()
    # assert
    assert complex_is_complex


def test_DenseMatrixView_owner_lifetime_keep_alive():
    # arrange / act
    def create_view():
        # Temporary owner matrix dropped when function exits
        temp_owner = DenseMatrix([[1, 2], [3, 4]])
        return DenseMatrixView(temp_owner, 1, 1, 1, 1)

    view = create_view()

    # act
    telemetry_tests.start()
    val = view[0, 0]
    telemetry_tests.end()

    # assert
    # Ensures keep_alive<1, 2> binding prevented garbage collection of underlying owner
    assert val == 4
    telemetry_tests.asserts(TelemetryStats())