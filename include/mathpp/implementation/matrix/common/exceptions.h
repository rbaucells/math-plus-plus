#ifndef MATHPP_IMPLEMENTATION_MATRIX_COMMON_EXCEPTIONS
#define MATHPP_IMPLEMENTATION_MATRIX_COMMON_EXCEPTIONS

#include <stdexcept>

/**
 * @brief Thrown when an invalid pivot is found (e.g. 0, or imaginary)
 */
class InvalidPivotException final : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

#endif // MATHPP_IMPLEMENTATION_MATRIX_COMMON_EXCEPTIONS
