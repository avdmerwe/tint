# TINT - TINT Is Not Tetris®

A terminal-based clone of the original Tetris® game, written in C using ncurses.

## Overview

TINT is a faithful recreation of the classic falling-blocks puzzle game, designed to run in a terminal environment. It maintains the gameplay mechanics of the original while providing a clean, text-based interface.

## Features

- Classic Tetris gameplay
- Terminal-based interface using ncurses
- 9 difficulty levels
- High score tracking (stored in user's home directory)
- Next piece preview (optional)
- Clean, minimalist design

## Installation

### From Source

```bash
make
sudo make install
```

### Debian/Ubuntu

```bash
make debian
sudo dpkg -i ../tint_*.deb
```

## Usage

Start the game:
```bash
tint
```

Start at a specific level (1-9):
```bash
tint -l 5
```

### Controls

- `h` or `←` - Move piece left
- `l` or `→` - Move piece right  
- `j` or `↓` - Rotate piece
- `k` or `↑` - Drop piece faster
- `Space` - Drop piece immediately
- `p` - Pause game
- `n` - Toggle next piece preview
- `a` - Increase level (if not at maximum)
- `q` - Quit game

## Development

### Building with Debug Symbols

```bash
make CFLAGS="-g -Wall" LDFLAGS="" STRIP=":"
```

### Memory Leak Testing

```bash
make leaks
```

This runs valgrind to check for memory leaks using both quick and extended test scenarios.

## Technical Notes

### Score Calculation

The scoring system works as follows:

1. Count the number of lines a piece drops when pressing SPACE
2. Add 1 when the block comes to rest
3. Multiply by the current level
4. If "Show Next" is enabled, divide by 2
5. Add the result to the score

Note: Internally, scores are doubled to prevent precision loss, and the displayed score is divided by 2.

### Timing

- 9 levels numbered 1-9
- Block drop speed: 1/level seconds
- Level increases automatically every 10 lines cleared
- Starting at a higher level requires proportionally more lines to advance

### Implementation Details

For implementation notes regarding rotation algorithms and data structures, see the source code comments.

## License

This project is distributed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Credits

See [CREDITS.md](CREDITS.md) for acknowledgments and attribution.

