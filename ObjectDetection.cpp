#include "ObjectDetection.h"

const Scalar ObjectDetection::colourBounds[NUM_COLORS][2] = {
    {Scalar(165, 75, 25), Scalar(15, 255, 255)}, // Red
    {Scalar(40, 75, 25), Scalar(80, 255, 255)},  // Green
    {Scalar(90, 75, 25), Scalar(140, 255, 255)}, // Blue
    {Scalar(22, 75, 25), Scalar(40, 255, 255)}   // Yellow
};

const string ObjectDetection::colourNames[NUM_COLORS] = {"Red", "Green", "Blue",
                                                         "Yellow"};

const int ObjectDetection::PlayerX[2] = {0, 3};
const int ObjectDetection::PlayerO[2] = {1, 2};
