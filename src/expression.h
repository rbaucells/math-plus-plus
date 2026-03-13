#pragma once
#include <tuple>

/**
 * Base class for all math expressions.
 * To be used for operators ONLY.
 * Common uses are + and - operators, where you do all additions and subtractions in one loop instead of multiple.
 * @tparam RESULT What the expression will get turned into implicitly.
 * @tparam ARGS The types of all the parameters.
 */
template<typename RESULT, typename... ARGS>
struct Expression {
    const std::tuple<const ARGS&...> args;

    Expression(const ARGS&... args) : args(args...) {}

    operator RESULT() const {
        return this->evaluate();
    }

    virtual RESULT evaluate() const = 0;

    virtual ~Expression() = default;
};