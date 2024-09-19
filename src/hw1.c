#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "hw1.h"
// #include "../include/hw1.h"

char board[MAX_ROWS][MAX_COLS] = {0};
char copiedBoard[MAX_ROWS][MAX_COLS] = {0};
char copiedBoardStr[MAX_ROWS * MAX_COLS] = "";
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

    while (left >= 0 && board[r][left] == p && counter != 4) {
        left--;
        counter++;
    }
    while (right <= rows && board[r][right] == p && counter != 4) {
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

    while (up >= 0 && board[up][c] == p && counter != 4) {
        up--;
        counter++;
    }
    while (down <= cols && board[down][c] == p && counter != 4) {
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

    while (up >= 0 && left >= 0 && board[up][left] == p && counter <= 4) {
        up--;
        left--;
        counter++;
    }
    while (down <= rows && right <= cols && board[down][right] == p && counter <= 4) {
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

    while (down <= rows && left >= 0 && board[down][left] == p && counter <= 4) {
        down++;
        left--;
        counter++;
    }
    while (up >= 0 && right <= cols && board[up][right] == p && counter <= 4) {
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

        while (up >= 0 && board[up][currCol] == currPiece && counter != 4) {
            up--;
            counter++;
        }
        while (down < totalRows && board[down][currCol] == currPiece && counter != 4) {
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

        while (up >= 0 && left >= 0 && board[up][left] == currPiece && counter != 4) {
            up--;
            left--;
            counter++;
        }
        while (down < totalRows && right < totalCols && board[down][right] == currPiece && counter != 4) {
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

        while (down < totalRows && left >= 0 && board[down][left] == currPiece && counter != 4) {
            down++;
            left--;
            counter++;
        }
        while (up >= 0 && right < totalCols && board[up][right] == currPiece && counter != 4) {
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

void setCopiedBoard(int totalRows, int totalCols) {
    for (int r = 0; r < totalRows; r++) {
        for (int c = 0; c < totalCols; c++) {
            copiedBoard[r][c] = board[r][c];
        }
    }
}

void setGlobalBoard(int totalRows, int totalCols) {
    for (int r = 0; r < totalRows; r++) {
        for (int c = 0; c < totalCols; c++) {
            board[r][c] = copiedBoard[r][c];
        }
    }
}

void copiedBoardToString(int totalRows, int totalCols) {
    int strIndex = 0;

    for (int r = 0; r < totalRows; r++) {
        for (int c = 0; c < totalCols; c++) {
            copiedBoardStr[strIndex++] = copiedBoard[r][c];
        }
    }
}

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
                                    continue;
                                }
                            }
                        }
                        board[r][c] = '-';
                    }
                }
            }
            if (piecesPlaced == 0 && !isBoardFilled(num_rows, num_cols)) {
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
                *num_x = countX;
                *num_o = countO;
                return FOUND_SOLUTION;
            }
        }
    }

    return 0;
}


char* generate_medium(const char *final_state, int num_rows, int num_cols) { 
    
    int num_x = 0;
    int num_o = 0;

    int currentPieceIndex = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            board[i][j] = final_state[currentPieceIndex++];
        }
    }

    setCopiedBoard(num_rows, num_cols);

    bool piecesRemoved = false;

    while (true) {
        for (int r = 0; r < num_rows; r++) {
            for (int c = 0; c < num_cols; c++) {
                board[r][c] = '-';
                if (solve(final_state, num_rows, num_cols, &num_x, &num_o)) {
                    copiedBoard[r][c] = '-';
                    setGlobalBoard(num_rows, num_cols);
                    piecesRemoved = true;
                    continue;
                }
            }
        }
        if (piecesRemoved) {
            continue;
        } else {
            break;
        }
    }
    copiedBoardToStr(num_rows, num_cols);
    return copiedBoardStr;
}
