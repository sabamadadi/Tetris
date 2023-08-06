# Tetris Game

This is a simple implementation of the Tetris game in C. The program uses ASCII characters to display the game board and shapes.

## Compilation and Execution

To compile the program, you can use a C compiler such as GCC:

```bash
gcc tetris.c -o tetris
```

To run the game, execute the compiled binary:

```bash
./tetris
```

## Gameplay

The game starts with an empty game board represented by a grid of cells. Shapes consisting of blocks fall from the top of the board, and the player can move and rotate the shapes to create horizontal lines of blocks. When a complete line is formed, it is cleared, and the player earns points.

The available shapes are:

1. S shape
2. Z shape
3. T shape
4. L shape
5. Flipped L shape
6. Square shape
7. Long bar shape

### Controls

- Move left: Press the left arrow key or 'A' key.
- Move right: Press the right arrow key or 'D' key.
- Rotate: Press the up arrow key or 'W' key.
- Soft drop: Press the down arrow key or 'S' key.
- Hard drop: Press the spacebar key.

### Scoring

- Each cleared line earns the player 10 points.

### Game Over

The game ends when a new shape cannot be placed at the top of the board. The final score is displayed, and the game can be restarted by running the program again.

## Code Structure

The code is structured as follows:

- The `Shape` struct represents a Tetris shape and stores its array, width, row, and column.
- The `ShapesArray` array contains the predefined shapes.
- The `Table` array represents the game board.
- The `score` variable stores the player's score.
- The `gameOn` variable controls the game loop.
- The `timer` variable controls the speed of the falling shapes.
- The `decrease` variable determines the rate at which the timer decreases over time.
- The `copyShape` function creates a copy of a given shape.
- The `deleteShape` function is not implemented in the provided code.
- The `checkPosition` function checks if a shape can be placed at its current position.
- The `setNewRandomShape` function selects a new random shape and places it at the top of the board.
- The `rotateShape` function rotates a shape 90 degrees clockwise.
- The `writeToTable` function updates the game board with the current shape.
- The `checkFullRows` function checks if any rows are completely filled and clears them.
- The `displayTable` function prints the current state of the game board.
- The `updateTable` function updates the game board based on the current shape's position.
- The `moveShapeLeft` and `moveShapeRight` functions move the current shape horizontally.
- The `gameLoop` function contains the main game loop and handles user input and game updates.
- The `main` function initializes the game and starts the game loop.

----------------

Many thanks to [Najib Ghadri](https://www.linkedin.com/in/najibghadri/) for giving me the original idea of implementing this game in the C language, and this is the first program I have written entirely in C :)
