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

    Mat horizontal_stack(hstack({ cards_image, millie_image }));
    Mat vertical_stack(vstack({ horizontal_stack, horizontal_stack }));

    imshow("Output", vertical_stack);
    if (waitKey(0) == 'w')
        exit(1);
}