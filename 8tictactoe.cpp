#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

void printBoard() {
    cout << "---------" << endl;
    for (int i = 0; i < 3; i++) {
        cout << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << endl;
        cout << "---------" << endl;
    }
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void userMove() {
    int row, col;
    while (true) {
        cout << "Enter your move (row & column): ";
        cin >> row >> col;
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = 'X';
            break;
        } else {
            cout << "This move is not valid" << endl;
        }
    }
    printBoard();
}

void computerMove() {
    int row, col;
    while (true) {
        row = rand() % 3;
        col = rand() % 3;
        if (board[row][col] == ' ') {
            board[row][col] = 'O';
            break;
        }
    }
    cout << "Computer moved:" << endl;
    printBoard();
}

int main() {
    srand(time(0));
    cout << "Let's begin Tic Tac Toe!" << endl;
    printBoard();
    computerMove();

    while (true) {
        userMove();
        if (checkWin('X')) {
            printBoard();
            cout << "You win!" << endl;
            break;
        }
        if (isBoardFull()) {
            printBoard();
            cout << "It's a tie!" << endl;
            break;
        }

        computerMove();
        if (checkWin('O')) {
            printBoard();
            cout << "Computer wins!" << endl;
            break;
        }
        if (isBoardFull()) {
            printBoard();
            cout << "It's a tie!" << endl;
            break;
        }
    }
    return 0;
}