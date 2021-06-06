#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <utility>
#include "/usr/local/include/c++/10.2.0/bits/stdc++.h"
using namespace std;
using namespace cv;

void ShowManyImages(string title, vector<Mat> &images) {
    int nArgs = images.size();
    int size;
    int i;
    int m, n;
    int x, y;

// w - Maximum number of images in a row
// h - Maximum number of images in a column
    int w, h;

// scale - How much we have to resize the image
    float scale;
    int max;

// If the number of arguments is lesser than 0 or greater than 12
// return without displaying
    if(nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;
    }
    else if(nArgs > 14) {
        printf("Number of arguments too large, can only handle maximally 12 images at a time ...\n");
        return;
    }
// Determine the size of the image,
// and the number of rows/cols
// from number of arguments
    else if (nArgs == 1) {
        w = h = 1;
        size = 300;
    }
    else if (nArgs == 2) {
        w = 2; h = 1;
        size = 300;
    }
    else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 300;
    }
    else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 200;
    }
    else if (nArgs == 7 || nArgs == 8) {
        w = 4; h = 2;
        size = 200;
    }
    else {
        w = 4; h = 3;
        size = 150;
    }

// Create a new 3 channel image
    Mat DispImage = Mat::zeros(Size(100 + size*w, 60 + size*h), CV_8UC3);

// Loop for nArgs number of arguments
    for (i = 0, m = 20, n = 20; i < images.size(); i++, m += (20 + size)) {
        // Get the Pointer to the IplImage
        cout << "Hello : " << i << endl;
        Mat img = images[i];

        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        if(img.empty()) {
            printf("Invalid arguments");
            return;
        }

        // Find the width and height of the image
        x = img.cols;
        y = img.rows;

        // Find whether height or width is greater in order to resize the image
        max = (x > y)? x: y;

        // Find the scaling factor to resize the image
        scale = (float) ( (float) max / size );

        // Used to Align the images
        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

        // Set the image ROI to display the current image
        // Resize the input image and copy the it to the Single Big Image
        Rect ROI(m, n, (int)( x/scale ), (int)( y/scale ));
        Mat temp; resize(img,temp, Size(ROI.width, ROI.height));
        temp.copyTo(DispImage(ROI));
    }

// Create a new window, and show the Single Big Image
    namedWindow( title, 1 );
    imshow( title, DispImage);
    waitKey();

// End the number of arguments
}

class FixedSizeMultiImageHandler {
    vector<Mat> componentImages;
    Size sizeOfComponentImage = Size(300, 300);
    Mat collatedImage;
    Size collatedImageSize;
    int noOfRows = 0, noOfCols = 0;

    void collateComponentImages() {
        findNumberOfColumnsAndRowsInResultantImage();

        collatedImageSize = Size2d(sizeOfComponentImage.width * noOfCols, sizeOfComponentImage.height * noOfRows);
        collatedImage = Mat(collatedImageSize, CV_8UC3, Scalar(0, 0, 0, 0));

        for (int imageNumber = 0; imageNumber < componentImages.size(); ++imageNumber) {
            Mat image = componentImages[imageNumber];
            Mat temp;
            double scale = (image.rows > image.cols) ? ((double) sizeOfComponentImage.height/image.rows) : ((double) sizeOfComponentImage.width/image.cols);
            resize(image, temp, Size2d(0 , 0), scale, scale);

            Rect2i componentImageCoordinatesInCollatedImage = getComponentImageCoordInCollatedImage(imageNumber, temp);
            temp.copyTo(collatedImage(componentImageCoordinatesInCollatedImage));
        }
    }

    void findNumberOfColumnsAndRowsInResultantImage() {
        switch (componentImages.size()) {
            case 1:
                noOfRows = 1; noOfCols = 1;
                break;
            case 2:
                noOfRows = 1; noOfCols = 2;
                break;
            case 3:
            case 4:
                noOfRows = 2; noOfCols = 2;
                break;
            case 5:
            case 6:
                noOfRows = 2; noOfCols = 3;
                break;
            case 7:
            case 8:
                noOfRows = 2; noOfCols = 4;
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                noOfRows = 3; noOfCols = 4;
                break;
        }
    }

    Rect getComponentImageCoordInCollatedImage(int imageNumber, Mat& temp) const {
        int rowNumber = imageNumber/noOfCols;
        int columnNumber = imageNumber%noOfCols;
        return {sizeOfComponentImage.width * columnNumber, sizeOfComponentImage.height * rowNumber, temp.cols, temp.rows};
    }

public:
    explicit FixedSizeMultiImageHandler(vector<Mat> &images, Size sizeOfComponentImage = Size(300, 300)) {
        assert(images.size() <= 12);
        assert(sizeOfComponentImage.width == sizeOfComponentImage.height);
        this->componentImages = images;
        this->sizeOfComponentImage = std::move(sizeOfComponentImage);
        this->collateComponentImages();
    }

    Mat& getCollatedImage() {
        return collatedImage;
    }
};

int main() {
    Mat img = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", IMREAD_COLOR);
    namedWindow("ABCD", WINDOW_NORMAL);
    imshow("ABCD", img);
    vector<Mat> v1;
    v1.push_back(img);
    v1.push_back(img);
    v1.push_back(img);
    v1.push_back(img);
    v1.push_back(img);
    v1.push_back(img);
    v1.push_back(img);
    v1.push_back(img);
//    ShowManyImages("CREATE_SELECTION_BOXES", v1);
    FixedSizeMultiImageHandler obj = FixedSizeMultiImageHandler(v1);
    Mat finalImage = obj.getCollatedImage();
    namedWindow("MULTIPLE_IMAGE_BOX", WINDOW_NORMAL);
    imshow("MULTIPLE_IMAGE_BOX", finalImage);
    waitKey(0);
    return 0;
}