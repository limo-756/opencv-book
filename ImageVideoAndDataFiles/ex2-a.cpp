#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../FixedSizeMultiImageHandler.h"
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_MOUSE_CLICK_COORDINATES";

void addMouseClickCoordinates(int event, int x, int y, int flags, void* params) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        FixedSizeMultiImageHandler imageHandler = *(FixedSizeMultiImageHandler *) params;
        Mat newImg(imageHandler.getCollatedImage().size(), imageHandler.getCollatedImage().type());
        imageHandler.getCollatedImage().copyTo(newImg);

        Point2i coordinatesWithRespectToComponentImage = imageHandler.getCoordinatesWithRespectToComponentImage(Point2i(x, y));
        string message = "(" + std::to_string(coordinatesWithRespectToComponentImage.x) + ", " + std::to_string(coordinatesWithRespectToComponentImage.y) + ")" ;
        putText(newImg, message, Size(x, y), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0, 128 ), 2, 8, false);

        imshow(WINDOW_NAME, newImg);
        newImg.deallocate();
        waitKey(10);
    }
}

int main() {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 300);

    Mat img1 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_UNCHANGED);
    Mat img2 = imread("/Users/anurag.sh/Season2/naruto/car.jpg", IMREAD_UNCHANGED);
    Mat img3 = imread("/Users/anurag.sh/Season2/naruto/person.jpg", IMREAD_UNCHANGED);

    vector<Mat> imgVec{img1, img2, img3};
    FixedSizeMultiImageHandler imageHandler = FixedSizeMultiImageHandler(imgVec);

    setMouseCallback(WINDOW_NAME, addMouseClickCoordinates, &imageHandler);

    imshow(WINDOW_NAME, imageHandler.getCollatedImage());

    while (true) {
        if (waitKey(200) == 27) break;
    }
    return 0;
}