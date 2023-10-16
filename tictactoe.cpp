#include <iostream>
#include <vector>

using namespace std;

// Function to display the Tic Tac Toe board
void displayBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "---------\n";
    }
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));  // Initialize an empty 3x3 board

    char currentPlayer = 'X';  // Player X starts the game

    cout << "Welcome to Tic Tac Toe!\n";

    int row, col;
    int moves = 0;
    while (moves < 9) {
        displayBoard(board);

        // Get player's move
        cout << "Player " << currentPlayer << ", enter your move (row [0-2] and column [0-2]): ";
        cin >> row >> col;

        // Check if the move is valid
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        // Update the board with the player's move
        board[row][col] = currentPlayer;
        ++moves;

        // Check if the current player has won
        if (checkWin(board, currentPlayer)) {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            return 0;
        }

        // Switch to the other player for the next turn
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    displayBoard(board);
    cout << "It's a draw!\n";

    return 0;
}
