#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

Point2i* startPosition;
Point2i* endPosition;
bool shouldDraw = false;

void drawRectangleOnTempImage(const Mat& mainImage) {
    Mat tempImage(mainImage.size(), mainImage.type());
    mainImage.copyTo(tempImage);
    rectangle(tempImage, Rect2d(*startPosition, *endPosition), Scalar(0, 255, 0, 128 ), 1, LINE_8, 0);
    imshow("CREATE_SELECTION_BOXES", tempImage);
    tempImage.deallocate();
}

void drawRectangleOnMainImage(const Mat& mainImage) {
    rectangle(mainImage, Rect2d(*startPosition, *endPosition), Scalar( 0, 255, 0, 128 ), 1, LINE_8, 0);
    imshow("CREATE_SELECTION_BOXES", mainImage);
}

void drawRect(int event, int x, int y, int flags, void* params) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        startPosition = new Point2i(x, y);
        endPosition = new Point2i(x,y);
        shouldDraw = true;
    } else if (event == cv::EVENT_MOUSEMOVE) {
        endPosition = new Point2i(x, y);
    } else if (event == cv::EVENT_LBUTTONUP) {
        endPosition = new Point2i(x, y);
        shouldDraw = false;
        drawRectangleOnMainImage(Mat(*(Mat *) params));
        return;
    }

    if (shouldDraw) {
        drawRectangleOnTempImage(Mat(*(Mat *) params));
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