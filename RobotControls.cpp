#include "RobotControls.h"
#include "libserialport.h"
#include <chrono>

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

    int err = PerformCommand(startPos, true);
    if (err != SP_OK)
        return err;

    Pause(2000);

    err = PerformCommand(endPos, false);
    if (err != SP_OK)
        return err;

    Pause(2000);

    err = PerformCommand(0, false);
    if (err != SP_OK)
        return err;

    Pause(500);

    err = PerformCommand(0, false, false);
    if (err != SP_OK)
        return err;

    return SP_OK;
}

int RobotControls::PerformCommand(int pos, bool closeGripper, bool start) {
    char cmd = pos;
    pos |= start << 5;
    pos |= closeGripper << 6;
    return SP_OK;
}

void RobotControls::Pause(int ms) {
    auto target =
        std::chrono::system_clock::now() + std::chrono::milliseconds(ms);
    while (std::chrono::system_clock::now() < target) {
    }
}
