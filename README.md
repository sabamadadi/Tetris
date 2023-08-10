# Tetris Game

This is a simple implementation of the classic game Tetris in C programming language. The game is played on a grid-based board, where different shapes called "tetrominoes" fall from the top of the board. The player's goal is to arrange these tetrominoes to form complete rows, which will then be cleared from the board. The game ends when the tetrominoes stack up and reach the top of the board.

## How to Play

The game is played using the following controls:

- **A** or **a**: Move the current tetromino to the left.
- **D** or **d**: Move the current tetromino to the right.
- **S** or **s**: Move the current tetromino down faster.
- **W** or **w**: Rotate the current tetromino clockwise.

The objective of the game is to score as many points as possible by clearing rows. Each row cleared earns the player 10 points.

## Code Structure

The code consists of several functions and data structures:

- `Shape` structure: Represents a tetromino shape, including its array representation, width, row, and column.
- `ShapesArray` constant: An array of the seven tetromino shapes available in the game.
- `Table` array: Represents the game board, storing the positions of the tetrominoes.
- `score` variable: Tracks the player's score.
- `gameOn` variable: Indicates whether the game is still running.
- `timer` variable: Controls the speed at which the tetrominoes fall.
- `decrease` variable: Specifies the rate at which the timer decreases over time.

The code also includes various functions for initializing the game, handling key presses, moving and rotating tetrominoes, checking positions, and updating the game board.

## Running the Game

To run the game, you need a C compiler installed on your system. Save the code to a file with a `.c` extension, such as `tetris.c`. Then, compile the code using the following command:

```
gcc tetris.c -o tetris
```

After successful compilation, run the game by executing the generated executable:

```
./tetris
```

The game will start, and you can use the controls mentioned above to play the game.

## Notes

This implementation of Tetris is a simplified version and may not include all the features found in commercial versions. It serves as a basic example to understand the game's mechanics and implement a simple version of it.

Feel free to modify and enhance the code to add additional features, such as levels, high scores, or graphical interfaces, to make it more interactive and enjoyable.

Have fun playing Tetris!
