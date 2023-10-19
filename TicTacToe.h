#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TicTacToe {
  private:
    vector<vector<char>> board;
    char currentPlayer;
    int moves;

  public:
    TicTacToe();
    void displayBoard() const;
    bool checkWin(char player) const;
    bool isValidMove(int row, int col) const;
    void makeMove(int row, int col);
    void switchPlayer();
    char getCurrentPlayer() const;
    int getMoves() const;
};
