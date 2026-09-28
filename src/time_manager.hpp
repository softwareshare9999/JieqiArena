#pragma once

#include <string>

#include "types.hpp"

// --- Time / search control ---

// Default timeout buffer in milliseconds to prevent premature timeouts
constexpr int DEFAULT_TIMEOUT_BUFFER_MS = 5000;  // 5 seconds buffer

enum class SearchMode {
    Time,      // go wtime/btime/winc/binc (default)
    Movetime,  // go movetime MainTimeMs
    Nodes      // go nodes NodesPerMove — fair algorithm A/B, ignores clock
};

struct TimeControl {
    int wtime_ms = 0;
    int btime_ms = 0;
    int winc_ms = 0;
    int binc_ms = 0;
};

class TimeManager {
   private:
    TimeControl tc;
    int timeout_buffer_ms;
    SearchMode search_mode;
    int nodes_per_move;

   public:
    TimeManager(const TimeControl &initial_tc, int timeout_buffer_ms = DEFAULT_TIMEOUT_BUFFER_MS,
                SearchMode search_mode = SearchMode::Time, int nodes_per_move = 0);

    void update(Color player_who_moved, long long elapsed_ms);
    bool is_out_of_time(Color player, long long elapsed_ms = 0) const;
    int get_time_ms(Color player) const;
    std::string get_go_command() const;
    SearchMode mode() const { return search_mode; }
    bool uses_clock() const { return search_mode == SearchMode::Time; }

    // Setter for timeout buffer
    void set_timeout_buffer(int buffer_ms);
};
