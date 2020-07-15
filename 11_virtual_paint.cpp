#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face/facerec.hpp>
#include <iostream>
#include "2_join_images_helper.hpp"

using namespace std;
using namespace cv;

struct MyColor {
    string name;
    Scalar minRange, maxRange, actualColor;
    MyColor(string name, Scalar minRange, Scalar maxRange, Scalar actualColor): minRange{minRange}, maxRange{maxRange}, actualColor{actualColor} {

    }
};

vector<MyColor> colors = {
    MyColor("Blue", Scalar(39, 0, 0), Scalar(255, 255, 38), Scalar(255, 0, 0)),
    MyColor("Red", Scalar(0, 0, 87), Scalar(65, 52, 255), Scalar(0, 0, 255))
};

struct Dot {
    Point point;
    Scalar actualColor;
    Dot(Point point, Scalar actualColor): point{point}, actualColor{actualColor} {

    }
};

void getContours(InputArray image, Point &point) {

    vector<vector<Point>> contours;
    findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (int idx = 0; idx < contours.size(); ++idx) {
        auto con = contours[idx];
        double area = contourArea(con);
        if (area > 800) {
            
            auto arcl = arcLength(con, true);
            vector<Point> approx;
            approxPolyDP(con, approx, 0.03*arcl, true);

            auto rect = boundingRect(approx);
            point.x = rect.x + rect.width/4;
            point.y = rect.y;
        }
    }
}


int main() {
    VideoCapture vCapture(1);

    Mat frame;
    vector<Dot> dots;
    while (true) {
        vCapture.read(frame);
        flip(frame, frame, 1);

        vector<Mat> masks;
        for (const auto &color : colors) {
            Mat mask;
            Point point;
            inRange(frame, color.minRange, color.maxRange, mask);

            getContours(mask, point);
            dots.push_back(Dot(point, color.actualColor));
            masks.push_back(mask);
        }

        for (const auto &dot: dots) {
            circle(frame, dot.point, 10, dot.actualColor, -1, FILLED);
        }

        Mat top(hstack({ frame, masks[0] }));
        Mat bottom(hstack({ masks[1] }));

        imshow("Virtual Paint", vstack({ top, bottom }));
        if (waitKey(1) == 'w') {
            exit(0);
        }
    }
}