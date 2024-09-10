#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "hw1.h"

char board[MAX_ROWS][MAX_COLS] = {0};
int rows;
int cols;
char piece;
int row;
int col;
void printGameBoard();
void printGamePrompts();
bool horizontalFour(char, int);
bool verticalFour(char, int);
bool diagonalFour(char, int, int);
bool isFourInARow(char, int, int);
bool isBoardFilled();

/*
Hint: Consider adding a global variable to store a string large enough to store a board.
*/


void printGameBoard(int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void printGamePrompts(int num_rows, int num_cols) {
    // Choose a piece
    printf("Choose a piece (x or o) or q to quit: ");
    scanf(" %c", &piece);

    if (piece == 'q') {
        return;
    }

    while (true) {
        if (piece != 'x' && piece != 'o' && piece != 'q') {
            printf("Invalid choice. Choose a piece (x or o) or q to quit: ");
            scanf(" %c", &piece);
        } else {
            break;
        }
    }
    
    /* Choose a row */
    printf("Choose a row (0-%d): ", num_rows - 1);
    scanf(" %d", &row);

    while (true) {
        if (!(row >= 0 && row <= num_rows)) {
            printf("Invalid choice. Choose a row (0-%d): ", num_rows - 1);
            scanf(" %d", &row);
        } else {
            break;
        }
    }
    
    /* Choose a column */
    printf("Choose a column (0-%d): ", num_cols - 1);
    scanf(" %d", &col);

    while (true) {
        if (!(col >= 0 && col <= num_cols)) {
            printf("Invalid choice. Choose a column (0-%d): ", num_cols - 1);
            scanf(" %d", &col);
        } else {
            break;
        }
    }

    if (board[row][col] != '-') {
        /* Check if the chosen space is filled */
        printf("Invalid choice. That space is already occupied.\n");
        printGameBoard(num_rows, num_cols);
        printGamePrompts(num_rows, num_cols);
    } else {
        board[row][col] = piece;

        if (isBoardFilled(num_rows, num_cols) == false) {
            printGameBoard(num_rows, num_cols);
            printGamePrompts(num_rows, num_cols);
        } else {
            printf("Congratulations, you have filled the board!\n");
            printGameBoard(num_rows, num_cols);
        }
    }

    if (isFourInARow(piece, row, col) == true) {
        printf("Invalid choice.");
        printGameBoard(num_rows, num_cols);
        printGamePrompts(num_rows, num_cols);
    } else {
        board[row][col] = piece;

        if (isBoardFilled(num_rows, num_cols) == false) {
            printGameBoard(num_rows, num_cols);
            printGamePrompts(num_rows, num_cols);
        } else {
            printf("Congratulations, you have filled the board!\n");
            printGameBoard(num_rows, num_cols);
        }
    }
}


bool horizontalFour(char p, int r) {
    bool four = false;

    for (int i = 0; i < cols - 3; i++) {
        if (board[r][i] == p &&
            board[r][i + 1] == p &&
            board[r][i + 2] == p &&
            board[r][i + 3] == p) {
                four = true;
                break;
            }
    }

    return four;
}

bool verticalFour(char p, int c) {
    bool four = false;

    for (int i = 0; i < rows - 3; i++) {
        if (board[i][c] == p &&
            board[i + 1][c] == p &&
            board[i + 2][c] == p &&
            board[i + 3][c] == p) {
                four = true;
                break;
            }
    }

    return four;
}
/*
bool diagonalFour(char p, int r, int c) {
    bool four = false;

    for (int )

    return four;
}
*/

bool isFourInARow(char p, int r, int c) {
    if (horizontalFour(p, r) == true || verticalFour(p, c) == true) {
        return true;
    }
    return false;
}

bool isBoardFilled(num_rows, num_cols) {
    bool filled = true;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (board[i][j] == '-') {
                filled = false;
            }
        }
    }

    return filled;
}

void initialize_board(const char *initial_state, int num_rows, int num_cols) {

    // Compute the length of the initial_state string
    int initial_state_length = strlen(initial_state);

    // Edge Cases
    if (num_rows > MAX_ROWS) {
        printf("The number of rows that was entered exceeds the limit.");
        return;
    } else if (num_cols > MAX_ROWS) {
        printf("The number of columns that was entered exceeds the limit.");
        return;
    } else if (initial_state_length > MAX_ROWS * MAX_COLS) {
        printf("The length of the board's initial state exceeds the limit.");
        return;
    }

    /* Fill the board with values from initial_state */
    int currentPieceIndex = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            board[i][j] = initial_state[currentPieceIndex++];
        }
    }

    /* Print the board */
    printGameBoard(num_rows, num_cols);
    printGamePrompts(num_rows, num_cols);
}

int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o) {   

    return 0;
}

char* generate_medium(const char *final_state, int num_rows, int num_cols) { 

    return 0;
}
