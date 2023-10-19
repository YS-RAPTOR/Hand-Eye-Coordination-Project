#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "opencv2/core/matx.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <intrin0.inl.h>
#include <libserialport.h>
#include <opencv2/imgproc.hpp>

#define BAUD 9600

#include "ObjectDetection.h"
#include "TicTacToe.h"

using namespace cv;
using namespace std;

int main() {
    string folder = "../../Pictures/";
    string file_header = "Im";
    cout << Mat();
    for (int i = 1; i < 10; i++) {
        string file_name = folder + file_header + to_string(i) + ".jpg";
        Mat bgrImage = imread(file_name);
        ObjectDetection od;
        od.Calibrate(bgrImage);
    }
    TicTacToe game;
    std::cout << "Welcome to Tic Tac Toe!\n";

    while (game.getMoves() < 9) {
        game.displayBoard();
        std::string command;

        std::cout << "Player " << game.getCurrentPlayer()
                  << ", enter your move (e.g., A1) or enter Q to quit: ";
        std::getline(std::cin, command);

        if (command.length() == 1 && toupper(command[0]) == 'Q') {
            std::cout << "Good Bye!";
            return 0;
        }

        if (command.length() != 2 || !isalpha(command[0]) ||
            !isdigit(command[1]) ||
            !game.isValidMove(toupper(command[0]) - 'A', command[1] - '0')) {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }
        int row = toupper(command[0]) - 'A';
        int col = command[1] - '1';
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
