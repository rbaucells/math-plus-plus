import mathpy

def test_get_py_int_dtype():
    a = 25
    b = -25

    assert mathpy.get_py_int_dtype(a)