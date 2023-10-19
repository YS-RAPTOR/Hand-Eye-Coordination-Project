#include "ObjectDetection.h"

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
    Mat mask[NUM_COLORS];
    Mat morph = getStructuringElement(MORPH_RECT, Size(7, 7));
    for (int i = 0; i < NUM_COLORS; i++) {
        // Gets the Mask
        if (colourBounds[i][0][0] > colourBounds[i][1][0]) {
            Mat tempMask;
            inRange(hsv, colourBounds[i][0],
                    Scalar(180, colourBounds[i][1][1], colourBounds[i][1][2]),
                    tempMask);
            inRange(hsv,
                    Scalar(0, colourBounds[i][0][1], colourBounds[i][0][2]),
                    colourBounds[i][1], mask[i]);
            bitwise_or(tempMask, mask[i], mask[i]);
        } else {
            inRange(hsv, colourBounds[i][0], colourBounds[i][1], mask[i]);
        }

        // Erode and Dilate to remove noise

        erode(mask[i], mask[i], morph);
        dilate(mask[i], mask[i], morph);
        imshow("Calibration", mask[i]);
        waitKey(0);
    }
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
