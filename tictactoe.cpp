#include "TicTacToe.h"

TicTacToe::TicTacToe()
    : board(3, vector<char>(3, ' ')), currentPlayer('X'), moves(0) {}

void TicTacToe::displayBoard() const {
    cout << "   1   2   3\n";
    for (int i = 0; i < 3; ++i) {
        char rowLabel = 'A' + i;
        cout << rowLabel << " ";
        for (int j = 0; j < 3; ++j) {
            cout << " " << board[i][j] << " ";
            if (j < 2)
                cout << "|";
        }
        cout << "\n";
        if (i < 2)
            cout << "  ---+---+---\n";
    }
}

bool TicTacToe::checkWin(char player) const {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player &&
            board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player &&
            board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool TicTacToe::isValidMove(int row, int col) const {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 &&
            board[row][col] == ' ');
}

void TicTacToe::makeMove(int row, int col) {
    board[row][col] = currentPlayer;
    ++moves;
}

void TicTacToe::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

char TicTacToe::getCurrentPlayer() const { return currentPlayer; }

int TicTacToe::getMoves() const { return moves; }
