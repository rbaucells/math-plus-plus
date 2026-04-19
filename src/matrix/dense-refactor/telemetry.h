#pragma once

#include <cstddef>

struct DenseMatrixStats {
    std::size_t copy_constructs = 0;
    std::size_t move_constructs = 0;
    std::size_t copy_assigns = 0;
    std::size_t move_assigns = 0;
    std::size_t allocations = 0;
    std::size_t deallocations = 0;
};

struct DenseMatrixTelemetry {
    static void emit_copy_construct() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        ++stats_.copy_constructs;
#endif
    }

    static void emit_move_construct() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        ++stats_.move_constructs;
#endif
    }

    static void emit_copy_assign() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        ++stats_.copy_assigns;
#endif
    }

    static void emit_move_assign() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        ++stats_.move_assigns;
#endif
    }

    static void emit_allocation() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        ++stats_.allocations;
#endif
    }

    static void emit_deallocation() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        ++stats_.deallocations;
#endif
    }

    static void reset() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        stats_ = DenseMatrixStats{};
#endif
    }

    [[nodiscard]] static DenseMatrixStats snapshot() noexcept {
#ifdef MATHPP_ENABLE_TELEMETRY
        return stats_;
#else
        return DenseMatrixStats{};
#endif
    }

private:
#ifdef MATHPP_ENABLE_TELEMETRY
    static inline thread_local DenseMatrixStats stats_{};
#endif
};
