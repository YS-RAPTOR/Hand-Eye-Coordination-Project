#include "ObjectDetection.h"
#include "opencv2/highgui.hpp"

const Scalar ObjectDetection::colourBounds[NUM_COLORS][2] = {
    {Scalar(165, 75, 25), Scalar(15, 255, 255)}, // Red
    {Scalar(40, 75, 25), Scalar(80, 255, 255)},  // Green
    {Scalar(90, 75, 25), Scalar(140, 255, 255)}, // Blue
    {Scalar(22, 75, 25), Scalar(40, 255, 255)},  // Yellow
    {Scalar(0, 0, 0), Scalar(180, 255, 50)}      // Black
};

const string ObjectDetection::colourNames[NUM_COLORS] = {"Red", "Green", "Blue",
                                                         "Yellow", "Black"};

const int ObjectDetection::PlayerX[2] = {0, 3};
const int ObjectDetection::PlayerO[2] = {1, 2};

void ObjectDetection::Calibrate(Mat &frame) {
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    Mat mask;
    for (int i = 0; i < NUM_COLORS; i++) {

        Mat tempMask;
        if (colourBounds[i][0][0] > colourBounds[i][1][0]) {
            inRange(hsv, colourBounds[i][0],
                    Scalar(180, colourBounds[i][1][1], colourBounds[i][1][2]),
                    tempMask);
            if (i == 0) {
                mask = tempMask.clone();
            }
            bitwise_or(tempMask, mask, mask);
            inRange(hsv,
                    Scalar(0, colourBounds[i][0][1], colourBounds[i][0][2]),
                    colourBounds[i][1], tempMask);
            bitwise_or(tempMask, mask, mask);
            continue;
        }

        inRange(hsv, colourBounds[i][0], colourBounds[i][1], tempMask);
        bitwise_or(tempMask, mask, mask);
    }
    erode(mask, mask, Mat(), Point(-1, -1), 3);
    dilate(mask, mask, Mat(), Point(-1, -1), 3);
    imshow("Calibration", mask);
    waitKey(0);
}

PlayerObjects ObjectDetection::GetPlayerObjectsInInputLocations(Mat &frame) {
    // TODO
    vector<int> x;
    vector<int> o;
    return PlayerObjects(x, o);
}

PlayerObjects ObjectDetection::GetPlayerObjectsInOutputLocations(Mat &frame) {
    // TODO
    vector<int> x;
    vector<int> o;
    return PlayerObjects(x, o);
}
