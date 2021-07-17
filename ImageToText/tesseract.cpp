#include "/usr/local/include/tesseract/baseapi.h"
#include "/usr/local/include/leptonica/allheaders.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../FixedSizeMultiImageHandler.h"
using namespace cv;
using namespace std;

Pix* mat8ToPix(cv::Mat *mat8)
{
    Pix *pixd = pixCreate(mat8->size().width, mat8->size().height, 8);
    for(int y=0; y<mat8->rows; y++) {
        for(int x=0; x<mat8->cols; x++) {
            pixSetPixel(pixd, x, y, (l_uint32) mat8->at<uchar>(y,x));
        }
    }
    return pixd;
}

int main()
{
    char *outText;

    auto *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init("/Users/anurag.sh/workspace/SQLDump/acurate", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Mat img = imread("/Users/anurag.sh/Season2/naruto/myText.jpeg");
//    Pix *image = pixRead("/Users/anurag.sh/workspace/SQLDump/myText.jpeg");

    Mat grayScaleImage, gaussianBlurImage, cannyEdgeDetection;

    cvtColor(img, grayScaleImage, COLOR_BGR2GRAY, 1);
    GaussianBlur(grayScaleImage, gaussianBlurImage, Size(5,5), 0.0);
    Canny(gaussianBlurImage, cannyEdgeDetection, 10, 30, 3, false);
    vector<Mat> imgVec({img, grayScaleImage, gaussianBlurImage, cannyEdgeDetection});
    FixedSizeMultiImageHandler imageHandler = FixedSizeMultiImageHandler(imgVec, Size(600,600));
    imshow("abcd", imageHandler.getCollatedImage());
    waitKey(0);

    Pix *image1 = mat8ToPix(&img);
    api->SetSourceResolution(300);
    api->SetImage(image1);
//    api->SetRectangle(30, 86, 590, 100);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);
    printf("OCR output:\n%s", api->GetUNLVText());

    // Destroy used object and release memory
    api->End();
    delete api;
    delete [] outText;
//    pixDestroy(&image1);
    return 0;
}
