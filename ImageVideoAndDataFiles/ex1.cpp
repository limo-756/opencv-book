#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

const string WINDOW1_NAME = "SHOW_ORIGINAL_VIDEO";
const string WINDOW2_NAME = "SHOW_GRAYSCALE_VIDEO";
const string WINDOW3_NAME = "SHOW_CANNY_EDGE_VIDEO";

int main() {
    namedWindow(WINDOW1_NAME, WINDOW_NORMAL);
    namedWindow(WINDOW2_NAME, WINDOW_NORMAL);
    namedWindow(WINDOW3_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW1_NAME, 0, 0);
    moveWindow(WINDOW2_NAME, 300, 0);
    moveWindow(WINDOW3_NAME, 600, 0);

    VideoCapture videoCapture = VideoCapture("/Users/anurag.sh/Season2/naruto/9.mp4");

    if (!videoCapture.isOpened()) {
        cout << "File could not be opened" << endl;
        return -1;
    }

    Mat frame;
    while (true) {
        videoCapture >> frame;
        if (frame.empty()) {
            cout << "Video ended" << endl;
            break;
        }

        Mat grayScaleImage, cannyEdgeDetection;
        cvtColor(frame, grayScaleImage, COLOR_BGR2GRAY, 1);
        Canny(grayScaleImage, cannyEdgeDetection, 10, 30);
        imshow(WINDOW1_NAME, frame);
        imshow(WINDOW2_NAME, grayScaleImage);
        imshow(WINDOW3_NAME, cannyEdgeDetection);
        if (waitKey(10) == 27 ) break;
    }

    return 0;
}