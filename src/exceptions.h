#pragma once
#include <stdexcept>

/**
 * @brief Thrown when arguments (matrices/vectors) don't have the expected size/shape.
 */
class InvalidDimensionException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

/**
 * @brief Thrown when an operation is attempted on something that can't be allowed (e.g. modifying owner on view)
 */
class InvalidOperationException : public std::logic_error {
    using std::logic_error::logic_error;
};

/**
 * Thrown when an index is invalid.
 */
class InvalidIndexException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};
