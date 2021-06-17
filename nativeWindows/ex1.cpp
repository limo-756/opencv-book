#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <utility>
#include "bits/stdc++.h"
#include "../FixedSizeMultiImageHandler.h"
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

const string WINDOW_NAME = "MULTIPLE_IMAGE_BOX";

void displayPixelColorAndImageNumber(const Mat& original, const int imageNumber, const Scalar& color) {
    Mat newImg(original.size(), original.type());
    original.copyTo(newImg);

    string message = "Image Number - " + std::to_string(imageNumber) +
            " Color - " + std::to_string(color[0]) + "," + std::to_string(color[1]) + "," + std::to_string(color[2]) + "," + std::to_string(color[3]);
    putText(newImg, message, Point2i(0, newImg.rows), FONT_HERSHEY_PLAIN, 1, Scalar( 0, 255, 0, 128 ), 2, 8, false);

    cout << message << endl;
    imshow(WINDOW_NAME, newImg);
    newImg.deallocate();
    waitKey(1000);
}

void displayPixelColorAndImageNumberOnMouseClick(int event, int x, int y, int flags, void* params) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        FixedSizeMultiImageHandler obj = *(FixedSizeMultiImageHandler*) params;
        int imageNumber = obj.getImageNumber(Point2i(x,y));
        Mat img = obj.getCollatedImage();
        Vec3b color = img.at<Vec3b>(Point(x,y));
        displayPixelColorAndImageNumber(img, imageNumber, color);
    }
}


int main() {
    Mat img = imread("/Users/anurag.sh/Season2/naruto/flower.jpg", IMREAD_COLOR);
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
    FixedSizeMultiImageHandler obj = FixedSizeMultiImageHandler(v1, Size2i(300, 300));
    Mat finalImage = obj.getCollatedImage();
    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    imshow(WINDOW_NAME, finalImage);
    setMouseCallback(WINDOW_NAME, displayPixelColorAndImageNumberOnMouseClick, &obj);

    while (true) {
        if (waitKey(200) == 27) break;
    }
    destroyAllWindows();
    return 0;
}