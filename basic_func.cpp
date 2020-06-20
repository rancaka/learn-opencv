#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img(imread("./resources/Millie_Brady.jpg"));
    Mat img_cropped(img, Rect(1500, 500, 1000, 1000));
    
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);

    Mat img_blur;
    GaussianBlur(img, img_blur, Size(21, 21), 0);

    Mat img_canny;
    // resize image to get better edges
    resize(img_gray, img_canny, Size(img_gray.cols/4, img_gray.rows/4));
    Canny(img_canny, img_canny, 150, 200);

    Mat img_dialation;
    Mat kernel(5, 5, CV_8U, Scalar(1));
    dilate(img_canny, img_dialation, kernel);

    Mat img_eroded;
    erode(img_dialation, img_eroded, kernel);
    
    imshow("Default Image", img);
    imshow("Cropped Image", img_cropped);
    imshow("Gray Image", img_gray);
    imshow("Blur Image", img_blur);
    imshow("Canny Image", img_canny);
    imshow("Dialation Image", img_dialation);
    imshow("Eroded Image", img_eroded);

    if (waitKey(0) == 'w')
        exit(0);
}