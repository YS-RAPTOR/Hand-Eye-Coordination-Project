#include "ObjectDetection.h"
#include "RobotControls.h"
#include "TicTacToe.h"
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    string folder = "../../Pictures/";
    string file_header = "Im";
    string file_name = folder + file_header + to_string(10) + ".jpg";
    Mat bgrImage = imread(file_name);
    ObjectDetection od;
    od.Calibrate(bgrImage);

    PlayerObjects inputs = od.GetPlayerObjectsInLocation(bgrImage, true);
    auto x = get<0>(inputs);
    auto o = get<1>(inputs);

    for (auto &i : x) {
        cout << "X: " << i << endl;
    }
    for (auto &i : o) {
        cout << "O: " << i << endl;
    }

    PlayerObjects outputs = od.GetPlayerObjectsInLocation(bgrImage, false);
    auto x1 = get<0>(outputs);
    auto o1 = get<1>(outputs);

    for (auto &i : x1) {
        cout << "X: " << i << endl;
    }
    for (auto &i : o1) {
        cout << "O: " << i << endl;
    }
    return 0;

    Mat frame;

    TicTacToe game;
    RobotControls rc(argc, argv);
    ObjectDetection od;
    od.Calibrate(frame);
    system("cls");
    while (true) {
        std::cout << "Welcome to Tic Tac Toe!\n";
        game.displayBoard();
        std::string command;

        std::cout << "Player " << game.getCurrentPlayer()
                  << ", enter your move (e.g., A1) or enter Q to quit: ";
        std::getline(std::cin, command);

        if (command.length() == 1 && toupper(command[0]) == 'Q') {
            system("cls");
            std::cout << "Good Bye!";
            break;
        }

        if (command.length() != 2 ||
            !game.isValidMove(toupper(command[0]) - 'A', command[1] - '1')) {

            system("cls");
            std::cout << "Invalid move. Try again.\n";
            continue;
        }
        int row = toupper(command[0]) - 'A';
        int col = command[1] - '1';
        game.makeMove(row, col);
        PlayerObjects inputs = od.GetPlayerObjectsInLocation(frame, true);
        if (game.getCurrentPlayer() == 'X')
            rc.PerformMove(row, col, get<0>(inputs));
        else
            rc.PerformMove(row, col, get<1>(inputs));

        if (game.checkWin(game.getCurrentPlayer())) {
            system("cls");
            game.displayBoard();
            std::cout << "Player " << game.getCurrentPlayer() << " wins!\n";

            break;
        }

        game.switchPlayer();

        if (game.getMoves() == 9) {
            system("cls");
            game.displayBoard();
            std::cout << "It's a draw!\n";
            break;
        }
        system("cls");
    }
    return 0;
}
