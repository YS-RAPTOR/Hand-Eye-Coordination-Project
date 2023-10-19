#include "ObjectDetection.h"
#include "RobotControls.h"
#include "TicTacToe.h"

using namespace cv;
using namespace std;

/* string folder = "../../Pictures/"; */
/* string file_header = "Im"; */
/* cout << Mat(); */
/* for (int i = 1; i < 10; i++) { */
/*     string file_name = folder + file_header + to_string(i) + ".jpg"; */
/*     Mat bgrImage = imread(file_name); */
/*     ObjectDetection od; */
/*     od.Calibrate(bgrImage); */
/* } */
int main(int argc, char *argv[]) {
    // HACK
    // For debugging sake, we will just have an array of 10 positions where a
    // piece will be removed from the front after each move.
    vector<int> pickupLocations = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TicTacToe game;
    RobotControls rc(argc, argv);

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
        rc.PerformMove(row, col, pickupLocations);

        // HACK
        // Removes the front element from the vector
        pickupLocations.erase(pickupLocations.begin());

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
