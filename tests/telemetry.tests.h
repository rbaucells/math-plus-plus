#pragma once

#include "gtest/gtest.h"

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
