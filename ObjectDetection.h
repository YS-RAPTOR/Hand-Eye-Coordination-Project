#pragma once

#include "opencv2/core.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace cv;
using namespace std;

// First vector is X, second is O
typedef tuple<vector<int>, vector<int>> PlayerObjects;

class ObjectDetection {
  public:
    // Configs
    static const int InputLocations = 10;
    static const int OutputLocations = 9;
    static const int NUM_COLORS = 5;
    static const Scalar colourBounds[NUM_COLORS][2];
    static const string colourNames[NUM_COLORS];
    static const int PlayerX[2];
    static const int PlayerO[2];
    static const int YLocation2Index[5];
    // Functions
    array<Mat, NUM_COLORS> GetMasks(Mat &frame);

    Rect InputObjects[InputLocations];
    Rect OutputObjects[OutputLocations];

    PlayerObjects GetPlayerObjectsInInputLocation(Mat &frame);
    vector<vector<char>> GetBoard(Mat &frame);
    void Calibrate(Mat &frame);
};
