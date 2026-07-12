import mathpy

# def test_answer():
#     result = mathpy.compare(mathpy.Precision(0.14), 1, 2.1, 3)
#     assert result == True

def test_answer2():
    result = mathpy.compare(mathpy.Precision(0.14), 1, 2.1, 3)
    assert result == False
    