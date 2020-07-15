#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "2_join_images_helper.hpp"

using namespace std;
using namespace cv;

void get_contours(InputArray image, InputOutputArray contour_shapes);

int main()
{
    Mat original_shapes(imread("resources/shapes.jpg"));
    Mat canny_shapes;
    
    cvtColor(original_shapes, canny_shapes, COLOR_BGR2GRAY);
    Canny(canny_shapes, canny_shapes, 20, 20);

    Mat kernel(2, 2, CV_8U, Scalar(1));
    dilate(canny_shapes, canny_shapes, kernel);

    Mat img_eroded;
    erode(canny_shapes, canny_shapes, kernel);

    Mat contour_shapes;
    original_shapes.copyTo(contour_shapes);
    get_contours(canny_shapes, contour_shapes);

    Mat shapes(hstack({ original_shapes, canny_shapes, contour_shapes}));
    imshow("shapes", shapes);
    if (waitKey(0) == 'w')
        exit(0);
}

void get_contours(InputArray image, InputOutputArray contour_shapes) {

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (int idx = 0; idx < contours.size(); ++idx) {
        auto con = contours[idx];
        double area = contourArea(con);
        if (area > 50) {
            
            Scalar color((uchar)rand(), (uchar)rand(), (uchar)rand());
            drawContours(contour_shapes, contours, idx, color, 2);
            auto arcl = arcLength(con, true);

            vector<Point> approx;
            approxPolyDP(con, approx, 0.03*arcl, true);

            auto rect = boundingRect(approx);
            putText(contour_shapes, to_string(approx.size()), Point(rect.x, rect.y+rect.height+12), FONT_HERSHEY_PLAIN, 1, color, 1);
        }
    }
}