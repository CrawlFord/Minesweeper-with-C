# Minesweeper Complete Edition

A terminal-based Minesweeper game written in C. This project implements the core gameplay of Minesweeper, including random mine placement, difficulty selection, cell opening, flagging, scoring, win/loss detection, and file-based player records.

The project was developed as a C programming project and has been cleaned for use as part of a games programming portfolio.

## Project Overview

Minesweeper is a grid-based puzzle game where the player must avoid hidden mines. The player reveals cells on the board and uses the numbers shown to identify where mines may be located.

This version runs in the terminal and uses text-based input to control the game.

## Features

* Terminal-based Minesweeper gameplay
* Difficulty selection
* Random mine placement
* Cell opening and mine flagging
* Grid-based board display
* Win and loss condition handling
* Score tracking
* Login and sign-up system
* File handling for player records
* Menu-driven user interface

## How to Run

### Requirements

* A C compiler, such as GCC
* A terminal or command prompt

### Compile

```bash
gcc src/minesweeper.c -o minesweeper
```

### Run

On macOS/Linux:

```bash
./minesweeper
```

On Windows:

```bash
minesweeper.exe
```

## How to Play

The player selects a difficulty level and plays on a square grid. Each turn, the player enters a row, a column, and an action.

The input format is:

```text
row column action
```

For example:

```text
1 3 1
```

This means the player selected row `1`, column `3`, and chose action `1`.

Actions:

```text
1 = Open a cell
2 = Flag a suspected mine
```

The player wins by correctly identifying the mine positions and loses if they open a cell containing a mine.

Full gameplay rules are available in [`docs/rules.md`](docs/rules.md).

## Project Structure

```text
minesweeper-complete-edition/
├── README.md
├── LICENSE
├── .gitignore
├── docs/
│   ├── rules.md
│   └── screenshots/
└── src/
    └── minesweeper.c
```

## C Concepts Demonstrated

This project demonstrates several important C programming concepts:

* 2D arrays for grid-based board representation
* Loops for board display, gameplay flow, and mine checking
* Conditional statements for game decisions
* Functions for separating gameplay logic
* Random number generation for mine placement
* File handling for saving player details and scores
* String handling for login and sign-up functionality
* Input validation and menu-based interaction
* Game state management
* Boundary checking when working with grid coordinates

## What I Learned

This project helped me understand how to design and implement a complete terminal-based game in C. I practised breaking gameplay into smaller systems, managing game state, handling player input, saving data to files, and using arrays to represent a game board.

It also helped me build confidence with debugging and structuring a larger C program.

## Future Improvements

Possible future improvements include:

* Refactoring the code into smaller source files
* Improving input validation
* Adding automated tests for board logic
* Improving the scoring system
* Adding a timer
* Creating a graphical version using a game engine or graphics library
* Replacing plain text user storage with a safer approach

## Screenshots

Screenshots will be added in the `docs/screenshots/` folder.

Example:

```markdown
![Minesweeper gameplay screenshot](docs/screenshots/gameplay-demo.png)
```

## License

This project is licensed under the MIT License.
