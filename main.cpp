#include "opencv2/core/matx.hpp"
#include <intrin0.inl.h>
#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD 9600

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <vector>

using namespace cv;
using namespace std;

#define NUM_COLORS 4

const Scalar colourBounds[NUM_COLORS][2] = {
    {Scalar(165, 75, 25), Scalar(15, 255, 255)}, // Red
    {Scalar(40, 75, 25), Scalar(80, 255, 255)},  // Green
    {Scalar(90, 75, 25), Scalar(140, 255, 255)}, // Blue
    {Scalar(22, 75, 25), Scalar(40, 255, 255)}   // Yellow
};

const string colourNames[NUM_COLORS] = {"Red", "Green", "Blue", "Yellow"};

int main() {
    Mat bgrImage = imread("test.jpg");

    Mat hsvImage;
    cvtColor(bgrImage, hsvImage, COLOR_BGR2HSV);

    Mat masks[NUM_COLORS];
    for (int i = 0; i < NUM_COLORS; i++) {
        if (colourBounds[i][0][0] > colourBounds[i][1][0]) {
            Mat tempMask;
            inRange(hsvImage, colourBounds[i][0],
                    Scalar(180, colourBounds[i][1][1], colourBounds[i][1][2]),
                    tempMask);
            inRange(hsvImage,
                    Scalar(0, colourBounds[i][0][1], colourBounds[i][0][2]),
                    colourBounds[i][1], masks[i]);
            bitwise_or(tempMask, masks[i], masks[i]);
            continue;
        }
        inRange(hsvImage, colourBounds[i][0], colourBounds[i][1], masks[i]);
    }

    Mat segmentedImages[NUM_COLORS];
    for (int i = 0; i < NUM_COLORS; i++) {
        bitwise_and(bgrImage, bgrImage, segmentedImages[i], masks[i]);
    }

    for (int i = 0; i < NUM_COLORS; i++) {
        imshow("Segmented " + colourNames[i], segmentedImages[i]);
    }

    waitKey(0);

    return 0;
}
