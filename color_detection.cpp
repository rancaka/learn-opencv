#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <iostream>
#include "join_images_helper.hpp"

using namespace std;
using namespace cv;

int main()
{
    namedWindow("Jonas", WINDOW_AUTOSIZE);

    int hue_min = 0;
    int hue_max = 79;
    int sat_min = 75;
    int sat_max = 255;
    int val_min = 30;
    int val_max = 255;

    createTrackbar("Hue Min", "Jonas", &hue_min, 179, nullptr);
    createTrackbar("Hue Max", "Jonas", &hue_max, 179, nullptr);
    createTrackbar("Sat Min", "Jonas", &sat_min, 255, nullptr);
    createTrackbar("Sat Max", "Jonas", &sat_max, 255, nullptr);
    createTrackbar("Val Min", "Jonas", &val_min, 255, nullptr);
    createTrackbar("Val Max", "Jonas", &val_max, 255, nullptr);

    Mat jonas(imread("resources/jonas_dark_netflix.jpg"));
    resize(jonas, jonas, Size(jonas.cols * (0.35), jonas.rows * (0.35)));
    Mat jonas_hsv;
    cvtColor(jonas, jonas_hsv, COLOR_BGR2HSV);

    while (true)
    {
        Mat jonas_mask, jonas_coat;
        
        vector<int> lower = {hue_min, sat_min, val_min};
        vector<int> upper = {hue_max, sat_max, val_max};
        
        inRange(jonas_hsv, lower, upper, jonas_mask);
        bitwise_and(jonas, jonas, jonas_coat, jonas_mask);
        
        Mat upper_horizontal(hstack({ jonas, jonas_hsv }));
        Mat lower_horizontal(hstack({ jonas_mask, jonas_coat }));
        Mat all(vstack({ upper_horizontal, lower_horizontal }));

        imshow("Jonas", all);
        cout << hue_min << " " << hue_max << " "   << sat_min << " " << sat_max << " " << val_min << " " << val_max << endl;
        if (waitKey(1) == 'w')
            exit(1);
    }
}

// 0 79 75 255 30 255