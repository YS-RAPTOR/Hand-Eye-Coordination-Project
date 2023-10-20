#include "ObjectDetection.h"
#include <iostream>

const Scalar ObjectDetection::colourBounds[NUM_COLORS][2] = {
    {Scalar(165, 75, 25), Scalar(15, 255, 255)}, // Red
    {Scalar(45, 75, 25), Scalar(80, 255, 255)},  // Green
    {Scalar(90, 75, 25), Scalar(140, 255, 255)}, // Blue
    {Scalar(22, 75, 25), Scalar(45, 255, 255)},  // Yellow
    {Scalar(0, 0, 0), Scalar(180, 255, 55)}      // Black
};

const string ObjectDetection::colourNames[NUM_COLORS] = {"Red", "Green", "Blue",
                                                         "Yellow", "Black"};

const int ObjectDetection::PlayerX[2] = {0, 3};
const int ObjectDetection::PlayerO[2] = {1, 2};

const int ObjectDetection::YLocation2Index[5] = {0, 3, 1, 4, 2};

array<Mat, ObjectDetection::NUM_COLORS> ObjectDetection::GetMasks(Mat &frame) {
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    array<Mat, NUM_COLORS> mask;
    Mat morph = getStructuringElement(MORPH_RECT, Size(5, 5));
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

        // Morphological Operations to remove noise
        morphologyEx(mask[i], mask[i], MORPH_CLOSE, morph);
        morphologyEx(mask[i], mask[i], MORPH_OPEN, morph);
    }
    return mask;
}

void ObjectDetection::Calibrate(Mat &frame) {
    vector<vector<Point>> contours;
    array<Mat, NUM_COLORS> mask = GetMasks(frame);
    vector<vector<Point>> c;
    for (int i = 0; i < NUM_COLORS; i++) {
        // Find contours
        findContours(mask[i], c, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        contours.insert(contours.end(), c.begin(), c.end());
    }

    // Sort contours by area
    sort(contours.begin(), contours.end(),
         [](const vector<Point> &a, const vector<Point> &b) {
             return contourArea(a) > contourArea(b);
         });

    // Only get the top 20 contours
    if (contours.size() > 11) {
        // Print warning message and print int stderror
        cerr << "WARNING: More than 20 objects detected. You can safely ignore "
                "this message if you are sure that all the objects are in frame"
             << endl;
        contours.erase(contours.begin() + 11, contours.end());
    } else if (contours.size() < 11) {
        // Display error message and exit
        cerr << "Error: Less than 11 objects detected. Make Sure that the "
                "objects are in frame and check if all the objects are present"
             << endl;
        exit(-1);
    }

    // Get bounding rectangles
    vector<Rect> boundRect(contours.size());
    for (int i = 0; i < contours.size(); i++) {
        boundRect[i] = boundingRect(contours[i]);
    }

    // Create 9 smaller rectangles for the output locations from the rectangle
    // in index 0 (The largest Rectangle)
    for (int i = 0; i < OutputLocations; i++) {
        this->OutputObjects[i] =
            Rect(boundRect[0].x + boundRect[0].width / 3 * (i % 3),
                 boundRect[0].y + boundRect[0].height / 3 * (i / 3),
                 boundRect[0].width / 3, boundRect[0].height / 3);
    }

    int center = round(boundRect[0].x + boundRect[0].width / 2);
    array<Rect, InputLocations / 2> left;
    array<Rect, InputLocations / 2> right;
    int leftIndex = 0;
    int rightIndex = 0;
    for (int i = 1; i < boundRect.size(); i++) {
        if (boundRect[i].x < center) {
            left[leftIndex++] = boundRect[i];
        } else {
            right[rightIndex++] = boundRect[i];
        }
    }

    // Sort left and right by y
    sort(left.begin(), left.end(),
         [](const Rect &a, const Rect &b) { return a.y < b.y; });
    sort(right.begin(), right.end(),
         [](const Rect &a, const Rect &b) { return a.y < b.y; });

    for (int i = 0; i < InputLocations / 2; i++) {
        this->InputObjects[YLocation2Index[i]] = left[i];
        this->InputObjects[YLocation2Index[i] + InputLocations / 2] = right[i];
    }
}

PlayerObjects ObjectDetection::GetPlayerObjectsInInputLocation(Mat &frame) {
    vector<int> x;
    vector<int> o;

    array<int, NUM_COLORS> colorCount = {0};
    auto mask = GetMasks(frame);
    for (int i = 0; i < InputLocations; i++) {
        colorCount = {0};
        for (int c = 0; c < NUM_COLORS; c++) {
            // Set color count to the number of pixels in the mask at the object
            // Rectangle created in calibration
            colorCount[c] = countNonZero(mask[c](InputObjects[i]));
        }
        // Set the max color as the color of the object and add it to the
        // correct team according to the color
        int maxColor = max_element(colorCount.begin(), colorCount.end()) -
                       colorCount.begin();
        if (maxColor == PlayerX[0] || maxColor == PlayerX[1]) {
            x.push_back(i + 1);
        } else if (maxColor == PlayerO[0] || maxColor == PlayerO[1]) {
            o.push_back(i + 1);
        }
    }

    return PlayerObjects(x, o);
}

vector<vector<char>> ObjectDetection::GetBoard(Mat &frame) {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    array<int, NUM_COLORS> colorCount = {0};
    auto mask = GetMasks(frame);
    for (int i = 0; i < OutputLocations; i++) {
        colorCount = {0};
        for (int c = 0; c < NUM_COLORS; c++) {
            colorCount[c] = countNonZero(mask[c](OutputObjects[i]));
        }
        int maxColor = max_element(colorCount.begin(), colorCount.end()) -
                       colorCount.begin();
        if (maxColor == PlayerX[0] || maxColor == PlayerX[1]) {
            board[i / 3][i % 3] = 'X';
        } else if (maxColor == PlayerO[0] || maxColor == PlayerO[1]) {
            board[i / 3][i % 3] = 'O';
        }
    }
    return board;
}
