#ifndef MATHPP_IMPLEMENTATION_COMMON_DOT_BEHAVIOR_H
#define MATHPP_IMPLEMENTATION_COMMON_DOT_BEHAVIOR_H

#include <cstdint>

enum class DotProductConjugationBehavior : std::uint8_t {
    first_argument,
    second_argument,
    neither
};

constexpr DotProductConjugationBehavior DEFAULT_CONJUGATION_BEHAVIOR = DotProductConjugationBehavior::second_argument;

#endif // MATHPP_IMPLEMENTATION_COMMON_DOT_BEHAVIOR_H
