Example test names:
    - lu_decomp_wide
    - fail_lu_decomp_square_zero_column
    - cholesky_complex_not_hermitian_skip_checks
    - fail_cholesky_real_not_symmetric
    - not_row_echelon_wide_zero_row
    - inverse_2x2
    - division_same_type_scalar

Tests on checks should have one true check, and one false check. Example:
    - row_echelon_wide
    - not_row_echelon_wide_zero_row

Tests on decomposition should compare against known decomposition. if not unique, test if calculatedA == a

Tests on general should compare against known, or compare against a neccasary and sufficient characteristic. Example: inverse x matrix == identity

Tests on eigen should compare against known, or check if eigen vec * matrix == eigen vec * eigen val