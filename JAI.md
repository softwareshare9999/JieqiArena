## JAI Protocol

### GUI (JieqiBox) -> Match Engine (JAI Engine)

`jai`
- Handshake command.

`setoption name <OptionName> value <OptionValue>`
- Set parameters.

`isready`
- Query ready status.

`startmatch`
- Start match.

`stop`
- Stop.

`quit`
- Exit.

---

### Match Engine (JAI Engine) -> GUI (JieqiBox)

`id name <EngineName>`
`id author <AuthorName>`
- Engine self information.

`jaiok`
- Confirmation of `jai` command.
- After receiving `jai`, the engine must first return `id`, then immediately list all supported `option`s, and finally output `jaiok`.

`option name <Name> type <Type> [default <Value>] [min <Value>] [max <Value>] [var <Value>] ...`
- **Description:** Declare a supported parameter, GUI will generate settings interface accordingly.
- **`type` types:**
  - `string`: String, usually used for paths or filenames.
    - Example: `option name BookFile type string default C:\book.dat`
  - `spin`: Integer.
    - Example: `option name Threads type spin default 4 min 1 max 128`
  - `check`: Boolean value (`true`/`false`).
    - Example: `option name UseGUIBook type check default true`
  - `button`: Button. When user clicks, GUI will send `setoption name <Name>` to the engine, used to trigger an action.
    - Example: `option name ClearHash type button`
  - `combo`: Dropdown list. Can be followed by multiple `var` to define options.
    - Example: `option name SearchMode type combo default time var time var movetime var nodes`

`readyok`
- Confirmation of `isready` command.

`info string <Message>`
- JAI engine's own status information.
- After each finished game (and at match start/end), this is a named scoreboard:
  `<Engine1Name> <Wins>-<Losses>-<Draws> <Engine2Name> (<Score1>-<Score2>)`
- Example: `info string pikafishbmi2.exe 3-0-1 pikafishmodern.exe (3.5-0.5)`
- Wins/Losses/Draws and Score1 are always for Engine1 (the engine set via `Engine1Path`).

`info game <CurrentGame>/<TotalGames>`
- Current game progress.

`info wld <Wins>-<Losses>-<Draws>`
- Total wins, losses, and draws for **Engine1** in the current match.
- Engine2's record is the reverse: `<Losses>-<Wins>-<Draws>`.
- Example: `info wld 3-0-1` means Engine1 has 3 wins, 0 losses, and 1 draw.

`info fen <FENString>`
- Current game FEN, only sent once at the start of the game, GUI will clear the current move record.

`info move <MoveString> time <TimeMs>`
- Engine move with time taken in milliseconds.

`info result <ResultString>`
- Single game result. The standard token (`1-0`, `0-1`, `1/2-1/2`) may be followed by the winner:
  `1-0 (<RedEngine> won)`, `0-1 (<BlackEngine> won)`, or `1/2-1/2 (draw)`.

`info engine <RedEngine> <BlackEngine>`
- Indicates the red and black engines currently competing.

`info depth ...`
- Analysis information from UCI engine output, passed through to JieqiBox as-is.

### Interaction Flow Example
1. GUI -> `jai`
2. Engine -> `id name Jieqi Match Tools`
3. Engine -> `id author xxx`
4. Engine -> `option name Engine1Path type string` ...
5. Engine -> `option name TotalRounds type spin default 100`
6. Engine -> `jaiok`
7. ... (list all options)
8. GUI -> `setoption name Engine1Path value ...` ...
9. GUI -> `isready`
10. Engine -> `readyok`
11. GUI -> `startmatch`
12. Engine -> `info game 0/200`
13. Engine -> `info engine engine1.exe engine2.exe`
14. Engine -> `info wld 0-0-0`
15. Engine -> `info string engine1.exe 0-0-0 engine2.exe (0.0-0.0)`
16. ...
17. Engine -> `info depth 10 score cp 50 ...` (This is passed through from the jieqi engine)
18. ...
19. Engine -> `info result 1-0 (engine1.exe won)`
20. Engine -> `info wld 1-0-0`
21. Engine -> `info string engine1.exe 1-0-0 engine2.exe (1.0-0.0)`