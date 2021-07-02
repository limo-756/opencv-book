#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../FixedSizeMultiImageHandler.h"
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_MOUSE_CLICK_COORDINATES";

void addMouseClickCoordinates(int event, int x, int y, int flags, void* params) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        Mat original = *(Mat *) params;
        Mat newImg(original.size(), original.type());
        original.copyTo(newImg);

        Vec3b color = newImg.at<Vec3b>(Point(x,y));
        string message = " Color - " + std::to_string(color[0]) + "," + std::to_string(color[1]) + "," + std::to_string(color[2]) + "," + std::to_string(color[3]);
        putText(newImg, message, Size(x, y), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0, 128 ), 2, 8, false);

        imshow(WINDOW_NAME, newImg);
        newImg.deallocate();
        waitKey(10);
    }
}

int main() {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 300);

    Mat img = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_UNCHANGED);

    setMouseCallback(WINDOW_NAME, addMouseClickCoordinates, &img);

    imshow(WINDOW_NAME, img);

    while (true) {
        if (waitKey(200) == 27) break;
    }
    return 0;
}