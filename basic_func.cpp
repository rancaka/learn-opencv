#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "join_images_helper.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat img(imread("./resources/Millie_Brady.jpg"));
    Mat img_cropped(img.clone(), Rect(1500, 500, 1000, 1000));
    
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);

    Mat img_blur;
    GaussianBlur(img, img_blur, Size(29, 29), 29, 29);

    Mat img_canny;
    // resize image to get better edges
    resize(img_gray, img_canny, Size(img_gray.cols/4, img_gray.rows/4));
    Canny(img_canny, img_canny, 150, 200);

    Mat img_dialation;
    Mat kernel(5, 5, CV_8U, Scalar(1));
    dilate(img_canny, img_dialation, kernel);

    Mat img_eroded;
    erode(img_dialation, img_eroded, kernel);

    // titles
    putText(img, "Original", Point(img.cols/2, img.rows/2), FONT_HERSHEY_COMPLEX, 8, Scalar(213, 200, 14), 4);
    putText(img_cropped, "Cropped", Point(0, 100), FONT_HERSHEY_COMPLEX, 4, Scalar(213, 200, 14), 4);
    putText(img_gray, "Grayscale", Point(img_gray.cols/2, img_gray.rows/2), FONT_HERSHEY_COMPLEX, 8, Scalar(213, 200, 14), 4);
    putText(img_blur, "Blur", Point(img_blur.cols/2, img_blur.rows/2), FONT_HERSHEY_COMPLEX, 8, Scalar(213, 200, 14), 4);

    putText(img_canny, "Canny", Point(img_canny.cols/2, img_canny.rows/2), FONT_HERSHEY_COMPLEX, 2, Scalar(213, 200, 14), 4);
    putText(img_dialation, "Dialation", Point(img_dialation.cols/2, img_dialation.rows/2), FONT_HERSHEY_COMPLEX, 2, Scalar(213, 200, 14), 4);
    putText(img_eroded, "Eroded", Point(img_eroded.cols/2, img_eroded.rows/2), FONT_HERSHEY_COMPLEX, 2, Scalar(213, 200, 14), 4);
    
    imshow("Original Images", hstack({ img, img_gray, img_blur }));
    imshow("Cropped Image", img_cropped);
    imshow("Edges Images", hstack({ img_canny, img_dialation, img_eroded }));

    if (waitKey(0) == 'w')
        exit(0);
}