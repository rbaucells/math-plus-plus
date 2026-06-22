#pragma once
#include <cstdint>

enum class DotProductConjugationBehavior : std::uint8_t {
    first_argument,
    second_argument,
    neither
};

constexpr DotProductConjugationBehavior DEFAULT_CONJUGATION_BEHAVIOR = DotProductConjugationBehavior::second_argument;
