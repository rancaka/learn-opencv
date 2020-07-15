#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat cards_image = imread("resources/cards.jpg");

    vector<Point2f> src = {
        Point2f(369, 136),
        Point2f(495, 165),
        Point2f(270, 295),
        Point2f(415, 335)
    };

    int card_width = 250;
    int card_height = 350;
    vector<Point2f> dst = {
        Point2f(0, 0),
        Point2f(card_width, 0),
        Point2f(0, card_height),
        Point2f(card_width, card_height)
    };

    Mat matrix(getPerspectiveTransform(src, dst));
    Mat family_card;
    warpPerspective(cards_image, family_card, matrix, Size(card_width, card_height));

    line(cards_image, src[0], src[1], Scalar(255, 0, 0), 4);
    line(cards_image, src[0], src[2], Scalar(255, 0, 0), 4);
    line(cards_image, src[3], src[1], Scalar(255, 0, 0), 4);
    line(cards_image, src[3], src[2], Scalar(255, 0, 0), 4);

    imshow("Cards", cards_image);
    imshow("Family", family_card);
    if (waitKey(0) == 'w')
        exit(0);
}