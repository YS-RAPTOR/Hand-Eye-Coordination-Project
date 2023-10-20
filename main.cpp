#include "ObjectDetection.h"
#include "RobotControls.h"
#include "TicTacToe.h"
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    Mat frame;
    VideoCapture cap(0);

    TicTacToe game;
    RobotControls rc(argc, argv);
    ObjectDetection od;
    cap >> frame;
    od.Calibrate(frame);

    system("cls");
    while (true) {
        std::cout << "Welcome to Tic Tac Toe!\n";
        game.DisplayBoard();
        std::string command;

        std::cout << "Player " << game.GetCurrentPlayer()
                  << ", enter your move (e.g., A1) or enter Q to quit: ";
        std::getline(std::cin, command);

        if (command.length() == 1 && toupper(command[0]) == 'Q') {
            system("cls");
            std::cout << "Good Bye!";
            break;
        }

        if (command.length() != 2 ||
            !game.IsValidMove(toupper(command[0]) - 'A', command[1] - '1')) {

            system("cls");
            std::cout << "Invalid move. Try again.\n";
            continue;
        }
        int row = toupper(command[0]) - 'A';
        int col = command[1] - '1';
        game.MakeMove(row, col);

        // Capture the frame and get the player objects
        cap >> frame;
        PlayerObjects inputs = od.GetPlayerObjectsInInputLocation(frame);

        auto x = get<0>(inputs);
        auto o = get<1>(inputs);

        if (x.size() + o.size() == od.InputLocations - game.GetMoves() - 1) {
            cerr << "Error: Operation Failed. Missing Objects." << endl;
            exit(-1);
        }

        if (game.GetCurrentPlayer() == 'X') {
            rc.PerformMove(row, col, x);
        } else {
            rc.PerformMove(row, col, o);
        }

        auto board = od.GetBoard(frame);
        if (!game.CheckEqual(board)) {
            cerr << "Error: Operation Failed. Incorrect Objects." << endl;
            exit(-1);
        }

        if (game.CheckWin(game.GetCurrentPlayer())) {
            system("cls");
            game.DisplayBoard();
            std::cout << "Player " << game.GetCurrentPlayer() << " wins!\n";

            break;
        }

        game.SwitchPlayer();

        if (game.GetMoves() == 9) {
            system("cls");
            game.DisplayBoard();
            std::cout << "It's a draw!\n";
            break;
        }
        system("cls");
    }
    return 0;
}
