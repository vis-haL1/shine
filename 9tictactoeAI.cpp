#include <iostream>
#include <limits>
#include <cstdlib> 

using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'O';
const char PLAYER_O = 'X'; 

void printBoard(char board[3][3]) {
   
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << '|';
        }
        cout << endl;
        if (i < 2) cout << "-----\n";
    }
    cout << endl;
}

bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) return false;
        }
    }
    return true;
}

int evaluate(char board[3][3]) {
    if (checkWin(board, PLAYER_X)) return 10;
    if (checkWin(board, PLAYER_O)) return -10;
    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (checkDraw(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

void bestMove(char board[3][3]) {
    int bestVal = numeric_limits<int>::min();
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    if (moveRow != -1 && moveCol != -1) {
        board[moveRow][moveCol] = PLAYER_X;
    }
}

void playerMove(char board[3][3]) {
    int x, y;
    while (true) {
        cout << "Enter your move (row and column, 0-2): ";
        cin >> x >> y;
        if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != EMPTY) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid move. Please enter valid row and column (0-2) for an empty cell.\n";
        } else {
            board[x][y] = PLAYER_O;
            break;
        }
    }
}

int main() {
    char board[3][3] = {{EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}};
    bool playerTurn = true;

    while (true) {
        printBoard(board);
        if (playerTurn) {
            playerMove(board);
            if (checkWin(board, PLAYER_O)) {
                printBoard(board);
                cout << "Player O wins!\n";
                break;
            }
        } else {
            bestMove(board);
            if (checkWin(board, PLAYER_X)) {
                printBoard(board);
                cout << "Player X wins!\n";
                break;
            }
        }

        if (checkDraw(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }

        playerTurn = !playerTurn;
    }

    return 0;
}