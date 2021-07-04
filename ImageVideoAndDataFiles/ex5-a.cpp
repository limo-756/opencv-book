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

void setShape(const int flags) {
    if ((cv::EVENT_FLAG_CTRLKEY & flags) && (cv::EVENT_FLAG_SHIFTKEY & flags)) {
        shape = Shape::line;
    } else if (!(cv::EVENT_FLAG_CTRLKEY & flags) && (cv::EVENT_FLAG_SHIFTKEY & flags)) {
        shape = Shape::circle;
    } else if ((cv::EVENT_FLAG_CTRLKEY & flags) && !(cv::EVENT_FLAG_SHIFTKEY & flags)) {
        shape = Shape::ellipse;
    } else if (!(cv::EVENT_FLAG_CTRLKEY & flags) && !(cv::EVENT_FLAG_SHIFTKEY & flags)) {
        shape = Shape::rect;
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
        setShape(flags);
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

    while (true) {
        if (waitKey(200) == 27) break;
    }
    destroyAllWindows();
    return 0;
}