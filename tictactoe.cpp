#include <iostream>
#include <vector>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    int moves;

public:
    TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X'), moves(0) {}

    void displayBoard() const {
        std::cout << "   1   2   3\n";
        for (int i = 0; i < 3; ++i) {
            char rowLabel = 'A' + i;
            std::cout << rowLabel << " ";
            for (int j = 0; j < 3; ++j) {
                std::cout << " " << board[i][j] << " ";
                if (j < 2)
                    std::cout << "|";
            }
            std::cout << "\n";
            if (i < 2)
                std::cout << "  ---+---+---\n";
        }
    }

    bool checkWin(char player) const {
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

    bool isValidMove(int row, int col) const {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
    }

    void makeMove(int row, int col) {
        board[row][col] = currentPlayer;
        ++moves;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }

    int getMoves() const {
        return moves;
    }
};

int main() {
    TicTacToe game;
    std::cout << "Welcome to Tic Tac Toe!\n";

    while (game.getMoves() < 9) {
        game.displayBoard();

        int row, col;
        char colChar;

        std::cout << "Player " << game.getCurrentPlayer() << ", enter your move (e.g., A1): ";
        std::cin >> colChar >> row;

        // Convert column character to index (0-based)
        col = colChar - '1';

        // Convert row character to index (0-based)
        row = toupper(row) - 'A';

        if (!std::isalpha(colChar) || !std::isdigit(row + '0') || !game.isValidMove(row, col)) {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }

        game.makeMove(row, col);

        if (game.checkWin(game.getCurrentPlayer())) {
            game.displayBoard();
            std::cout << "Player " << game.getCurrentPlayer() << " wins!\n";
            return 0;
        }

        game.switchPlayer();
    }

    game.displayBoard();
    std::cout << "It's a draw!\n";

    return 0;
}
