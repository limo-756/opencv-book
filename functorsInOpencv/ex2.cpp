#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../Color.h"
#include "../FixedSizeMultiImageHandler.h"
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_RANDOM_PIXELS_IMAGE";

int main(int argc, char *argv[]) {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 300);

    RNG rng;
    Mat uniformDistribution1(20, 1, CV_32FC1, Color::black);
    rng.fill(uniformDistribution1, RNG::UNIFORM, 0.f, 1.f);
    cout << uniformDistribution1 << endl;
    imshow(WINDOW_NAME, uniformDistribution1);
    waitKey(0);

    Mat normalDistribution1(20, 1, CV_32FC1, Color::black);
    rng.fill(normalDistribution1, RNG::NORMAL, 0.f, 1.f);
    cout << normalDistribution1 << endl;
    imshow(WINDOW_NAME, normalDistribution1);
    waitKey(0);

    Mat uniformDistribution2 = Mat(20, 1, CV_8UC1, Color::black);
    rng.fill(uniformDistribution2, RNG::UNIFORM, 0, 255);
    cout << uniformDistribution2 << endl;
    imshow(WINDOW_NAME, uniformDistribution2);
    waitKey(0);

    Mat normalDistribution2 = Mat(20, 1, CV_8UC1, Color::black);
    rng.fill(normalDistribution2, RNG::NORMAL, 150, 100);
    cout << normalDistribution2 << endl;
    imshow(WINDOW_NAME, normalDistribution2);
    waitKey(0);

    Mat uniformDistribution3 = Mat(20, 1, CV_8UC3, Color::black);
    rng.fill(uniformDistribution3, RNG::UNIFORM, 0, 255);
    cout << uniformDistribution3 << endl;
    imshow(WINDOW_NAME, uniformDistribution3);
    waitKey(0);
    return 0;
}