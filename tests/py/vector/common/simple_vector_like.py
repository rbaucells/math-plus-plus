import numpy
from mathpy import VectorLike

class SimpleVectorLike(VectorLike):
    def __init__(self, n_: int, dtype_: numpy.dtype):
        super().__init__()
        self.n_ = n_
        self.dtype_ = dtype_

    def dtype(self) -> numpy.dtype:
        return self.dtype_

    def get(self, i):
        return None

    def is_complex(self) -> bool:
        return self.dtype_ == numpy.dtypes.Complex64DType or self.dtype_ == numpy.dtypes.Complex128DType

    def n(self) -> int:
        return self.n_

    def set(self, i, v):
        pass
