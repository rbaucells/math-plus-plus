#pragma once

#include <cstddef>

struct TelemetryStats {
    std::size_t copy_constructs = 0;
    std::size_t move_constructs = 0;
    std::size_t copy_assigns = 0;
    std::size_t move_assigns = 0;
    std::size_t allocations = 0;
    std::size_t deallocations = 0;
};

struct Telemetry {
    constexpr static void emit_copy_construct() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            ++stats_.copy_constructs;
        }
#endif
    }

    constexpr static void emit_move_construct() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            ++stats_.move_constructs;
        }
#endif
    }

    constexpr static void emit_copy_assign() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            ++stats_.copy_assigns;
        }
#endif
    }

    constexpr static void emit_move_assign() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            ++stats_.move_assigns;
        }
#endif
    }

    constexpr static void emit_allocation() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            ++stats_.allocations;
        }
#endif
    }

    constexpr static void emit_deallocation() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            ++stats_.deallocations;
        }
#endif
    }

    constexpr static void reset() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            stats_ = TelemetryStats();
        }
#endif
    }

    [[nodiscard]] constexpr static TelemetryStats snapshot() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        if !consteval {
            return stats_;
        }
        else {
            return TelemetryStats();
        }
#else
        return TelemetryStats();
#endif
    }

private:
#ifdef MATHPP_ENABLE_TELEMETRY
    static inline thread_local TelemetryStats stats_{};
#endif
};
