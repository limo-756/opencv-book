#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    RNG rng;
    cout << (float) rng.uniform(0.f, 1.f) << endl;
    cout << (float) rng.uniform(0.f, 1.f) << endl;
    cout << (float) rng.uniform(0.f, 1.f) << endl;

    cout << (double) rng.gaussian(1.0) << endl;
    cout << (double) rng.gaussian(1.0) << endl;
    cout << (double) rng.gaussian(1.0) << endl;

    cout << (int) rng.uniform(0, 255) << endl;
    cout << (int) rng.uniform(0, 255) << endl;
    cout << (int) rng.uniform(0, 255) << endl;
    return 0;
}