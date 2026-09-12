import typing
from typing import Any

import numpy
from mathpy import *

class SimpleDenseVectorLike(DenseVectorLike):
    def __init__(self, data: list[Any]):
        super().__init__()
        self.data: list[Any] = data
        self.n_ = len(data)
        self.dtype_ = detail.get_sequence_info(data)[0]

    def __getitem__(self, i: typing.SupportsInt | typing.SupportsIndex) -> typing.Any:
        return self.data[i]

    def __setitem__(self, i: typing.SupportsInt | typing.SupportsIndex, v: typing.Any) -> None:
        self.data[i] = v

    def dtype(self) -> numpy.dtype[typing.Any]:
        return self.dtype_

    def get(self, i: typing.SupportsInt | typing.SupportsIndex) -> typing.Any:
        if i > self.n_:
            raise IndexError()

        return self.data[i]

    def is_complex(self) -> bool:
        return self.dtype_ == numpy.dtypes.Complex64DType or self.dtype_ == numpy.dtypes.Complex128DType

    def n(self) -> int:
        return self.n_

    def set(self, i: typing.SupportsInt | typing.SupportsIndex, v: typing.Any) -> None:
        if i > self.n_:
            raise IndexError()

        self.data[i] = v


