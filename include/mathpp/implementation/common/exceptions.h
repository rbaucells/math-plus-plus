#ifndef MATHPP_IMPLEMENTATION_COMMON_EXCEPTIONS
#define MATHPP_IMPLEMENTATION_COMMON_EXCEPTIONS

#include <stdexcept>

/**
 * @brief Thrown when arguments (matrices/vectors) don't have the expected size/shape.
 */
struct InvalidDimensionException final : std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

/**
 * @brief Thrown when an operation is attempted on something that can't be allowed (e.g. modifying owner on view)
 */
struct InvalidOperationException final : std::logic_error {
    using std::logic_error::logic_error;
};

/**
 * Thrown when an index is invalid.
 */
struct InvalidIndexException final : std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

#endif // MATHPP_IMPLEMENTATION_COMMON_EXCEPTIONS
