#pragma once
#include <stdexcept>

class InvalidDimensionException : public std::invalid_argument
{
    using std::invalid_argument::invalid_argument;
};
