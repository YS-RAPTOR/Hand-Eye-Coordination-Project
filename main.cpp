#include <intrin0.inl.h>
#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD 9600

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace cv;
using namespace std;

#define NUM_COLORS 4

int main() {
    Vec3b colors[NUM_COLORS];
    colors[0] = (Vec3b(0, 0, 255));   // Red
    colors[1] = (Vec3b(0, 255, 0));   // Green
    colors[2] = (Vec3b(255, 0, 0));   // Blue
    colors[3] = (Vec3b(0, 255, 255)); // Yellow

    double thresholdDistance = 200;

    // Read image from file
    Mat frame = imread("test.jpg");

    Mat labelledMask = Mat::zeros(frame.size(), CV_8UC1);

    auto operation = [&colors, thresholdDistance, &labelledMask](
                         Vec3b &pixel, const int *position) -> void {
        double minDistance = 1000.0;
        double distance = 0.0;
        for (int i = 0; i < NUM_COLORS; i++) {
            distance = norm(pixel, colors[i], NORM_L2);
            if (distance < minDistance) {
                minDistance = distance;
                if (minDistance < thresholdDistance) {
                    labelledMask.at<uchar>(position[0], position[1]) =
                        (i + 1) * (255 / 5);
                }
            }
        }
    };

    frame.forEach<Vec3b>(operation);
    imwrite("output.jpg", labelledMask);
}
