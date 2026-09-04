import typing
from typing import Any

import numpy
from mathpy import *

class SimpleDenseMatrixLike(DenseMatrixLike):
    def __init__(self, data: list[list[Any]]):
        super().__init__()
        self.data: list[list[Any]] = data
        self.rows_ = len(data)
        self.columns_ = len(data[0])
        self.dtype_ = detail.get_sequence_info_2d(data)[0]

    def __getitem__(self, indices: tuple[typing.SupportsInt | typing.SupportsIndex, typing.SupportsInt | typing.SupportsIndex]) -> typing.Any:
        return self.data[indices[0]][indices[1]]

    def __setitem__(self, indices: tuple[typing.SupportsInt | typing.SupportsIndex, typing.SupportsInt | typing.SupportsIndex], v: typing.Any) -> None:
        self.data[indices[0]][indices[1]] = v

    def columns(self) -> int:
        return self.columns_

    def dtype(self) -> numpy.dtype[typing.Any]:
        return self.dtype_

    def get(self, r: typing.SupportsInt | typing.SupportsIndex, c: typing.SupportsInt | typing.SupportsIndex) -> typing.Any:
        return self.data[r][c]

    def is_complex(self) -> bool:
        return self.dtype_ == numpy.dtypes.Complex64DType or self.dtype_ == numpy.dtypes.Complex128DType

    def rows(self) -> int:
        return self.rows_

    def set(self, r: typing.SupportsInt | typing.SupportsIndex, c: typing.SupportsInt | typing.SupportsIndex, v: typing.Any) -> None:
        self.data[r][c] = v
