#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define w 1000
using namespace cv;

int main()
{
    Mat background = Mat::zeros(Size(w, w), CV_8UC3);

    line(background, Point(0, 0), Point(background.rows/2, background.cols/2), Scalar(0, 0, 255), 2);
    rectangle(background, Rect(background.rows-150, 0, 150, 200), Scalar(255), 3);
    ellipse(background, Point(w/2, w/2), Size(w/4, w/16), 90, 0, 360, Scalar(255, 0, 0), 2);
    circle(background, Point(background.rows-50, background.cols-50), 50, Scalar(255, 255, 0), 2);
    putText(background, "Adityo Rancaka", Point(0, background.cols-26), FONT_HERSHEY_COMPLEX, 2, Scalar(213, 200, 14), 2);

    imshow("Image", background);
    if (waitKey(0) == 'w')
        exit(0);
}