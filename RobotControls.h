#pragma once

#include <chrono>
#include <intrin0.inl.h>
#include <libserialport.h>
#include <vector>

using namespace std;

class RobotControls {
  public:
    RobotControls(int argc, char *argv[]);
    ~RobotControls();
    int PerformMove(int row, int col, vector<int> pickupLocations);
    void Wait(int ms);

  private:
    static const int Delays[10];
    int PerformCommand(int pos, bool closeGripper, bool start = true);
    static const int BAUD_RATE = 9600;
    sp_port *port;
    int err;
    char *portName;
};
