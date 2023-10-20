#include "RobotControls.h"

const int RobotControls::Delays[10] = {
    4500, // 1
    4500, // 2
    7500, // 3
    4500, // 4
    4500, // 5
    4500, // 6
    4500, // 7
    7500, // 8
    4500, // 9
    4500, // 10
};

RobotControls::RobotControls(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, " Port use\n");
        exit(1);
    }

    err = sp_get_port_by_name(argv[1], &port);
    if (err == SP_OK)
        err = sp_open(port, SP_MODE_WRITE);
    if (err != SP_OK) {
        fprintf(stderr, " Can't open port %s\n", argv[1]);
        exit(2);
    }
    sp_set_baudrate(port, BAUD_RATE);
    sp_set_bits(port, 8);
}

RobotControls::~RobotControls() { sp_close(port); }

int RobotControls::PerformMove(int row, int col, vector<int> pickupLocations) {
    int startPos = pickupLocations.front();
    int endPos = row * 3 + col + 11;

    PerformCommand(startPos, true);
    Wait(Delays[startPos + 1]);

    PerformCommand(endPos, false);
    Wait(4500);

    PerformCommand(0, false);
    Wait(4500);

    PerformCommand(0, false, false);
    Wait(4500);
    return SP_OK;
}

int RobotControls::PerformCommand(int pos, bool closeGripper, bool start) {
    char cmd = pos;
    pos |= start << 5;
    pos |= closeGripper << 6;
    sp_blocking_write(port, &pos, 1, 100);
    return SP_OK;
}

void RobotControls::Wait(int ms) {
    auto target =
        std::chrono::system_clock::now() + std::chrono::milliseconds(ms);
    while (std::chrono::system_clock::now() < target) {
    }
}
