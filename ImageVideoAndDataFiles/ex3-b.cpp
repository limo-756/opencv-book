#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../FixedSizeMultiImageHandler.h"
#include "/Users/anurag.sh/workspace/c++/cvplot/include/cvplot/cvplot.h"
using namespace std;
using namespace cv;

Point2d* startPosition;
Point2d* endPosition;
bool shouldDraw = false;
const string GRAPH_WINDOW = "GRAPH_HISTOGRAM";

void drawGraph(const float red, const float blue, const float green) {
    auto &figure = cvplot::figure(GRAPH_WINDOW);
    figure.series("histogram")
            .setValue({red, blue, green})
            .type(cvplot::Histogram)
            .color(cvplot::Red);
    figure.show(true);

}

void drawRectangle(const Mat& original, const bool draw) {
    Mat newImg(original.size(), original.type());
    original.copyTo(newImg);

    if (draw) {
        rectangle(newImg, Rect2d(*startPosition, *endPosition), Scalar( 0, 255, 0, 128 ), 1, LINE_8, 0);
        long red = 0, blue =0, green =0;
        for (int row = startPosition->y; row < endPosition->y; ++row) {
            for (int col = startPosition->x; col < endPosition->x; ++col) {
                Vec3b color = newImg.at<Vec3b>(Point(col, row));
                if (color[0] < 100) red++;
                if (100 < color[0] && color[0] < 200) blue++;
                if (200 < color[0]) green++;
            }
        }
        drawGraph(red, blue, green);
    }
    imshow("CREATE_SELECTION_BOXES", newImg);
    newImg.deallocate();
    waitKey(1000);
}

void drawRect(int event, int x, int y, int flags, void* params) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        startPosition = new Point2d(x, y);
        shouldDraw = true;
    } else if (event == cv::EVENT_MOUSEMOVE) {
        endPosition = new Point2d(x, y);
    } else if (event == cv::EVENT_LBUTTONUP) {
        endPosition = new Point2d(x, y);
        shouldDraw = false;
        drawRectangle(Mat(*(Mat *) params), false);
    }

    if (shouldDraw) {
        drawRectangle(Mat(*(Mat *) params), true);
    }
}

int main()
{
    Mat img = imread("/Users/anurag.sh/Season2/naruto/flower.JPG", IMREAD_GRAYSCALE);
    namedWindow("CREATE_SELECTION_BOXES", WINDOW_NORMAL);
    moveWindow("CREATE_SELECTION_BOXES", 300, 200);
    imshow("CREATE_SELECTION_BOXES", img);

    setMouseCallback("CREATE_SELECTION_BOXES", drawRect, &img);

    cvplot::setWindowTitle(GRAPH_WINDOW, "line and histogram");
    cvplot::moveWindow(GRAPH_WINDOW, 0, 0);
    cvplot::resizeWindow(GRAPH_WINDOW, 300, 300);
    drawGraph(0.0, 0.0, 0.0);


    while (true) {
        if (waitKey(200) == 27) break;
    }
    destroyAllWindows();
    return 0;
}