#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_VIDEO";

int main() {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 200);

    VideoCapture videoCapture = VideoCapture("/Users/anurag.sh/Season2/naruto/9.mp4");

    if (!videoCapture.isOpened()) {
        cout << "File could not be opened" << endl;
        return -1;
    }

    return 0;
}