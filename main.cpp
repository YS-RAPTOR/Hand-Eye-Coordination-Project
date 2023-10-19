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

#include "ObjectDetection.h"

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
    string folder = "../../Pictures/";
    string file_header = "Im";
    cout << Mat();
    for (int i = 1; i < 10; i++) {
        string file_name = folder + file_header + to_string(i) + ".jpg";
        Mat bgrImage = imread(file_name);
        ObjectDetection od;
        od.Calibrate(bgrImage);
    }

    return 0;
}
