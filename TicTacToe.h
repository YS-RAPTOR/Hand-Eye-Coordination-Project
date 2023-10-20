#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class TicTacToe {
  private:
    vector<vector<char>> board;
    char currentPlayer;
    int moves;

  public:
    TicTacToe();
    void DisplayBoard() const;
    bool CheckWin(char player) const;
    bool IsValidMove(int row, int col) const;
    void MakeMove(int row, int col);
    void SwitchPlayer();
    char GetCurrentPlayer() const;
    int GetMoves() const;
    bool CheckEqual(vector<vector<char>> otherBoard) const;
};
