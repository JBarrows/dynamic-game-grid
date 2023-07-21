# dynamic-game-grid
A attempt to make a grid type that can be used for different games

## Purpose
I often come up with game ideas that take place on a grid, and get so caught up thinking about the grid framework that I lose track of the game itself. This particular project attempts to remedy that in some way by creating a grid that can expand in any direction and that can have custom components added to each cell so that they are flexible.

### Requirements
- The grid must expand in any direction at runtime
- The grid must support positive, negative, and zero coordinates on both axes
- The cells of the grid must be extendable for any game this library is used in

## Folder Structure

### GameGridLibrary
Contains the source code for the Grid (GameGrid), cells in the grid (GridCell), and a generic component to attch to a cell (CellComponent)
Builds to a folder "debug/GameGrid" at the root level, and the library can be used from there.
Builds with cmake because I wanted to learn a bit about that.

### QuickTest
A console application that implements Dynamic Game Grid and prints various contructed grids. Not automated, and kind of expects that you know what to look for when you run it. Not a great test.
Should be built to a directory such as "build_QuickTest" at the root level.
Builds with qmake because I'm more familiar with that.

### TicTacToe
A sample application with a Qt GUI.
Should be built to a directory such as "build_TicTacToe" at the root level.
Builds with qmake.