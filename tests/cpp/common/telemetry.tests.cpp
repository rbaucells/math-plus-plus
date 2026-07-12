#include <thread>

#include "gtest/gtest.h"

#include "mathpp/implementation/common/telemetry.h"
#include "mathpp/implementation/common/compare.h"

TEST(emit_copy_construct, should_increment_copy_construct) {
    // arrange
    const TelemetryStats start = Telemetry::snapshot();
    // act
    Telemetry::emit_copy_construct();
    // assert
    const TelemetryStats after = Telemetry::snapshot();
    ASSERT_TRUE(compare(after.copy_constructs, start.copy_constructs + 1));
}

TEST(emit_move_construct, should_increment_move_construct) {
    // arrange
    const TelemetryStats start = Telemetry::snapshot();
    // act
    Telemetry::emit_move_construct();
    // assert
    const TelemetryStats after = Telemetry::snapshot();
    ASSERT_TRUE(compare(after.move_constructs, start.move_constructs + 1));
}

TEST(emit_copy_assign, should_increment_copy_assign) {
    // arrange
    const TelemetryStats start = Telemetry::snapshot();
    // act
    Telemetry::emit_copy_assign();
    // assert
    const TelemetryStats after = Telemetry::snapshot();
    ASSERT_TRUE(compare(after.copy_assigns, start.copy_assigns + 1));
}

TEST(emit_move_assign, should_increment_move_assign) {
    // arrange
    const TelemetryStats start = Telemetry::snapshot();
    // act
    Telemetry::emit_move_assign();
    // assert
    const TelemetryStats after = Telemetry::snapshot();
    ASSERT_TRUE(compare(after.move_assigns, start.move_assigns + 1));
}

TEST(emit_allocation, should_increment_allocation) {
    // arrange
    const TelemetryStats start = Telemetry::snapshot();
    // act
    Telemetry::emit_allocation();
    // assert
    const TelemetryStats after = Telemetry::snapshot();
    ASSERT_TRUE(compare(after.allocations, start.allocations + 1));
}

TEST(emit_deallocation, should_increment_deallocation) {
    // arrange
    const TelemetryStats start = Telemetry::snapshot();
    // act
    Telemetry::emit_deallocation();
    // assert
    const TelemetryStats after = Telemetry::snapshot();
    ASSERT_TRUE(compare(after.deallocations, start.deallocations + 1));
}

TEST(reset, should_reset_all_values) {
    // arrange
    Telemetry::emit_copy_construct();
    Telemetry::emit_move_construct();
    Telemetry::emit_copy_assign();
    Telemetry::emit_move_assign();
    Telemetry::emit_allocation();
    Telemetry::emit_deallocation();
    // act
    Telemetry::reset();
    // assert
    const TelemetryStats after = Telemetry::snapshot();
    ASSERT_TRUE(compare(after.copy_constructs, 0));
    ASSERT_TRUE(compare(after.move_constructs, 0));
    ASSERT_TRUE(compare(after.copy_assigns, 0));
    ASSERT_TRUE(compare(after.move_assigns, 0));
    ASSERT_TRUE(compare(after.allocations, 0));
    ASSERT_TRUE(compare(after.deallocations, 0));
}

TEST(telemetry, when_accessed_from_diff_threads_should_have_different_telemetry_values) {
    // arrange
    TelemetryStats thread1Stats = {};
    TelemetryStats thread2Stats = {};
    // act
    std::thread thread1 = std::thread([](TelemetryStats& stats) {
        Telemetry::reset();
        // 1 copy_construct
        Telemetry::emit_copy_construct();
        // 2 move_construct
        Telemetry::emit_move_construct();
        Telemetry::emit_move_construct();
        // 3 copy_assign
        Telemetry::emit_copy_assign();
        Telemetry::emit_copy_assign();
        Telemetry::emit_copy_assign();
        // 4 move_assign
        Telemetry::emit_move_assign();
        Telemetry::emit_move_assign();
        Telemetry::emit_move_assign();
        Telemetry::emit_move_assign();
        // 5 allocation
        Telemetry::emit_allocation();
        Telemetry::emit_allocation();
        Telemetry::emit_allocation();
        Telemetry::emit_allocation();
        Telemetry::emit_allocation();
        // 6 deallocation
        Telemetry::emit_deallocation();
        Telemetry::emit_deallocation();
        Telemetry::emit_deallocation();
        Telemetry::emit_deallocation();
        Telemetry::emit_deallocation();
        Telemetry::emit_deallocation();

        stats = Telemetry::snapshot();
    }, std::ref(thread1Stats));

    std::thread thread2 = std::thread([](TelemetryStats& stats) {
        Telemetry::reset();
        // 6 copy_construct
        Telemetry::emit_copy_construct();
        Telemetry::emit_copy_construct();
        Telemetry::emit_copy_construct();
        Telemetry::emit_copy_construct();
        Telemetry::emit_copy_construct();
        Telemetry::emit_copy_construct();
        // 5 move_construct
        Telemetry::emit_move_construct();
        Telemetry::emit_move_construct();
        Telemetry::emit_move_construct();
        Telemetry::emit_move_construct();
        Telemetry::emit_move_construct();
        // 4 copy_assign
        Telemetry::emit_copy_assign();
        Telemetry::emit_copy_assign();
        Telemetry::emit_copy_assign();
        Telemetry::emit_copy_assign();
        // 3 move_assign
        Telemetry::emit_move_assign();
        Telemetry::emit_move_assign();
        Telemetry::emit_move_assign();
        // 2 allocation
        Telemetry::emit_allocation();
        Telemetry::emit_allocation();
        // 1 deallocation
        Telemetry::emit_deallocation();

        stats = Telemetry::snapshot();
    }, std::ref(thread2Stats));

    thread1.join();
    thread2.join();
    // assert
    ASSERT_TRUE(compare(thread1Stats.copy_constructs, 1));
    ASSERT_TRUE(compare(thread1Stats.move_constructs, 2));
    ASSERT_TRUE(compare(thread1Stats.copy_assigns, 3));
    ASSERT_TRUE(compare(thread1Stats.move_assigns, 4));
    ASSERT_TRUE(compare(thread1Stats.allocations, 5));
    ASSERT_TRUE(compare(thread1Stats.deallocations, 6));

    ASSERT_TRUE(compare(thread2Stats.copy_constructs, 6));
    ASSERT_TRUE(compare(thread2Stats.move_constructs, 5));
    ASSERT_TRUE(compare(thread2Stats.copy_assigns, 4));
    ASSERT_TRUE(compare(thread2Stats.move_assigns, 3));
    ASSERT_TRUE(compare(thread2Stats.allocations, 2));
    ASSERT_TRUE(compare(thread2Stats.deallocations, 1));

}

// snapshot already tested in other telemetry tests.
