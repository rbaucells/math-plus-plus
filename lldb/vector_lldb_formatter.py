from typing import Callable

# maximum size for which a full vector view is rendered
_MAX_VIEW_DIM: int = 7


def format_vector_summary(n: int, get_element: Callable[[int], str]) -> str:
    # build compact single-line summary: [a, b, c]
    element_strs: list[str] = [get_element(i) for i in range(n)]
    # exit
    return "[" + ", ".join(element_strs) + "]"
