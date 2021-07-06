#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <utility>
#include "../Color.h"

const std::string WINDOW_NAME = "ADD_LABEL";

class AddText {
private:
    cv::Mat img;
    bool writeText = false;
    cv::Point position;
    std::string textToPut;

public:
    explicit AddText() {
        resetImage();
    }

    bool canWrite() const {
        return writeText;
    }

    void startWrite(cv::Point position1) {
        writeText = true;
        textToPut.clear();
        this->position = std::move(position1);
        std::cout << "Start write : " << writeText << " at " << position1 << std::endl;
    }

    void write(char c) {
        if (canWrite() && 'a' <= c && c <= 'z') {
            textToPut = textToPut + c;
        }
    }

    void removeLastChar() {
        if (canWrite() && !textToPut.empty()) {
            textToPut.erase(textToPut.end() -1);
        }
    }

    void addLabel() {
        std::cout << canWrite() << " yes i can write" << std::endl;
        if (canWrite() && !textToPut.empty()) {
            std::cout << "Text put kar " << textToPut << " at : " << position << std::endl;
            cv::putText(img, textToPut, position, cv::FONT_HERSHEY_PLAIN, 2, Color::white, 2, 8, false);
        }
        writeText = false;
        textToPut.clear();
    }

    void resetImage() {
        img = cv::Mat(cv::Size(700, 700), CV_8SC3, Color::brown);
        imshow(WINDOW_NAME, img);
        cv::waitKey(10);
    }
};



void startWrite(int event, int x, int y, int flags, void *params) {
    auto *text = (AddText *) params;
    if (event == cv::EVENT_LBUTTONDOWN) {
        std::cout << "Mouse pressed : " << std::endl;
        text->startWrite(cv::Point2i(x, y));
    } else if (event == cv::EVENT_RBUTTONUP) {
        std::cout << "Mouse unpressed : " << std::endl;
        text->resetImage();
    }
}

int main() {
    cv::namedWindow(WINDOW_NAME, cv::WINDOW_NORMAL);
    cv::moveWindow(WINDOW_NAME, 300, 200);
    AddText text;
    cv::setMouseCallback(WINDOW_NAME, startWrite, &text);

    while (true) {
        char c = (char) cv::waitKey(0);
        std::cout << "Key preseed : " << (int) c << std::endl;
        if (c == 8) {
            text.removeLastChar();
        }
        if (c == 13) {
            text.addLabel();
        }
        if (text.canWrite()) {
            text.write(c);
        }
        if (c == 27) break;
    }
    cv::destroyAllWindows();
    return 0;
}