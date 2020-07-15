#include <opencv2/highgui.hpp>
#include <opencv2/face/facerec.hpp>
#include <opencv2/imgproc.hpp>
#include "2_join_images_helper.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    CascadeClassifier faceCascade("resources/haarcascade_frontalface_default.xml");
    CascadeClassifier eyeCascade("resources/haarcascade_eye.xml");
    VideoCapture vCapture(1);

    Mat originalFrame;
    Mat grayFrame;
    while (true) {
        vCapture.read(originalFrame);
        flip(originalFrame, originalFrame, 1);
        cvtColor(originalFrame, grayFrame, COLOR_BGR2GRAY);

        vector<Rect> faceAreas;
        faceCascade.detectMultiScale(grayFrame, faceAreas, 1.05, 3, 0, Size(100, 100));

        Mat finalFrame = originalFrame;
        Mat blackFrame = Mat::zeros(Size(originalFrame.cols, originalFrame.rows), CV_8UC3);

        for (auto &faceArea : faceAreas) {
            
            float aspectRatio = float(originalFrame.cols)/float(originalFrame.rows);
            float width = faceArea.height * aspectRatio;
            float height = faceArea.height;
            float x = min(max(faceArea.x - ((width - faceArea.width)/2), float(3)), (originalFrame.cols - width - float(3)));
            float y = faceArea.y;
            Rect roi(x, y, width, height);
            finalFrame = Mat(originalFrame, roi);
            rectangle(blackFrame, roi, Scalar(150, 0, 0), 3);
            x = faceArea.x + (faceArea.width/2);
            y = faceArea.y + (faceArea.height/2);
            circle(blackFrame, Point(x, y), faceArea.height/2, Scalar(0, 150, 0), 2);
            
            roi.height = roi.height/2; // eyes supposed to be in upper half of the face
            Mat face(grayFrame, roi);
            vector<Rect> eyesArea;
            eyeCascade.detectMultiScale(face, eyesArea);
            for (const auto &eyeArea : eyesArea) {
                int x = (roi.x + eyeArea.x) + (eyeArea.width/2);
                int y = (roi.y + eyeArea.y) + (eyeArea.height/2);
                circle(blackFrame, Point(x, y), eyeArea.width, Scalar(0, 0, 150), 1);
            }
            
            resize(finalFrame, finalFrame, Size(originalFrame.cols, originalFrame.rows));
        }

        imshow("Camera", vstack({ finalFrame, blackFrame }));
        if (waitKey(1) == 'w')
            exit(0);
    }
}