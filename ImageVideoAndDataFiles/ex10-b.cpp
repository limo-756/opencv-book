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
    cv::FileStorage fileStorage("/Users/anurag.sh/Season2/naruto/abc.json", cv::FileStorage::APPEND | cv::FileStorage::FORMAT_JSON);
    fileStorage << "myStructArr" << "[";
    for (int i = 1; i < 11; i++) {
        fileStorage << "{";
        fileStorage << "point" << "{" << "x" << i*10 << "y" << i*20 << "}";
        fileStorage << "rect" << "{" << "x1" << i*10 << "y1" << i*20 << "x2" << i*100 << "y2" << i*200 << "}";
        fileStorage << "}";
    }
    fileStorage << "]";
    fileStorage.release();
}

void readMyStruct() {
    cv::FileStorage fileStorage("/Users/anurag.sh/Season2/naruto/abc.json", cv::FileStorage::READ | cv::FileStorage::FORMAT_JSON);

    cv::FileNode myStruct = fileStorage["myStructArr"];
    for (auto && i : myStruct) {
        cv::FileNode point = i["point"];
        cv::FileNode rect = i["rect"];

        MyStruct myStructObj(cv::Point((int) point["x"], (int) point["y"]),
        cv::Rect((int) rect["x1"], (int) rect["y1"], (int) rect["x2"],  (int) rect["y2"]));
        std::cout << myStructObj << std::endl;
    }

    fileStorage.release();
}

int main() {
    writeMyStruct();
    readMyStruct();
    return 0;
}