#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

Point2d* startPosition;
Point2d* endPosition;
bool shouldDraw = false;

void drawRectangle(const Mat& original, const bool draw) {
    Mat newImg(original.size(), original.type());
    original.copyTo(newImg);

    if (draw) {
        rectangle(newImg, Rect2d(*startPosition, *endPosition), Scalar( 0, 255, 0, 128 ), 1, LINE_8, 0);
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
    Mat img = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_COLOR);
    namedWindow("CREATE_SELECTION_BOXES", WINDOW_NORMAL);
    moveWindow("CREATE_SELECTION_BOXES", 300, 200);
    imshow("CREATE_SELECTION_BOXES", img);

    setMouseCallback("CREATE_SELECTION_BOXES", drawRect, &img);

    while (true) {
        if (waitKey(200) == 27) break;
    }
    destroyAllWindows();
    return 0;
}