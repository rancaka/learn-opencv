#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat hstack(Mat * matrices, int arrayCount)
{
    Mat output;

    for (int i = 0; i < arrayCount; i ++)
    {
        Mat m = matrices[i];
        if (output.rows > m.rows)
        {
            if (m.cols == 0)
                continue;

            Mat add = Mat::zeros(Size(m.cols, output.rows-m.rows), CV_8UC3);
            vconcat(m, add, m);
        } else if (m.rows > output.rows)
        {
            if (output.cols == 0)
            {
                output = m;
                continue;
            }
            Mat add = Mat::zeros(Size(output.cols, m.rows-output.rows), CV_8UC3);
            vconcat(output, add, output);
        }

        hconcat(output, m, output);
    }

    return output;
}

Mat vstack(Mat * matrices, int arrayCount)
{
    Mat output;

    for (int i = 0; i < arrayCount; i ++)
    {
        Mat m = matrices[i];
        if (output.cols > m.cols)
        {
            if (m.rows == 0)
                continue;

            Mat add = Mat::zeros(Size(m.rows, output.cols-m.cols), CV_8UC3);
            hconcat(m, add, m);
        } else if (m.cols > output.cols)
        {
            if (output.rows == 0)
            {
                output = m;
                continue;
            }
            Mat add = Mat::zeros(Size(output.rows, m.cols-output.cols), CV_8UC3);
            hconcat(output, add, output);
        }

        vconcat(output, m, output);
    }

    return output;
}

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