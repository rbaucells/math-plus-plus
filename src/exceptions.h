#pragma once
#include <stdexcept>

/**
 * @brief Thrown when arguments (matrices/vectors) don't have the expected size/shape.
 */
class InvalidDimensionException : public std::invalid_argument
{
    using std::invalid_argument::invalid_argument;
};
