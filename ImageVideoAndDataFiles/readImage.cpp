#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "FixedSizeMultiImageHandler.h"
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_IMAGE";

int main() {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 200);

    Mat img1 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_UNCHANGED);
    Mat img2 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_GRAYSCALE);
    Mat img3 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_COLOR);
    Mat img4 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_ANYDEPTH);
    Mat img5 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_ANYCOLOR);
    Mat img6 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_LOAD_GDAL);

    Mat img7 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_REDUCED_GRAYSCALE_2);
    Mat img8 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_REDUCED_COLOR_2);
    Mat img9 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_REDUCED_GRAYSCALE_4);
    Mat img10 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_REDUCED_COLOR_4);
    Mat img11 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_REDUCED_GRAYSCALE_8);
    Mat img12 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_REDUCED_COLOR_8);
    Mat img13 = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_IGNORE_ORIENTATION);

    if (img1.empty() || img2.empty() || img3.empty() || img4.empty() || img5.empty() || img6.empty()) {
        cout << "File could not be opened in first 6 formats" << endl;
    } else {
        vector<Mat> imgVec = vector<Mat>();
        imgVec.push_back(img1);imgVec.push_back(img2);imgVec.push_back(img3);imgVec.push_back(img4);imgVec.push_back(img5);imgVec.push_back(img6);
        FixedSizeMultiImageHandler imgHandler = FixedSizeMultiImageHandler(imgVec);
    }



    return 0;
}