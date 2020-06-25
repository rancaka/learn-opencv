#include <opencv2/core.hpp>
#include "join_images_helper.hpp"
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat hstack(Mat * matrices, int arrayCount)
{
    Mat output;

    for (int i = 0; i < arrayCount; i ++)
    {
        Mat m = matrices[i];
        if (m.channels() == CV_8U || m.channels() == CV_8S)
            cvtColor(m, m, COLOR_GRAY2BGR);

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
        if (m.channels() == CV_8U || m.channels() == CV_8S)
            cvtColor(m, m, COLOR_GRAY2BGR);

        if (output.cols > m.cols)
        {
            if (m.rows == 0)
                continue;

            Mat add = Mat::zeros(Size(output.cols-m.cols, m.rows), CV_8UC3);
            hconcat(m, add, m);
        } else if (m.cols > output.cols)
        {
            if (output.rows == 0)
            {
                output = m;
                continue;
            }
            Mat add = Mat::zeros(Size(m.cols-output.cols, output.rows), CV_8UC3);
            hconcat(output, add, output);
        }

        vconcat(output, m, output);
    }

    return output;
}