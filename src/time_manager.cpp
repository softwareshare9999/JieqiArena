#include "time_manager.hpp"

#include <format>

TimeManager::TimeManager(const TimeControl &initial_tc, int timeout_buffer_ms,
                         SearchMode search_mode, int nodes_per_move)
    : tc(initial_tc),
      timeout_buffer_ms(timeout_buffer_ms),
      search_mode(search_mode),
      nodes_per_move(nodes_per_move) {}

void TimeManager::update(Color player_who_moved, long long elapsed_ms) {
    if (search_mode != SearchMode::Time) {
        return;
    }
    if (player_who_moved == Color::RED) {
        tc.wtime_ms -= elapsed_ms;
        tc.wtime_ms += tc.winc_ms;
    } else {
        tc.btime_ms -= elapsed_ms;
        tc.btime_ms += tc.binc_ms;
    }
}

bool TimeManager::is_out_of_time(Color player, long long elapsed_ms) const {
    switch (search_mode) {
        case SearchMode::Nodes:
            return false;
        case SearchMode::Movetime:
            // MainTimeMs is stored on both clocks; flag if this move overran it plus buffer.
            return elapsed_ms > static_cast<long long>(tc.wtime_ms) + timeout_buffer_ms;
        case SearchMode::Time:
        default:
            if (player == Color::RED) {
                return tc.wtime_ms <= -timeout_buffer_ms;
            }
            return tc.btime_ms <= -timeout_buffer_ms;
    }
}

int TimeManager::get_time_ms(Color player) const {
    return player == Color::RED ? tc.wtime_ms : tc.btime_ms;
}

std::string TimeManager::get_go_command() const {
    switch (search_mode) {
        case SearchMode::Nodes:
            return std::format("go nodes {}", nodes_per_move > 0 ? nodes_per_move : 1);
        case SearchMode::Movetime:
            return std::format("go movetime {}", tc.wtime_ms);
        case SearchMode::Time:
        default:
            return std::format("go wtime {} btime {} winc {} binc {}", tc.wtime_ms, tc.btime_ms,
                               tc.winc_ms, tc.binc_ms);
    }
}

void TimeManager::set_timeout_buffer(int buffer_ms) {
    timeout_buffer_ms = buffer_ms;
}
