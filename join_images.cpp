#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "join_images_helper.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat millie_image(imread("resources/Millie_Brady.jpg"));
    Mat cards_image(imread("resources/cards.jpg"));

    Mat matrices_a[2] = { cards_image, millie_image };
    Mat horizontal_stack(hstack(matrices_a, 2));

    Mat matrices_b[2] = { horizontal_stack, horizontal_stack };
    Mat vertical_stack(vstack(matrices_b, 2));

    imshow("Output", vertical_stack);
    if (waitKey(0) == 'w')
        exit(1);
}