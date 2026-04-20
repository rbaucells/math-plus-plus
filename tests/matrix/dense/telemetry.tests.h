#pragma once

#include <utility>

#include "gtest/gtest.h"

#include "mathpp/math.h"

[[nodiscard]] inline TelemetryStats telemetry_snapshot() {
    return Telemetry::snapshot();
}

inline void reset_telemetry() {
    Telemetry::reset();
}

inline void assert_telemetry_stats(const TelemetryStats& actual, const TelemetryStats& expected) {
    ASSERT_EQ(actual.copy_constructs, expected.copy_constructs) << "copy_constructs mismatch";
    ASSERT_EQ(actual.move_constructs, expected.move_constructs) << "move_constructs mismatch";
    ASSERT_EQ(actual.copy_assigns, expected.copy_assigns) << "copy_assigns mismatch";
    ASSERT_EQ(actual.move_assigns, expected.move_assigns) << "move_assigns mismatch";
    ASSERT_EQ(actual.allocations, expected.allocations) << "allocations mismatch";
    ASSERT_EQ(actual.deallocations, expected.deallocations) << "deallocations mismatch";
}

class TelemetryScope {
public:
    TelemetryScope() : baseline_(Telemetry::snapshot()) {
    }

    [[nodiscard]] TelemetryStats delta() const {
        const TelemetryStats current = Telemetry::snapshot();
        TelemetryStats d;
        d.copy_constructs = current.copy_constructs - baseline_.copy_constructs;
        d.move_constructs = current.move_constructs - baseline_.move_constructs;
        d.copy_assigns = current.copy_assigns - baseline_.copy_assigns;
        d.move_assigns = current.move_assigns - baseline_.move_assigns;
        d.allocations = current.allocations - baseline_.allocations;
        d.deallocations = current.deallocations - baseline_.deallocations;
        return d;
    }

    void assert_stats_delta(const TelemetryStats& expected) const {
        assert_telemetry_stats(delta(), expected);
    }

private:
    TelemetryStats baseline_;
};

inline void reset_copy_telemetry() {
    Telemetry::reset();
}

[[nodiscard]] inline std::size_t copy_telemetry_count() {
    return Telemetry::snapshot().copy_constructs;
}

inline void assert_copy_telemetry(const std::size_t expected_number_of_copies) {
    ASSERT_EQ(copy_telemetry_count(), expected_number_of_copies);
}

class TelemetryFixture : public ::testing::Test {
protected:
    void SetUp() override {
        reset_telemetry();
    }

    template<typename RESULT, typename ACTION>
    RESULT run_with_budget(const TelemetryStats& expected, ACTION&& action) {
        const TelemetryScope scope;
        RESULT result(std::forward<ACTION>(action)());
        scope.assert_stats_delta(expected);
        return result;
    }
};

template<typename RESULT, typename ACTION>
RESULT run_with_budget(const TelemetryStats& expected, ACTION&& action) {
    const TelemetryScope scope;
    RESULT result(std::forward<ACTION>(action)());
    scope.assert_stats_delta(expected);
    return result;
}

#define START_TELEMETRY() \
    const auto startTelemetryStats = Telemetry::snapshot();

#define END_TELEMETRY() \
    const auto endTelemetryStats = Telemetry::snapshot();

#define ASSERT_TELEMETRY(expectedTelemetryStats) \
    ASSERT_EQ(endTelemetryStats.copy_constructs, startTelemetryStats.copy_constructs + expectedTelemetryStats.copy_constructs); \
    ASSERT_EQ(endTelemetryStats.move_constructs, startTelemetryStats.move_constructs + expectedTelemetryStats.move_constructs); \
    ASSERT_EQ(endTelemetryStats.copy_assigns, startTelemetryStats.copy_assigns + expectedTelemetryStats.copy_assigns); \
    ASSERT_EQ(endTelemetryStats.move_assigns, startTelemetryStats.move_assigns + expectedTelemetryStats.move_assigns); \
    ASSERT_EQ(endTelemetryStats.allocations, startTelemetryStats.allocations + expectedTelemetryStats.allocations); \
    ASSERT_EQ(endTelemetryStats.deallocations, startTelemetryStats.deallocations + expectedTelemetryStats.deallocations); \
