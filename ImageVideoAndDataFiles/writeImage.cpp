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

    Mat img = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_ANYCOLOR);

    cout << "Number of channels : " << img.channels() << endl;

    imwrite("/Users/anurag.sh/Season2/naruto/temp1.jpg", img, {cv::IMWRITE_JPEG_LUMA_QUALITY, 99});
    imwrite("/Users/anurag.sh/Season2/naruto/temp2.jp2", img);
    imwrite("/Users/anurag.sh/Season2/naruto/temp3.tiff", img);
    imwrite("/Users/anurag.sh/Season2/naruto/temp4.png", img);
    imwrite("/Users/anurag.sh/Season2/naruto/temp5.bmp", img);
    imwrite("/Users/anurag.sh/Season2/naruto/temp6.ppm", img);

    Mat img1 = imread("/Users/anurag.sh/Season2/naruto/temp1.jpg", IMREAD_ANYCOLOR);
    Mat img2 = imread("/Users/anurag.sh/Season2/naruto/temp2.jp2", IMREAD_ANYCOLOR);
    Mat img3 = imread("/Users/anurag.sh/Season2/naruto/temp3.tiff", IMREAD_ANYCOLOR);
    Mat img4 = imread("/Users/anurag.sh/Season2/naruto/temp4.png", IMREAD_ANYCOLOR);
    Mat img5 = imread("/Users/anurag.sh/Season2/naruto/temp5.bmp", IMREAD_ANYCOLOR);
    Mat img6 = imread("/Users/anurag.sh/Season2/naruto/temp6.ppm", IMREAD_ANYCOLOR);

    vector<Mat> imgVec = vector<Mat>();
    imgVec.push_back(img1);imgVec.push_back(img2);imgVec.push_back(img3);imgVec.push_back(img4);imgVec.push_back(img5);imgVec.push_back(img6);
    vector<string> flagName = vector<string>();
    flagName.emplace_back("jpg");flagName.emplace_back("jp2");flagName.emplace_back("tiff");flagName.emplace_back("png");flagName.emplace_back("bmp");flagName.emplace_back("ppm");
    FixedSizeMultiImageHandler imgHandler = FixedSizeMultiImageHandler(imgVec);

    for (int i = 0; i < flagName.size(); ++i) {
        addFlagNameToImage(imgHandler, i, flagName[i]);
    }

    imshow(WINDOW_NAME, imgHandler.getCollatedImage());
    imshow("originalImage", img);
    imshow("jpg", img1);
    imshow("jp2", img2);
    imshow("tiff", img3);
    imshow("png", img4);
    imshow("bmp", img5);
    imshow("ppm", img6);
    waitKey(0);


    return 0;
}