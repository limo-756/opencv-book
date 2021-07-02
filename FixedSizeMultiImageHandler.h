//
// Created by anurag.sh on 09/06/21.
//

#pragma FixedSizeMultiImageHandler

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <utility>
#include "bits/stdc++.h"
using namespace std;
using namespace cv;


class FixedSizeMultiImageHandler {
private:
    vector<Mat> componentImages;
    Size sizeOfComponentImage = Size(300, 300);
    Mat collatedImage;
    Size collatedImageSize;
    int noOfRows = 0, noOfCols = 0;

    void collateComponentImages();

    void findNumberOfColumnsAndRowsInResultantImage();

    Rect getComponentImageCoordInCollatedImage(int imageNumber, Mat& temp) const;

public:
    explicit FixedSizeMultiImageHandler(vector<Mat> &images, Size sizeOfComponentImage = Size(300, 300));

    Mat& getCollatedImage();

    Mat& getComponentImage(const int imageNumber);

    int getImageNumber(const Point2i& pixelCoord) const;

    Rect2i getImageCoord(int imageNumber);

    Point2i getImageBottomLeftCoord(const int imageNumber);

    void addTextToImages(const vector<vector<string>> &texts);
};
