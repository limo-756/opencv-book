//#include <opencv2/opencv.hpp>
//#include <opencv2/core/mat.hpp>
////#include "bits/stdc++.h"
//using namespace std;
//using namespace cv;
//
//int main(int argc, char const *argv[])
//{
//    Mat img = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", -1);
//    // circle(img, Point(200, 200), 50, Scalar(10,10, 10, 10), 10, 8, 0);
//    // putText(img, "Anurag", Point(400,800), FONT_HERSHEY_PLAIN, 4, Scalar(10,10,10,10), 4, 8, false);
//    Mat img1;
//    Sobel(img, img1, CV_8U, 1, 1, 5, 1, 0, BORDER_DEFAULT);
//    namedWindow("abcd", WINDOW_AUTOSIZE);
//    imshow("abcd", img1);
//    waitKey(0);
//    destroyWindow("abcd");
//    return 0;
//}

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
//#include "bits/stdc++.h"
using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = imread("/Users/anurag.sh/Season2/naruto/DSC_1917.JPG", 0);
    // circle(img, Point(200, 200), 50, Scalar(10,10, 10, 10), 10, 8, 0);
    // putText(img, "Anurag", Point(400,800), FONT_HERSHEY_PLAIN, 4, Scalar(10,10,10,10), 4, 8, false);
    Mat img1;
    Laplacian(img, img1, CV_8U, 15, 1, 0, BORDER_DEFAULT);
    namedWindow("abcd", WINDOW_AUTOSIZE);
    imshow("abcd", img1);
    waitKey(0);
    destroyWindow("abcd");
    return 0;
}