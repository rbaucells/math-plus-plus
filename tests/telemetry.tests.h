#pragma once

#include "gtest/gtest.h"
#include "mathpp/implementation/common/telemetry.h"

struct TelemetryTests {
    static void start() {
        startTelemetryStats = Telemetry::snapshot();
    }

    static void end() {
        endTelemetryStats = Telemetry::snapshot();
    }

    static void asserts(const TelemetryStats& expected) {
        ASSERT_EQ(endTelemetryStats.copy_constructs, startTelemetryStats.copy_constructs + expected.copy_constructs);
        ASSERT_EQ(endTelemetryStats.move_constructs, startTelemetryStats.move_constructs + expected.move_constructs);
        ASSERT_EQ(endTelemetryStats.copy_assigns, startTelemetryStats.copy_assigns + expected.copy_assigns);
        ASSERT_EQ(endTelemetryStats.move_assigns, startTelemetryStats.move_assigns + expected.move_assigns);
        ASSERT_EQ(endTelemetryStats.allocations, startTelemetryStats.allocations + expected.allocations);
        ASSERT_EQ(endTelemetryStats.deallocations, startTelemetryStats.deallocations + expected.deallocations);
        ASSERT_EQ(endTelemetryStats.dimensions_checks, startTelemetryStats.dimensions_checks + expected.dimensions_checks);
    }
private:
    static inline TelemetryStats startTelemetryStats = {};
    static inline TelemetryStats endTelemetryStats = {};
};
