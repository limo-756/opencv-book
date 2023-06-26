#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "../Color.h"
#include "../FixedSizeMultiImageHandler.h"
#include "/Users/anurag.sh/workspace/c++/cvplot/include/cvplot/cvplot.h"
#include "../EasyPrint.cpp"
using namespace std;
using namespace cv;

const string GRAPH_WINDOW = "SHOW_RANDOM_PIXELS_IMAGE";

void drawGraph(const Mat &computedMat) {
    namedWindow(GRAPH_WINDOW, WINDOW_NORMAL);
    moveWindow(GRAPH_WINDOW, 300, 300);

    vector<pair<float, float>> data;
    data.reserve(computedMat.rows);
for (int i = 0; i < computedMat.rows; ++i) {
        trace(computedMat.at<float>(i, 0, 0), computedMat.at<float>(i, 1, 0))
        data.emplace_back(computedMat.at<float>(i,0, 0), computedMat.at<float>(i,1, 0));
    }

    for (int i = 0; i < data.size(); ++i) {
        trace(i, data[i].first, data[i].second)
    }

    auto name = "SHOW_RANDOM_PIXELS_IMAGE";
    cvplot::setWindowTitle(name, "math curves");
    cvplot::moveWindow(name, 300, 0);
    cvplot::resizeWindow(name, 300, 300);
    auto &figure = cvplot::figure(name);
    figure.series(GRAPH_WINDOW)
        .set(data)
        .type(cvplot::Dots)
        .color(cvplot::Orange);

    figure.show(true);
}

int main(int argc, char *argv[]) {
    RNG rng(0);
    Mat imageWithDifferentDistributionInEveryDimension = Mat(20, 3, CV_16UC1, Color::black);

    for (int i = 0; i < imageWithDifferentDistributionInEveryDimension.rows; ++i) {
        int a = ((int) rng.gaussian(10)) + 64;
        int b = ((int) rng.gaussian(10)) + 192;
        int c = ((int) rng.gaussian(2)) + 128;
        imageWithDifferentDistributionInEveryDimension.at<int>(i,0, 0) = a;
        imageWithDifferentDistributionInEveryDimension.at<int>(i,1, 0) = b;
        imageWithDifferentDistributionInEveryDimension.at<int>(i,2, 0) = c;
        trace(a, b, c)
    }

    trace(imageWithDifferentDistributionInEveryDimension)
    PCA pca(imageWithDifferentDistributionInEveryDimension, Mat(), PCA::DATA_AS_ROW);

    trace(pca.mean, pca.eigenvectors, pca.eigenvalues)

    Mat computedMat = pca.project(Mat(20,3, CV_16UC1));
    trace(computedMat)
    drawGraph(computedMat);
    waitKey(0);
    return 0; 
}