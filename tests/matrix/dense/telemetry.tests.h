#pragma once

#include <utility>

#include "gtest/gtest.h"

#include "mathpp/math.h"

[[nodiscard]] inline DenseMatrixStats dense_matrix_telemetry_snapshot() {
    return DenseMatrixTelemetry::snapshot();
}

inline void reset_dense_matrix_telemetry() {
    DenseMatrixTelemetry::reset();
}

inline void assert_telemetry_stats(const DenseMatrixStats& actual, const DenseMatrixStats& expected) {
    ASSERT_EQ(actual.copy_constructs, expected.copy_constructs) << "copy_constructs mismatch";
    ASSERT_EQ(actual.move_constructs, expected.move_constructs) << "move_constructs mismatch";
    ASSERT_EQ(actual.copy_assigns, expected.copy_assigns) << "copy_assigns mismatch";
    ASSERT_EQ(actual.move_assigns, expected.move_assigns) << "move_assigns mismatch";
    ASSERT_EQ(actual.allocations, expected.allocations) << "allocations mismatch";
    ASSERT_EQ(actual.deallocations, expected.deallocations) << "deallocations mismatch";
}

class DenseMatrixTelemetryScope {
public:

    DenseMatrixTelemetryScope() : baseline_(DenseMatrixTelemetry::snapshot()) {
    }

    [[nodiscard]] DenseMatrixStats delta() const {
        const DenseMatrixStats current = DenseMatrixTelemetry::snapshot();
        DenseMatrixStats d;
        d.copy_constructs = current.copy_constructs - baseline_.copy_constructs;
        d.move_constructs = current.move_constructs - baseline_.move_constructs;
        d.copy_assigns = current.copy_assigns - baseline_.copy_assigns;
        d.move_assigns = current.move_assigns - baseline_.move_assigns;
        d.allocations = current.allocations - baseline_.allocations;
        d.deallocations = current.deallocations - baseline_.deallocations;
        return d;
    }

    void assert_stats_delta(const DenseMatrixStats& expected) const {
        assert_telemetry_stats(delta(), expected);
    }

private:
    DenseMatrixStats baseline_;
};

inline void reset_dense_matrix_copy_telemetry() {
    DenseMatrixTelemetry::reset();
}

[[nodiscard]] inline std::size_t dense_matrix_copy_telemetry_count() {
    return DenseMatrixTelemetry::snapshot().copy_constructs;
}

inline void assert_dense_matrix_copy_telemetry(const std::size_t expected_number_of_copies) {
    ASSERT_EQ(dense_matrix_copy_telemetry_count(), expected_number_of_copies);
}

class DenseMatrixTelemetryFixture : public ::testing::Test {
protected:

    void SetUp() override {
        reset_dense_matrix_telemetry();
    }

    template<typename RESULT, typename ACTION>
    RESULT run_with_budget(const DenseMatrixStats& expected, ACTION&& action) {
        const DenseMatrixTelemetryScope scope;
        RESULT result(std::forward<ACTION>(action)());
        scope.assert_stats_delta(expected);
        return result;
    }
};

template<typename RESULT, typename ACTION>
RESULT run_with_budget(const DenseMatrixStats& expected, ACTION&& action) {
    const DenseMatrixTelemetryScope scope;
    RESULT result(std::forward<ACTION>(action)());
    scope.assert_stats_delta(expected);
    return result;
}
