#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_VIDEO";
const string TRACKER_NAME = "VIDEO_TRACKER";

void trackbarCallback(int pos, void* userdata) {
    cout << "Callback" << endl;
    cout << "Callback" << endl;
    cout << pos << endl;
    VideoCapture videoCapture = *(VideoCapture *) userdata;
    videoCapture.set(CAP_PROP_POS_AVI_RATIO, pos/100.0);
}

int main() {
    VideoCapture videoCapture = VideoCapture("/Users/anurag.sh/Season2/naruto/9.mp4");
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 200);
    int videoPos = 0;
    createTrackbar(TRACKER_NAME, WINDOW_NAME, &videoPos, 100, trackbarCallback, &videoCapture);
    Mat img;

    while (true) {
        videoCapture.read(img);
//        videoCapture >> img;
        if (img.empty()) {
            cout << "Ran out of frames" << endl;
            continue;
        }
        imshow(WINDOW_NAME, img);
        if (waitKey(200) == 27) break;
    }
    return 0;
}