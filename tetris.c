#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 20
#define COLS 15
#define SHAPE_SIZE 4
#define NUM_SHAPES 7

char Table[ROWS][COLS] = {0};
int score = 0;
bool gameOn = true;
int timer = 400000;
int decrease = 1000;

typedef struct {
    char array[SHAPE_SIZE][SHAPE_SIZE];
    int width, row, col;
} Shape;

Shape current;

const Shape ShapesArray[NUM_SHAPES] = {
    {.array = {
        {' ', 'X', 'X', ' '},
        {'X', 'X', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }, .width = 3},  // S
    {.array = {
        {'X', 'X', ' ', ' '},
        {' ', 'X', 'X', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }, .width = 3},  // Z
    {.array = {
        {' ', 'X', ' ', ' '},
        {'X', 'X', 'X', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }, .width = 3},  // T
    {.array = {
        {'X', ' ', ' ', ' '},
        {'X', 'X', 'X', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }, .width = 3},  // L
    {.array = {
        {' ', ' ', 'X', ' '},
        {'X', 'X', 'X', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }, .width = 3},  // Flipped L
    {.array = {
        {'X', 'X', ' ', ' '},
        {'X', 'X', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }, .width = 2},  // Square
    {.array = {
        {'X', ' ', ' ', ' '},
        {'X', ' ', ' ', ' '},
        {'X', ' ', ' ', ' '},
        {'X', ' ', ' ', ' '}
    }, .width = 4}  // Long bar
};

// Function to create a copy of a shape
Shape copyShape(Shape shape) {
    Shape newShape = shape;
    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            newShape.array[i][j] = shape.array[i][j];
        }
    }
    return newShape;
}

// Function to check if a position is valid for a shape
bool checkPosition(Shape shape) {
    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            if (shape.col + j < 0 || shape.col + j >= COLS || shape.row + i >= ROWS) {
                // Check if the shape is outside the boundaries of the table
                if (shape.array[i][j])
                    return false;
            } else if (Table[shape.row + i][shape.col + j] && shape.array[i][j]) {
                // Check if the shape overlaps with existing blocks on the table
                return false;
            }
        }
    }
    return true;
}

// Function to set a new random shape
void setNewRandomShape() {
    Shape newShape = copyShape(ShapesArray[rand() % NUM_SHAPES]);

    newShape.col = rand() % (COLS - newShape.width + 1);
    newShape.row = 0;
    // Assign the new shape as the current shape
    current = newShape;
    if (!checkPosition(current)) {
        // If the new shape is not in a valid position, end the game
        gameOn = false;
    }
}

// Function to rotate a shape
void rotateShape(Shape* shape) {
    Shape temp = copyShape(*shape);
    int width = shape->width;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            shape->array[i][j] = temp.array[width - j - 1][i];
        }
    }
}

// Function to move thecurrent shape down
void moveDown() {
    Shape temp = copyShape(current);
    temp.row++;
    if (checkPosition(temp)) {
        current = temp;
    } else {
        // If the current shape cannot move down further, add it to the table and check for completed rows
        for (int i = 0; i < SHAPE_SIZE; i++) {
            for (int j = 0; j < SHAPE_SIZE; j++) {
                if (current.array[i][j]) {
                    Table[current.row + i][current.col + j] = current.array[i][j];
                }
            }
        }
        // Check for completed rows
        for (int i = ROWS - 1; i >= 0; i--) {
            bool rowCompleted = true;
            for (int j = 0; j < COLS; j++) {
                if (!Table[i][j]) {
                    rowCompleted = false;
                    break;
                }
            }
            if (rowCompleted) {
                // If a row is completed, remove it and move all the rows above it down
                for (int k = i; k > 0; k--) {
                    for (int j = 0; j < COLS; j++) {
                        Table[k][j] = Table[k - 1][j];
                    }
                }
                // Clear the top row
                for (int j = 0; j < COLS; j++) {
                    Table[0][j] = ' ';
                }
                score += 10;  // Increase the score
            }
        }
        setNewRandomShape();  // Set a new random shape
    }
}

// Function to move the current shape left
void moveLeft() {
    Shape temp = copyShape(current);
    temp.col--;
    if (checkPosition(temp)) {
        current = temp;
    }
}

// Function to move the current shape right
void moveRight() {
    Shape temp = copyShape(current);
    temp.col++;
    if (checkPosition(temp)) {
        current = temp;
    }
}

// Function to handle key presses
void handleKeyPress(char key) {
    if (key == 'a' || key == 'A') {
        moveLeft();
    } else if (key == 'd' || key == 'D') {
        moveRight();
    } else if (key == 's' || key == 'S') {
        moveDown();
    } else if (key == 'w' || key == 'W') {
        Shape temp = copyShape(current);
        rotateShape(&temp);
        if (checkPosition(temp)) {
            current = temp;
        }
    }
}

// Function to display the game board
void display() {
    system("clear");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", Table[i][j] ? Table[i][j] : ' ');
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    setNewRandomShape();  // Set the initial shape

    while (gameOn) {
        display();  // Display the game board
        usleep(timer);  // Pause for a short duration
        moveDown();  // Move the current shape down
        timer -= decrease;  // Decrease the timer
        if (timer < 1000) {
            timer = 1000;
        }
    }

    printf("Game Over! Your score is: %d\n", score);
    return 0;
}
