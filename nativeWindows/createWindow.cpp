#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
//#include "bits/stdc++.h"
using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", 0);
    namedWindow("WINDOW_NORMAL", WINDOW_NORMAL);
    namedWindow("WINDOW_AUTOSIZE", WINDOW_AUTOSIZE);
    namedWindow("WINDOW_OPENGL", WINDOW_OPENGL);
    namedWindow("WINDOW_FULLSCREEN", WINDOW_FULLSCREEN);
    namedWindow("WINDOW_FREERATIO", WINDOW_FREERATIO);
    namedWindow("WINDOW_KEEPRATIO", WINDOW_KEEPRATIO);
    namedWindow("WINDOW_GUI_EXPANDED", WINDOW_GUI_EXPANDED);
    namedWindow("WINDOW_GUI_NORMAL", WINDOW_GUI_NORMAL);

    moveWindow("WINDOW_NORMAL", 0, 0);
    moveWindow("WINDOW_AUTOSIZE", 400, 0);
    moveWindow("WINDOW_OPENGL", 800, 0);
    moveWindow("WINDOW_FULLSCREEN", 0, 400);
    moveWindow("WINDOW_FREERATIO", 400, 400);
    moveWindow("WINDOW_KEEPRATIO", 800, 400);
    moveWindow("WINDOW_GUI_EXPANDED", 0, 800);
    moveWindow("WINDOW_GUI_NORMAL", 400, 800);

    imshow("WINDOW_NORMAL", img);
    imshow("WINDOW_AUTOSIZE", img);
    imshow("WINDOW_OPENGL", img);
    imshow("WINDOW_FULLSCREEN", img);
    imshow("WINDOW_FREERATIO", img);
    imshow("WINDOW_KEEPRATIO", img);
    imshow("WINDOW_GUI_EXPANDED", img);
    imshow("WINDOW_GUI_NORMAL", img);

    waitKey(0);
    destroyAllWindows();
    return 0;
}