#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <utility>
#include <ostream>
#include "../Color.h"

struct MyStruct {
    cv::Point point;
    cv::Rect rect;

    MyStruct(cv::Point pt, cv::Rect rect) {
        this->point = std::move(pt);
        this->rect = std::move(rect);
    }

    MyStruct() {
    }

    friend std::ostream &operator<<(std::ostream &os, const MyStruct &aStruct) {
        os << "point: " << aStruct.point << " rect: " << aStruct.rect;
        return os;
    }
};

void writeMyStruct() {
    cv::FileStorage fileStorage("/Users/anurag.sh/Season2/naruto/abc.yml", cv::FileStorage::APPEND | cv::FileStorage::FORMAT_JSON);
    fileStorage << "myStruct" << "{:";
    fileStorage << "point" << "{:" << "x" << 10 << "y" << 20 << "}";
    fileStorage << "rect" << "{:" << "x1" << 10 << "y1" << 20 << "x2" << 100 << "y2" << 200 << "}";
    fileStorage << "}";
    fileStorage.release();
}

void readMyStruct() {
    cv::FileStorage fileStorage("/Users/anurag.sh/Season2/naruto/abc.yml", cv::FileStorage::READ | cv::FileStorage::FORMAT_JSON);

    cv::FileNode myStruct = fileStorage["myStruct"];
    cv::FileNode point = myStruct["point"];
    cv::FileNode rect = myStruct["rect"];

    MyStruct myStructObj(cv::Point((int) point["x"], (int) point["y"]),
                      cv::Rect((int) rect["x1"], (int) rect["y1"], (int) rect["x2"],  (int) rect["y2"]));
    std::cout << myStructObj << std::endl;

    fileStorage.release();
}

int main() {
    writeMyStruct();
    readMyStruct();
    return 0;
}