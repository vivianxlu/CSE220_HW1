#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "hw1.h"
// #include "../include/hw1.h"

char board[MAX_ROWS][MAX_COLS] = {0};
int rows;
int cols;
char piece;
int row;
int col;
void printGameBoard(int, int);
void printGamePrompts(int, int);
bool horizontalFour(char, int, int);
bool verticalFour(char, int, int);
bool mainDiagonalFour(char, int, int);
bool antiDiagonalFour(char, int, int);
bool isFourInARow(char, int, int);
bool isBoardFilled(int, int);

/*
Hint: Consider adding a global variable to store a string large enough to store a board.
*/

/* --- START | MULTIPURPOSE --- */
void printGameBoard(int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void printGamePrompts(int numRows, int numCols) {
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
    printf("Choose a row (0-%d): ", numRows - 1);
    scanf(" %d", &row);

    while (true) {
        if (!(row >= 0 && row <= numRows)) {
            printf("Invalid choice. Choose a row (0-%d): ", numRows - 1);
            scanf(" %d", &row);
        } else {
            break;
        }
    }
    
    /* Choose a column */
    printf("Choose a column (0-%d): ", numCols - 1);
    scanf(" %d", &col);

    while (true) {
        if (!(col >= 0 && col <= numCols)) {
            printf("Invalid choice. Choose a column (0-%d): ", numCols - 1);
            scanf(" %d", &col);
        } else {
            break;
        }
    }

    if (board[row][col] != '-') {
        /* Check if the chosen space is filled */
        printf("Invalid choice. That space is already occupied.\n");
        printGameBoard(numRows, numCols);
        printGamePrompts(numRows, numCols);
    } else if (isFourInARow(piece, row, col)) {
        printf("Invalid choice. You have created 4-in-a-row.\n");
        printGameBoard(numRows, numCols);
        printGamePrompts(numRows, numCols);
    } else {
        board[row][col] = piece;

        if (isBoardFilled(numRows, numCols) == false) {
            printGameBoard(numRows, numCols);
            printGamePrompts(numRows, numCols);
        } else {
            printf("Congratulations, you have filled the board with no 4-in-a-rows!\n");
            printGameBoard(numRows, numCols);
        }
    }

}

bool isBoardFilled(int numRows, int numCols) {
    bool filled = true;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (board[i][j] == '-') {
                filled = false;
            }
        }
    }

    return filled;
}
/* --- START | MULTIPURPOSE --- */

/* --- START | For the initialize_board function --- */
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
/* --- END | For the initialize_board function --- */

/* --- START | For the solve function --- */
bool horiFour(char currPiece, int currRow, int currCol, int totalCols) {
        int left = currCol - 1;
        int right = currCol + 1;
        int counter = 1;
        
        while (left >= 0 && board[currRow][left] == currPiece && counter != 4) {
            left--;
            counter++;
        }
        while (right < totalCols && board[currRow][right] == currPiece && counter != 4) {
            right++;
            counter++;
        }
        if (counter == 4) {
            return true;
        } else {
            return false;
        }
        
    }

bool vertFour(char currPiece, int currRow, int currCol, int totalRows) {
        int up = currRow - 1;
        int down = currRow + 1;
        int counter = 1;

        while (board[up][currCol] == currPiece && up >= 0 && counter != 4) {
            up--;
            counter++;
        }
        while (board[down][currCol] == currPiece && down < totalRows && counter != 4) {
            down++;
            counter++;
        }

        if (counter == 4) {
            return true;
        }
        return false;
    }

bool mainDiagFour(char currPiece, int currRow, int currCol, int totalRows, int totalCols) {
        int up = currRow - 1;
        int down = currRow + 1;
        int left = currCol - 1;
        int right = currCol + 1;
        int counter = 1;

        while (board[up][left] == currPiece && up >= 0 && left >= 0 && counter != 4) {
            up--;
            left--;
            counter++;
        }
        while (board[down][right] == currPiece && down < totalRows && right < totalCols && counter != 4) {
            down++;
            right++;
            counter++;
        }

        if (counter == 4) {
            return true;
        }
        return false;
    }

bool antiDiagFour(char currPiece, int currRow, int currCol, int totalRows, int totalCols) {
        int up = currRow - 1;
        int down = currRow + 1;
        int left = currCol - 1;
        int right = currCol + 1;
        int counter = 1;

        while (board[down][left] == currPiece && down < totalRows && left >= 0 && counter != 4) {
            down++;
            left--;
            counter++;
        }
        while (board[up][right] == currPiece && up >= 0 && right < totalCols && counter != 4) {
            up--;
            right++;
            counter++;
        }

        if (counter == 4) {
            return true;
        }
        return false;
    }

