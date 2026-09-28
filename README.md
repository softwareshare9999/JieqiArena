# JieqiArena

JieqiArena is a demo of JAI (Jieqi Arena Interface) that supports basic engine competition functionalities and can be loaded and used by [JieqiBox](https://github.com/Velithia/JieqiBox).

## JAI Options

### Engine Configuration

*   **Engine1Path**
    *   Description: The full path to the first UCI-compatible Jieqi engine executable.
    *   Type: `string`
    *   Default: (none)

*   **Engine1Options**
    *   Description: A string of UCI `setoption` commands for Engine 1. Each option must follow the format `name <Option Name> value <Value>`. Multiple options are separated by spaces. This parser correctly handles option names and values that contain spaces.
    *   Type: `string`
    *   Default: (empty)
    *   Example: `name Threads value 4 name Hash value 256`

*   **Engine2Path**
    *   Description: The full path to the second UCI-compatible Jieqi engine executable.
    *   Type: `string`
    *   Default: (none)

*   **Engine2Options**
    *   Description: A string of UCI `setoption` commands for Engine 2. See `Engine1Options` for format and examples.
    *   Type: `string`
    *   Default: (empty)

### Tournament Settings

*   **TotalRounds**
    *   Description: The number of pairs of games to be played. The total number of games will be `TotalRounds * 2`, as engines switch colors for each round.
    *   Type: `spin`
    *   Default: `10`
    *   Min: `1`
    *   Max: `1000`

*   **Concurrency**
    *   Description: The number of games to run in parallel.
    *   Type: `spin`
    *   Default: `2`
    *   Min: `1`
    *   Max: `128`

### Game Settings

*   **BookFile**
    *   Description: Path to an opening book file. The file should contain one FEN position per line. At the start of each round, a FEN is chosen randomly from this file to be used for that round's pair of games. If the path is empty, invalid, or the file contains no FENs, the default starting position is used.
    *   Type: `string`
    *   Default: (empty)

### Time Control

*   **SearchMode**
    *   Description: How each engine is told to search. `time` uses a game clock (`go wtime/btime/winc/binc`). `movetime` sends `go movetime MainTimeMs` every move. `nodes` sends `go nodes NodesPerMove` and never flags on time — use this for algorithm A/B so a clock-overrun bug cannot buy extra search.
    *   Type: `combo`
    *   Default: `time`
    *   Values: `time`, `movetime`, `nodes`

*   **MainTimeMs**
    *   Description: In `time` mode, the base clock in milliseconds. In `movetime` mode, the per-move limit. Ignored in `nodes` mode.
    *   Type: `spin`
    *   Default: `1000`
    *   Min: `0`
    *   Max: `3600000`

*   **IncTimeMs**
    *   Description: Time increment after each move, in milliseconds. Only used in `time` mode.
    *   Type: `spin`
    *   Default: `0`
    *   Min: `0`
    *   Max: `60000`

*   **NodesPerMove**
    *   Description: Nodes each engine may search per move when `SearchMode` is `nodes`. Same node budget for both engines; NPS differences then only change wall-clock time, not search depth.
    *   Type: `spin`
    *   Default: `100000`
    *   Min: `1`
    *   Max: `100000000`

*   **TimeoutBufferMs**
    *   Description: A grace period in milliseconds to account for process and communication overhead. In `time` mode, a player is only declared lost on time if their clock falls below `-(TimeoutBufferMs)`. In `movetime` mode, a move is flagged if wall time exceeds `MainTimeMs + TimeoutBufferMs`. Unused in `nodes` mode.
    *   Type: `spin`
    *   Default: `5000`
    *   Min: `0`
    *   Max: `60000`

### Debugging

*   **Logging**
    *   Description: If enabled (`true`), the match engine will create detailed log files for each engine process, capturing all UCI communication. The files are named `engine_debug_<Color>_job<ID>.log`.
    *   Type: `check`
    *   Default: `false`