#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

Point2d* startPosition;
Point2d* endPosition;

void drawRect(int event, int x, int y, int flags, void* params) {
    bool shouldDraw = false;
    cout << "In draw method " << event << " -> " << x << " : " << y << endl;
    if (event == cv::EVENT_LBUTTONDOWN) {
        startPosition = new Point2d(x, y);
        shouldDraw = true;
    } else if (event == cv::EVENT_MOUSEMOVE) {
//        endPosition = Point2d(x, y);
//        shouldDraw = true;
    } else if (event == cv::EVENT_LBUTTONUP) {
        endPosition = new Point2d(x, y);
        shouldDraw = true;
    }

    if (shouldDraw) {
        Mat orignal = Mat(*(Mat *) params);
        Mat newImg(orignal.size(), orignal.type());
        orignal.copyTo(newImg);
        rectangle(newImg, Rect2d(*startPosition, *endPosition), Scalar( 0, 255, 0, 128 ), 1, LINE_8, 0);
        imshow("CREATE_SELECTION_BOXES", newImg);
        waitKey(1000);
//        startPosition = NULL;
//        endPosition = NULL;
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