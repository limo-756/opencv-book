#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_VIDEO";

int main() {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 200);

    VideoCapture videoCapture;
    videoCapture.open(0);

    if (!videoCapture.isOpened()) {
        cout << "File could not be opened" << endl;
        return -1;
    }

    Mat img;
    while (true) {
        videoCapture >> img;
        imshow(WINDOW_NAME, img);
        if (waitKey(10) == 27) break;
    }

    return 0;
}