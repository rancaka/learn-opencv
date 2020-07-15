#include <string>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    string imgPath = samples::findFile("resources/Millie_Brady.jpg");
    Mat img(imread(imgPath));
    imshow("Image", img);

    if (waitKey(0) == 'w')
        exit(0);
}