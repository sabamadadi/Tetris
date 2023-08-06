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

Shape copyShape(Shape shape) {
    Shape newShape = shape;
    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            newShape.array[i][j] = shape.array[i][j];
        }
    }
    return newShape;
}

void deleteShape(Shape shape) {
}

bool checkPosition(Shape shape) {
    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            if ((shape.col + j < 0 || shape.col + j >= COLS || shape.row + i >= ROWS)) {
                if (shape.array[i][j])
                    return false;
            } else if (Table[shape.row + i][shape.col + j] && shape.array[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void setNewRandomShape() {
    Shape newShape = copyShape(ShapesArray[rand() % NUM_SHAPES]);

    newShape.col = rand() % (COLS - newShape.width + 1);
    newShape.row = 0;
    deleteShape(current);
    current = newShape;
    if (!checkPosition(current)) {
        gameOn = false;
    }
}

void rotateShape(Shape* shape) {
    Shape temp = copyShape(*shape);
    int width = shape->width;
    for (int i = 0; i < width; i++) {
        for (int j = 0, k = width - 1; j < width; j++, k--) {
            shape->array[i][j] = temp.array[k][i];
        }
    }
    deleteShape(temp);
}

void writeToTable() {
    for (int i = 0; i < current.width; i++) {
        for (int j = 0; j < current.width; j++) {
            if (current.array[i][j])
                Table[current.row + i][current.col + j] = current.array[i][j];
            }
        }
    }
}

void checkFullRows() {
    for (int i = ROWS - 1; i >= 0; i--) {
        bool rowFull = true;
        for (int j = 0; j < COLS; j++) {
            if (!Table[i][j]) {
                rowFull = false;
                break;
            }
        }
        if (rowFull) {
            score += 10;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < COLS; j++) {
                    Table[k][j] = Table[k - 1][j];
                }
            }
            for (int j = 0; j < COLS; j++) {
                Table[0][j] = 0;
            }
        }
    }
}

void displayTable() {
    printf("\nScore: %d\n", score);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(Table[i][j] ? "X" : " ");
        }
        printf("\n");
    }
}

void updateTable() {
    if (checkPosition((Shape){.array = current.array, .width = current.width, .row = current.row + 1, .col = current.col})) {
        current.row++;
    } else {
        writeToTable();
        checkFullRows();
        setNewRandomShape();
    }
}

void moveShapeLeft() {
    if (checkPosition((Shape){.array = current.array, .width = current.width, .row = current.row, .col = current.col - 1})) {
        current.col--;
    }
}

void moveShapeRight() {
    if (checkPosition((Shape){.array = current.array, .width = current.width, .row = current.row, .col = current.col + 1})) {
        current.col++;
    }
}

void gameLoop() {
    while (gameOn) {
        displayTable();
        updateTable();
        usleep(timer);
        if (timer - decrease > 0) {
            timer -= decrease;
        }
    }
}

int main() {
    srand(time(NULL));
    setNewRandomShape();
    gameLoop();
    return 0;
}
