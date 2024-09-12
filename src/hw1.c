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
bool horizontalFour(char, int, int);
bool verticalFour(char, int, int);
bool mainDiagonalFour(char, int, int);
bool antiDiagonalFour(char, int, int);
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
    } else if (isFourInARow(piece, row, col)) {
        printf("Invalid choice. You have created 4-in-a-row.\n");
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

bool horizontalFour(char p, int r, int c) {
    board[r][c] = p;
    int left = c - 1;
    int right = c + 1;
    int counter = 1;

    while (board[r][left] == p && left >= 0 && counter != 4) {
        left--;
        counter++;
    }
    while (board[r][right] == p && right <= rows && counter != 4) {
        right++;
        counter++;
    }

    if (counter == 4) {
        board[r][c] = '-';
        return true;
    } else {
        return false;
    }
}

bool verticalFour(char p, int r, int c) {
    board[r][c] = p;
    int up = r - 1;
    int down = r + 1;
    int counter = 1;

    while (board[up][c] == p && up >= 0 && counter != 4) {
        up--;
        counter++;
    }
    while (board[down][c] == p && down <= cols && counter != 4) {
        down++;
        counter++;
    }

    if (counter == 4) {
        board[r][c] = '-';
        return true;
    } else {
        return false;
    }
}

bool mainDiagonalFour(char p, int r, int c) {
    board[r][c] = p;
    int up = r - 1;
    int down = r + 1;
    int left = c - 1;
    int right = c + 1;
    int counter = 1;

    while (board[up][left] == p && up >= 0 && left >= 0 && counter <= 4) {
        up--;
        left--;
        counter++;
    }
    while (board[down][right] == p && down <= rows && right <= cols && counter <= 4) {
        down++;
        right++;
        counter++;
    }

    if (counter == 4) {
        board[r][c] = '-';
        return true;
    } else {
        return false;
    }
}

bool antiDiagonalFour(char p, int r, int c) {
    board[r][c] = p;
    int up = r - 1;
    int down = r + 1;
    int left = c - 1;
    int right = c + 1;
    int counter = 1;

    while (board[down][left] == p && down <= rows && left >= 0 && counter <= 4) {
        down++;
        left--;
        counter++;
    }
    while (board[up][right] == p && up >= 0 && right <= cols && counter <= 4) {
        up--;
        right++;
        counter++;
    }

    if (counter == 4) {
        board[r][c] = '-';
        return true;
    } else {
        return false;
    }
}

bool isFourInARow(char p, int r, int c) {
    if (horizontalFour(p, r, c) == true || verticalFour(p, r, c) == true || mainDiagonalFour(p, r, c) == true || antiDiagonalFour(p, r, c) == true) {
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

    rows = num_rows;
    cols = num_cols;

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
