#include "ObjectDetection.h"
#include "RobotControls.h"
#include "TicTacToe.h"
#include <opencv2/imgcodecs.hpp>
#include <thread>

using namespace cv;
using namespace std;

Mat frame;
mutex frameLock;
bool runStream = true;

void DisplayVideoStream(VideoCapture cap) {
    string windowsName = "Video Stream";
    namedWindow(windowsName);
    while (runStream) {
        {
            std::lock_guard<std::mutex> lock(frameLock);
            cap >> frame;
        }

        imshow("Video Stream", frame);
        char key = (char)waitKey(25);
        RobotControls::Wait(25);
    }
}

int main(int argc, char *argv[]) {
    VideoCapture cap(0);
    Mat processedFrame;

    if (!cap.isOpened()) {
        cout << "cannot open camera";
    }

    TicTacToe game;
    ObjectDetection od;

    thread videoStream(DisplayVideoStream, cap);
    RobotControls::Wait(5000);
    {
        std::lock_guard<std::mutex> lock(frameLock);
        processedFrame = frame.clone();
    }
    od.Calibrate(processedFrame);
    RobotControls rc(argc, argv);
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
            std::cout << "Good Bye!\n";
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
        {
            std::lock_guard<std::mutex> lock(frameLock);
            processedFrame = frame.clone();
        }
        PlayerObjects inputs =
            od.GetPlayerObjectsInInputLocation(processedFrame);

        auto x = get<0>(inputs);
        auto o = get<1>(inputs);

        if (game.GetCurrentPlayer() == 'X') {
            rc.PerformMove(row, col, x);
        } else {
            rc.PerformMove(row, col, o);
        }

        {
            std::lock_guard<std::mutex> lock(frameLock);
            processedFrame = frame.clone();
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
    runStream = false;
    videoStream.join();
    return 0;
}
