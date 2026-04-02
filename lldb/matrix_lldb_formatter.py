# shared matrix formatting utilities used by all matrix type formatters
# concrete formatters supply a get_element(row, col) -> str callable and delegate here for layout
from typing import Callable

# maximum dimension for which a full view is rendered (avoids expensive string building for large matrices)
_MAX_VIEW_DIM: int = 10

# unicode bracket characters for LaTeX-style multi-line matrix display
_BRACKET_TOP_LEFT:  str = "\u23a1"   # ⎡
_BRACKET_MID_LEFT:  str = "\u23a2"   # ⎢
_BRACKET_BOT_LEFT:  str = "\u23a3"   # ⎣
_BRACKET_TOP_RIGHT: str = "\u23a4"   # ⎤
_BRACKET_MID_RIGHT: str = "\u23a5"   # ⎥
_BRACKET_BOT_RIGHT: str = "\u23a6"   # ⎦


def format_matrix_summary(rows: int, columns: int, get_element: Callable[[int, int], str]) -> str:
    # build compact single-line MATLAB-style summary: [a, b; c, d]
    # rows separated by ';', columns separated by ','
    row_strs: list[str] = [", ".join(get_element(r, c) for c in range(columns)) for r in range(rows)]
    # exit
    return "[" + "; ".join(row_strs) + "]"


def format_matrix_display(rows: int, columns: int, get_element: Callable[[int, int], str]) -> str:
    # first pass: materialise all element strings in row-major order
    strings: list[list[str]] = [[get_element(r, c) for c in range(columns)] for r in range(rows)]
    # compute per-column max widths for right-justified alignment
    col_widths: list[int] = [max(len(strings[r][c]) for r in range(rows)) for c in range(columns)]
    # second pass: assemble bracket lines using unicode glyphs
    lines: list[str] = []
    # loop over rows
    for r in range(rows):
        # join columns with two-space separator, right-justified to column width
        row_content: str = "  ".join(strings[r][c].rjust(col_widths[c]) for c in range(columns))
        # select left/right bracket glyph based on row position
        if rows == 1:
            left, right = "[ ", " ]"
        elif r == 0:
            left, right = _BRACKET_TOP_LEFT + " ", " " + _BRACKET_TOP_RIGHT
        elif r == rows - 1:
            left, right = _BRACKET_BOT_LEFT + " ", " " + _BRACKET_BOT_RIGHT
        else:
            left, right = _BRACKET_MID_LEFT + " ", " " + _BRACKET_MID_RIGHT
        # append line with 3-space indent and brackets
        lines.append(f"   {left}{row_content}{right}")
    # exit
    return "\n".join(lines)
