#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../Color.h"

using namespace std;
using namespace cv;

Point2d *startPosition;
Point2d *endPosition;
bool shouldDraw = false;
enum Shape {
    line, circle, ellipse, rect
};
Shape shape = Shape::line;

void shapeSelector(int pos, void* userdata) {
    switch (pos) {
        case 0:
            shape = Shape::line;
            break;
        case 1:
            shape = Shape::circle;
            break;
        case 2:
            shape = Shape::ellipse;
            break;
        case 3:
            shape = Shape::rect;
            break;
        default:
            shape = Shape::line;
    }
}

void resetImage(Mat &img) {
    img = Mat(Size(700, 700), CV_8UC1, Color::black);
    imshow("CREATE_SELECTION_BOXES", img);
    waitKey(10);
}

void drawShape(Mat &img) {
    if (shape == Shape::line) {
        cv::line(img, *startPosition, *endPosition, Color::brown, 4);
    } else if (shape == Shape::circle) {
        cv::circle(img, *startPosition, norm((*endPosition) - (*startPosition)), Color::brown, 4);
    } else if (shape == Shape::ellipse) {
        cv::ellipse(img, *startPosition, Size(100, norm((*endPosition) - (*startPosition))), 30, 0, 360, Color::brown, 4);
    } else if (shape == Shape::rect) {
        cv::rectangle(img, Rect2d(*startPosition, *endPosition), Color::brown, 4, LINE_8, 0);
    }
    imshow("CREATE_SELECTION_BOXES", img);
    waitKey(10);
}

void drawRect(int event, int x, int y, int flags, void *params) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        startPosition = new Point2d(x, y);
        shouldDraw = true;
    } else if (event == cv::EVENT_LBUTTONUP) {
        endPosition = new Point2d(x, y);
        shouldDraw = false;
        drawShape((*(Mat *) params));
    } else if (event == cv::EVENT_RBUTTONUP) {
        resetImage(*(Mat *) params);
    }
}

int main() {
    Mat img;
    namedWindow("CREATE_SELECTION_BOXES", WINDOW_NORMAL);
    moveWindow("CREATE_SELECTION_BOXES", 300, 200);
    resetImage(img);
    imshow("CREATE_SELECTION_BOXES", img);

    setMouseCallback("CREATE_SELECTION_BOXES", drawRect, &img);
    int pos = 0;
    createTrackbar("SHAPE_SELECTOR_TRACKER", "CREATE_SELECTION_BOXES", &pos, 3, shapeSelector, nullptr);

    while (true) {
        if (waitKey(200) == 27) break;
    }
    destroyAllWindows();
    return 0;
}