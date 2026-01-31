#pragma once
#include <tuple>

/**
 * Base class for all math Expressions.
 * To be used for operators ONLY.
 * Common uses are + and - operators,
 * where you do all additions and subtractions in one loop instead of multiple
 * @tparam RESULT What the Expression will get turned into implicitly
 * @tparam OTHERS The types of all the other parameters
 */
template<typename RESULT, typename... OTHERS>
struct Expression {
    // All the parameters being passed to the main function
    const std::tuple<const OTHERS&...> others;

    Expression(const OTHERS&... args) : others(args...) {}

    operator RESULT() const {
        return this->evaluate();
    }

    virtual RESULT evaluate() const = 0;

    virtual ~Expression() = default;
};