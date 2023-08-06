#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

#define ROWS 20
#define COLS 15
#define TRUE 1
#define FALSE 0

char Table[ROWS][COLS] = {0};
int score = 0;
char GameOn = TRUE;
suseconds_t timer = 400000;
int decrease = 1000;

typedef struct {
    char **array;
    int width, row, col;
} Shape;
Shape current;

const Shape ShapesArray[7] = {
    {(char *[]){"XX ", " XX", "   "}, 3},  // S
    {(char *[]){" XX", "XX ", "   "}, 3},  // Z
    {(char *[]){" X ", "XXX", "   "}, 3},  // T
    {(char *[]){"X  ", "XXX", "   "}, 3},  // L
    {(char *[]){"  X", "XXX", "   "}, 3},  // Flipped L
    {(char *[]){"XX", "XX"},               // Square
     2},
    {(char *[]){"X   ", "X   ", "X   ", "X   "}, 4}  // Long bar
};

Shape CopyShape(Shape shape) {
    Shape new_shape = shape;
    char **copyshape = shape.array;
    new_shape.array = (char **)malloc(new_shape.width * sizeof(char *));
    int i, j;
    for (i = 0; i < new_shape.width; i++) {
        new_shape.array[i] = (char *)malloc(new_shape.width * sizeof(char));
        for (j = 0; j < new_shape.width; j++) {
            new_shape.array[i][j] = copyshape[i][j];
        }
    }
    return new_shape;
}

void DeleteShape(Shape shape) {
    int i;
    for (i = 0; i < shape.width; i++) {
        free(shape.array[i]);
    }
    free(shape.array);
}

int CheckPosition(Shape shape) {
    char **array = shape.array;
    int i, j;
    for (i = 0; i < shape.width; i++) {
        for (j = 0; j < shape.width; j++) {
            if ((shape.col + j < 0 || shape.col + j >= COLS || shape.row + i >= ROWS)) {
                if (array[i][j])
                    return FALSE;
            } else if (Table[shape.row + i][shape.col + j] && array[i][j]) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

void SetNewRandomShape() {
    Shape new_shape = CopyShape(ShapesArray[rand() % 7]);

    new_shape.col = rand() % (COLS - new_shape.width + 1);
    new_shape.row = 0;
    DeleteShape(current);
    current = new_shape;
    if (!CheckPosition(current)) {
        GameOn = FALSE;
    }
}

void RotateShape(Shape shape) {
    Shape temp = CopyShape(shape);
    int i, j, k, width;
    width = shape.width;
    for (i = 0; i < width; i++) {
        for (j = 0, k = width - 1; j < width; j++, k--) {
            shape.array[i][j] = temp.array[k][i];
        }
    }
    DeleteShape(temp);
}

void WriteToTable() {
    int i, j;
    for (i = 0; i < current.width; i++) {
        for (j = 0; j < current.width; j++) {
            if (current.array[i][j])
                Table[current.row + i][current.col + j] = current.array[i][j];
        }
    }
}

void RemoveFullRowsAndUpdateScore() {
    int i, j, sum, count = 0;
    for (i = 0; i < ROWS; i++) {
        sum = 0;
        for (j = 0; j < COLS; j++) {
            sum += Table[i][j];
        }
        if (sum == COLS) {
            count++;
            int k;
            for (k = i; k >= 1; k--)
                for (j = 0; j < COLS; j++)
                    Table[k][j] = Table[k - 1][j];
            for (j = 0; j < COLS; j++)
               Table[0][j] = 0;
        }
    }
    score += count * count;
}

void DrawTable() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (Table[i][j]) {
                mvprintw(i, j * 2, "[]");
            } else {
                mvprintw(i, j * 2, "  ");
            }
        }
    }
    mvprintw(ROWS, 0, "Score: %d", score);
}

void DrawShape(Shape shape) {
    int i, j;
    for (i = 0; i < shape.width; i++) {
        for (j = 0; j < shape.width; j++) {
            if (shape.array[i][j]) {
                mvprintw(shape.row + i, (shape.col + j) * 2, "[]");
            }
        }
    }
}

int main() {
    srand(time(NULL));

    initscr();
    noecho();
    curs_set(FALSE);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    SetNewRandomShape();

    while (GameOn) {
        clear();

        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        if (((current_time.tv_usec - start.tv_usec) >= timer)) {
            start = current_time;
            Shape temp = CopyShape(current);
            temp.row++;
            if (CheckPosition(temp))
                current.row++;
            else {
                WriteToTable();
                RemoveFullRowsAndUpdateScore();
                SetNewRandomShape();
            }
            DeleteShape(temp);
        }

        int c = getch();
        switch (c) {
            case 'q':
                GameOn = FALSE;
                break;
            case 'w':
                RotateShape(current);
                if (!CheckPosition(current))
                    RotateShape(current);
                break;
            case 'a':
                Shape temp = CopyShape(current);
                temp.col--;
                if (CheckPosition(temp))
                    current.col--;
                DeleteShape(temp);
                break;
            case 'd':
                temp = CopyShape(current);
                temp.col++;
                if (CheckPosition(temp))
                    current.col++;
                DeleteShape(temp);
                break;
            case 's':
                temp = CopyShape(current);
                temp.row++;
                if (CheckPosition(temp))
                    current.row++;
                DeleteShape(temp);
                break;
        }

        DrawTable();
        DrawShape(current);

        refresh();
    }

    endwin();

    return 0;
}
