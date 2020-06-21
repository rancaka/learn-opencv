#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat cards_image = imread("resources/cards.jpg");

    vector<Point2f> src = {
        Point2f(548, 197),
        Point2f(697, 232),
        Point2f(465, 370),
        Point2f(632, 417)
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
    Mat as_heart_card;
    warpPerspective(cards_image, as_heart_card, matrix, Size(card_width, card_height));

    imshow("Cards", cards_image);
    imshow("As Heart", as_heart_card);
    if (waitKey(0) == 'w')
        exit(0);
}