#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <iostream>
#include "2_join_images_helper.hpp"

using namespace std;
using namespace cv;

int main()
{
    namedWindow("liverpool", WINDOW_AUTOSIZE);

    int hue_min = 164;
    int hue_max = 179;
    int sat_min = 168;
    int sat_max = 255;
    int val_min = 0;
    int val_max = 255;

    createTrackbar("Hue Min", "liverpool", &hue_min, 179, nullptr);
    createTrackbar("Hue Max", "liverpool", &hue_max, 179, nullptr);
    createTrackbar("Sat Min", "liverpool", &sat_min, 255, nullptr);
    createTrackbar("Sat Max", "liverpool", &sat_max, 255, nullptr);
    createTrackbar("Val Min", "liverpool", &val_min, 255, nullptr);
    createTrackbar("Val Max", "liverpool", &val_max, 255, nullptr);

    Mat liverpool(imread("resources/liverpool.png"));
    resize(liverpool, liverpool, Size(liverpool.cols * (0.35), liverpool.rows * (0.35)));
    Mat liverpool_hsv;
    cvtColor(liverpool, liverpool_hsv, COLOR_BGR2HSV);

    while (true)
    {
        Mat liverpool_mask, liverpool_coat;
        
        vector<int> lower = {hue_min, sat_min, val_min};
        vector<int> upper = {hue_max, sat_max, val_max};
        
        inRange(liverpool_hsv, lower, upper, liverpool_mask);
        bitwise_and(liverpool, liverpool, liverpool_coat, liverpool_mask);
        
        Mat upper_horizontal(hstack({ liverpool, liverpool_hsv }));
        Mat lower_horizontal(hstack({ liverpool_mask, liverpool_coat }));
        Mat all(vstack({ upper_horizontal, lower_horizontal }));

        imshow("liverpool", all);
        cout << hue_min << " " << hue_max << " "   << sat_min << " " << sat_max << " " << val_min << " " << val_max << endl;
        if (waitKey(1) == 'w')
            exit(1);
    }
}