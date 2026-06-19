# Minesweeper Rules

## Objective

The objective of Minesweeper is to reveal safe cells on the grid while avoiding hidden mines.

The player loses if they open a cell that contains a mine.

## Game Board

The game is played on a square grid. The size of the grid depends on the difficulty level selected by the player.

Rows and columns are numbered so that the player can choose a cell using coordinates.

## Player Input

Each move uses three numbers:

```text
row column action
```
There is space between each number.

The first number is the row.

The second number is the column.

The third number is the action.

## Actions

```text
1 = Open a cell
2 = Flag a suspected mine
```

For example:

```text
1 3 1
```

This means:

```text
Row: 1
Column: 3
Action: Open the cell
```

Another example:

```text
2 4 2
```

This means:

```text
Row: 2
Column: 4
Action: Flag the cell as a suspected mine
```

## Numbers on the Board

When a safe cell is opened, the number shown helps the player understand how many mines are nearby.

The number represents the mines surrounding that cell, including cells above, below, left, right, and diagonally nearby.

## Winning the Game

The player wins by correctly identifying the mine positions and avoiding opening mined cells.

## Losing the Game

The player loses if they open a cell that contains a mine.
