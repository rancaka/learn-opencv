#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face/facerec.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat img(imread("resources/ios_team.jpg"));
    Mat grayImg;

    cvtColor(img, grayImg, COLOR_BGR2GRAY);
    
    CascadeClassifier cascade("resources/haarcascade_frontalface_default.xml");

    vector<Rect> faceAreas;
    cascade.detectMultiScale(grayImg, faceAreas, 1.1, 4, 0, Size(100, 100));

    int counter = 0;
    for (const auto &faceArea : faceAreas) {
        Mat face(img(faceArea));
        imwrite("detected_faces/" + to_string(counter) + ".jpg", face);
        rectangle(img, faceArea, Scalar(255, 0, 0), 8);
        counter++;
    }

    imshow("Image", img);
    if (waitKey(0) == 'w') {
        exit(0);
    }
}