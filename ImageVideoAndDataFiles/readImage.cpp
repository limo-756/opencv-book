#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "FixedSizeMultiImageHandler.h"
using namespace std;
using namespace cv;

const string WINDOW_NAME = "SHOW_IMAGE";


void addFlagNameToImage(FixedSizeMultiImageHandler& imgHandler, const int imageNumber, const string& flagName) {
    putText(imgHandler.getCollatedImage(), flagName, imgHandler.getImageBottomLeftCoord(imageNumber), FONT_HERSHEY_PLAIN, 1, Scalar( 0, 255, 0, 128 ), 2, 8,false);

    int textHeight;
    Size textSize = getTextSize(flagName, FONT_HERSHEY_PLAIN, 1, 2, &textHeight);

    string message = "c : " + std::to_string(imgHandler.getComponentImage(imageNumber).channels());
    putText(imgHandler.getCollatedImage(), message, Size(imgHandler.getImageBottomLeftCoord(imageNumber).x, imgHandler.getImageBottomLeftCoord(imageNumber).y - textSize.height - 2), FONT_HERSHEY_PLAIN, 1, Scalar( 0, 255, 0, 128 ), 2, 8, false);
}

int main() {
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    moveWindow(WINDOW_NAME, 300, 200);

    Mat img1 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_UNCHANGED);
    Mat img2 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_GRAYSCALE);
    Mat img3 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_COLOR);
    Mat img4 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_ANYDEPTH);
    Mat img5 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_ANYCOLOR);
    Mat img6 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_LOAD_GDAL);

    Mat img7 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_REDUCED_GRAYSCALE_2);
    Mat img8 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_REDUCED_COLOR_2);
    Mat img9 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_REDUCED_GRAYSCALE_4);
    Mat img10 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_REDUCED_COLOR_4);
    Mat img11 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_REDUCED_GRAYSCALE_8);
    Mat img12 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_REDUCED_COLOR_8);
    Mat img13 = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_IGNORE_ORIENTATION);

    if (img1.empty() || img2.empty() || img3.empty() || img4.empty() || img5.empty() || img6.empty()) {
        cout << "File could not be opened in first 6 formats" << endl;
    } else {
        vector<Mat> imgVec = vector<Mat>();
        imgVec.push_back(img1);imgVec.push_back(img2);imgVec.push_back(img3);imgVec.push_back(img4);imgVec.push_back(img5);imgVec.push_back(img6);
        vector<string> flagName = vector<string>();
        flagName.emplace_back("IMREAD_UNCHANGED");flagName.emplace_back("IMREAD_GRAYSCALE");flagName.emplace_back("IMREAD_COLOR");flagName.emplace_back("IMREAD_ANYDEPTH");flagName.emplace_back("IMREAD_ANYCOLOR");flagName.emplace_back("IMREAD_LOAD_GDAL");
        FixedSizeMultiImageHandler imgHandler = FixedSizeMultiImageHandler(imgVec);
        for (int i = 0; i < flagName.size(); ++i) {
            addFlagNameToImage(imgHandler, i, flagName[i]);
        }

        imshow(WINDOW_NAME, imgHandler.getCollatedImage());
        waitKey(0);
    }

    if (img7.empty() || img8.empty() || img9.empty() || img10.empty() || img11.empty() || img12.empty() || img13.empty()) {
        cout << "File could not be opened in first 6 formats" << endl;
    } else {
        vector<Mat> imgVec = vector<Mat>();
        imgVec.push_back(img7);imgVec.push_back(img8);imgVec.push_back(img9);imgVec.push_back(img10);imgVec.push_back(img11);imgVec.push_back(img12);imgVec.push_back(img13);
        vector<string> flagName = vector<string>();
        flagName.emplace_back("IMREAD_REDUCED_GRAYSCALE_2");flagName.emplace_back("IMREAD_REDUCED_COLOR_2");flagName.emplace_back("IMREAD_REDUCED_GRAYSCALE_4");flagName.emplace_back("IMREAD_REDUCED_COLOR_4");flagName.emplace_back("IMREAD_REDUCED_GRAYSCALE_8");flagName.emplace_back("IMREAD_REDUCED_COLOR_8");flagName.emplace_back("IMREAD_IGNORE_ORIENTATION");
        FixedSizeMultiImageHandler imgHandler = FixedSizeMultiImageHandler(imgVec);
        for (int i = 0; i < flagName.size(); ++i) {
            addFlagNameToImage(imgHandler, i, flagName[i]);
        }

        imshow(WINDOW_NAME, imgHandler.getCollatedImage());
        waitKey(0);
    }



    return 0;
}