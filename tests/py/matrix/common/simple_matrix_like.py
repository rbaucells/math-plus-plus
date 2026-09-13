import numpy
from mathpy import MatrixLike

class SimpleMatrixLike(MatrixLike):
    def __init__(self, rows_: int, columns_: int, dtype_: numpy.dtype):
        super().__init__()
        self.rows_ = rows_
        self.columns_ = columns_
        self.dtype_ = dtype_

    def columns(self) -> int:
        return self.columns_

    def dtype(self) -> numpy.dtype:
        return self.dtype_

    def get(self, r, c):
        return None

    def is_complex(self) -> bool:
        return self.dtype_ == numpy.dtypes.Complex64DType or self.dtype_ == numpy.dtypes.Complex128DType

    def rows(self) -> int:
        return self.rows_

    def set(self, r, c, v):
        pass
