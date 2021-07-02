//
// Created by anurag.sh on 09/06/21.
//

#include "FixedSizeMultiImageHandler.h"

void FixedSizeMultiImageHandler::collateComponentImages() {
    findNumberOfColumnsAndRowsInResultantImage();

    collatedImageSize = Size2d(sizeOfComponentImage.width * noOfCols, sizeOfComponentImage.height * noOfRows);
    collatedImage = Mat(collatedImageSize, CV_8UC3, Scalar(0, 0, 0, 0));

    for (int imageNumber = 0; imageNumber < componentImages.size(); ++imageNumber) {
        Mat image = componentImages[imageNumber];
        Mat temp;
        double scale = (image.rows > image.cols) ? ((double) sizeOfComponentImage.height / image.rows) : (
                (double) sizeOfComponentImage.width / image.cols);
        resize(image, temp, Size2d(0, 0), scale, scale);

        Mat dest;
        if (temp.channels() != collatedImage.channels()) {
            cvtColor(temp, dest, COLOR_GRAY2RGB);
        } else {
            dest = temp;
        }
        Rect2i componentImageCoordinatesInCollatedImage = getComponentImageCoordInCollatedImage(imageNumber, temp);
        dest.copyTo(collatedImage(componentImageCoordinatesInCollatedImage));
    }
}

void FixedSizeMultiImageHandler::findNumberOfColumnsAndRowsInResultantImage() {
    switch (componentImages.size()) {
        case 1:
            noOfRows = 1;
            noOfCols = 1;
            break;
        case 2:
            noOfRows = 1;
            noOfCols = 2;
            break;
        case 3:
        case 4:
            noOfRows = 2;
            noOfCols = 2;
            break;
        case 5:
        case 6:
            noOfRows = 2;
            noOfCols = 3;
            break;
        case 7:
        case 8:
            noOfRows = 2;
            noOfCols = 4;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            noOfRows = 3;
            noOfCols = 4;
            break;
    }
}

Rect FixedSizeMultiImageHandler::getComponentImageCoordInCollatedImage(int imageNumber, Mat &temp) const {
    int rowNumber = imageNumber / noOfCols;
    int columnNumber = imageNumber % noOfCols;
    return {sizeOfComponentImage.width * columnNumber, sizeOfComponentImage.height * rowNumber, temp.cols, temp.rows};
}

FixedSizeMultiImageHandler::FixedSizeMultiImageHandler(vector<Mat> &images, Size sizeOfComponentImage) {
    assert(images.size() <= 12);
    assert(sizeOfComponentImage.width == sizeOfComponentImage.height);
    this->componentImages = images;
    this->sizeOfComponentImage = std::move(sizeOfComponentImage);
    this->collateComponentImages();
}

Mat &FixedSizeMultiImageHandler::getCollatedImage() {
    return collatedImage;
}

Mat &FixedSizeMultiImageHandler::getComponentImage(const int imageNumber) {
    return componentImages[imageNumber];
}

int FixedSizeMultiImageHandler::getImageNumber(const Point2i& pixelCoord) const {
    return (pixelCoord.x / sizeOfComponentImage.width) + (pixelCoord.y / sizeOfComponentImage.height) * noOfCols;
}

Point2i FixedSizeMultiImageHandler::getCoordinatesWithRespectToComponentImage(const Point2i& pixelCoord) {
    int imageNumber = getImageNumber(pixelCoord);
    Rect2i componentImageCoord = getComponentImageCoordInCollatedImage(imageNumber);
    return {pixelCoord.x - componentImageCoord.x, pixelCoord.y - componentImageCoord.y};
}

Rect2i FixedSizeMultiImageHandler::getComponentImageCoordInCollatedImage(int imageNumber) {
    assert(imageNumber < componentImages.size());
    int rowNumber = imageNumber/this->noOfCols;
    int colNumber = imageNumber%this->noOfCols;
    return {sizeOfComponentImage.width * colNumber, sizeOfComponentImage.height * rowNumber, sizeOfComponentImage.width, sizeOfComponentImage.height};
}

Point2i FixedSizeMultiImageHandler::getImageBottomLeftCoord(const int imageNumber) {
    assert(imageNumber < componentImages.size());
    Point2i bottomRightCoord = this->getComponentImageCoordInCollatedImage(imageNumber).br();
    return {bottomRightCoord.x - sizeOfComponentImage.width, bottomRightCoord.y};
}

void FixedSizeMultiImageHandler::addTextToImages(const vector<vector<string>> &texts) {
    assert(texts.size() == componentImages.size());
    for (int imageNumber = 0; imageNumber < texts.size(); ++imageNumber) {
        int textHeight = 0;
        for (int textNumber = 0; textNumber < texts[imageNumber].size(); ++textNumber) {
            Size textLocation = Size(getImageBottomLeftCoord(imageNumber).x, getImageBottomLeftCoord(imageNumber).y - textHeight);
            putText(getCollatedImage(), texts[imageNumber][textNumber], textLocation, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0, 128 ), 2, 8, false);

            int temp = 0;
            Size textSize = getTextSize(texts[imageNumber][textNumber], FONT_HERSHEY_PLAIN, 1, 2, &temp);
            textHeight = textHeight + 2 + textSize.height;
        }
    }
}



