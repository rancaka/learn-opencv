#include <initializer_list>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

Mat hstack(initializer_list<Mat>);
Mat vstack(initializer_list<Mat>);