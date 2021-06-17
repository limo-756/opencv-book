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

        Rect2i componentImageCoordinatesInCollatedImage = getComponentImageCoordInCollatedImage(imageNumber, temp);
        temp.copyTo(collatedImage(componentImageCoordinatesInCollatedImage));
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

int FixedSizeMultiImageHandler::getImageNumber(const Point2i pixelCoord) {
    return (pixelCoord.x / sizeOfComponentImage.width) + (pixelCoord.y / sizeOfComponentImage.height) * noOfCols + 1;
}


