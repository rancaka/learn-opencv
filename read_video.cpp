#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

int main()
{
    // read video from webcap
    VideoCapture cap_webcam(0);
    cap_webcam.set(CAP_PROP_FRAME_WIDTH, 620);
    cap_webcam.set(CAP_PROP_FRAME_HEIGHT, 480);

    VideoCapture cap_resource("./resources/highway.mp4");

    Mat webcam_frame;
    Mat resource_frame;
    while (true)
    {
        cap_webcam.read(webcam_frame);
        imshow("Webcam", webcam_frame);

        cap_resource.read(resource_frame);
        imshow("Video", resource_frame);

        if (waitKey(1) == 'w')
            exit(0);
    }
}