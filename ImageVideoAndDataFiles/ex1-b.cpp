#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../FixedSizeMultiImageHandler.h"
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_CANNY_EDGE_PROCESS";

int main() {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 300);

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

        Mat grayScaleImage, gaussianBlurImage, cannyEdgeDetection;
        cvtColor(frame, grayScaleImage, COLOR_BGR2GRAY, 1);
        GaussianBlur(grayScaleImage, gaussianBlurImage, Size(5,5), 0.0);
        Canny(gaussianBlurImage, cannyEdgeDetection, 10, 30);
        vector<Mat> imgVec({frame, grayScaleImage, gaussianBlurImage, cannyEdgeDetection});
        FixedSizeMultiImageHandler imageHandler = FixedSizeMultiImageHandler(imgVec, Size(600,600));

        vector<vector<string>> textVec{{"Original Image"}, {"Gray Scale Image"}, {"Blurred Image"}, {"Canny Edge Detection Image"}};
        imageHandler.addTextToImages(textVec);
        imshow(WINDOW_NAME, imageHandler.getCollatedImage());
        if (waitKey(10) == 27 ) break;
    }

    return 0;
}