bool solveIsFourInARow(char currPiece, int currRow, int currCol, int totalRows, int totalCols) {
        if (currPiece != '-') {
            if (horiFour(currPiece, currRow, currCol, totalCols) == true || vertFour(currPiece, currRow, currCol, totalRows) == true ||
            mainDiagFour(currPiece, currRow, currCol, totalRows, totalCols) == true || antiDiagFour(currPiece, currRow, currCol, totalRows, totalCols) == true) {
                return true;
            }
        }
        return false;
    }

bool containsInvalidCharacters(char currPiece) {
        if (currPiece != 'x' && currPiece != 'o' && currPiece != '-') {
            return true;
        }
        return false;
    }

int checkInitialBoardState(int totalRows, int totalCols) {
        int invalidCharactersCount = 0;
        int fourInARowCount = 0;

        for (int r = 0; r < totalRows; r++) {
            for (int c = 0; c < totalCols; c++) {
                if (containsInvalidCharacters(board[r][c])) {
                    /* Check for Invalid Characters */
                    invalidCharactersCount++;
                }
                if (solveIsFourInARow(board[r][c], r, c, totalRows, totalCols)) {
                    /* Check for Four in a Row */
                    fourInARowCount++;
                }
            }
        }

        if ((invalidCharactersCount > 0 && fourInARowCount > 0) || (invalidCharactersCount > 0 && fourInARowCount == 0)) {
            return INITIAL_BOARD_INVALID_CHARACTERS;
        } else if (invalidCharactersCount == 0 && fourInARowCount > 0) {
            return INITIAL_BOARD_FOUR_IN_A_ROW;
        } else {
            return 0;
        }
    }
/* --- END | For the solve function --- */


void initialize_board(const char *initial_state, int num_rows, int num_cols) {

    // Compute the length of the initial_state string
    int initial_state_length = strlen(initial_state);

    // Check Edge Cases
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
    
    rows = num_rows;
    cols = num_cols; //global~ variable~
    int countX = 0;
    int countO = 0;

    /* Fill the board with values from initial_state */
    int currentPieceIndex = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            board[i][j] = initial_state[currentPieceIndex++];
        }
    }

    /* Print the board */
    printGameBoard(num_rows, num_cols);
    /* Check and return error values */
    if (checkInitialBoardState(num_rows, num_cols) == -2) {
        return INITIAL_BOARD_INVALID_CHARACTERS;
    } else if (checkInitialBoardState(num_rows, num_cols) == -1) {
        return INITIAL_BOARD_FOUR_IN_A_ROW;
    } else {
        while (true) {
            int piecesPlaced = 0;
            for (int r = 0; r < num_rows; r++) {
                for (int c = 0; c < num_cols; c++) {
                    if (board[r][c] == '-') {
                        board[r][c] = 'x';
                        if (solveIsFourInARow('x', r, c, num_rows, num_cols)) {
                            board[r][c] = 'o';
                            if (solveIsFourInARow('o', r, c, num_rows, num_cols)) {
                                return INITIAL_BOARD_NO_SOLUTION;
                            } else {
                                piecesPlaced++;
                                printf("Placed down o: %d at [%d][%d]\n", piecesPlaced, r, c);
                                printGameBoard(num_rows, num_cols);
                                printf("\n");
                                continue;
                            }
                        } else {
                            board[r][c] = 'o';
                            if (solveIsFourInARow('o', r, c, num_rows, num_cols)) {
                                board[r][c] = 'x';
                                if (solveIsFourInARow('x', r, c, num_rows, num_cols)) {
                                    return INITIAL_BOARD_NO_SOLUTION;
                                } else {
                                    piecesPlaced++;
                                    printf("Placed down x: %d at [%d][%d]\n", piecesPlaced, r,c);
                                    printGameBoard(num_rows, num_cols);
                                    printf("\n");
                                    continue;
                                }
                            }
                        }
                        board[r][c] = '-';
                    }
                }
            }
            printf("Exited the for loop :D. Pieces Placed: %d\n", piecesPlaced);
            if (piecesPlaced == 0 && !isBoardFilled(num_rows, num_cols)) {
                printf("%d Hi failed", piecesPlaced);
                return HEURISTICS_FAILED;
            }
            if (isBoardFilled(num_rows, num_cols)) {
                for (int r = 0; r < num_rows; r++) {
                    for (int c = 0; c < num_cols; c++) {
                        if (board[r][c] == 'x') {
                            countX++;
                        } else {
                            countO++;
                        }
                    }
                }
                printGameBoard(num_rows, num_cols);
                *num_x = countX;
                *num_o = countO;
                printf("X's : %d and O's: %d", countX, countO);
                return FOUND_SOLUTION;
            }
        }
    }

    return 0;
}

char* generate_medium(const char *final_state, int num_rows, int num_cols) { 

    return 0;
}
