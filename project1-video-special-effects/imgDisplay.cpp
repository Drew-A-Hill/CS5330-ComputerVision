/*
  Drew Hill
  Summer 2026 
  CS5330 Project 1

  imgDisplay.cpp

  Loads and displays image from file path.
*/
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

/*
  Reads and returns the img.

  std::string path is the file path of the img as a string.
*/
Mat readImgFile(string path) {
    Mat img = imread(path, IMREAD_ANYCOLOR);

    return img;
}

/*
  Displays image and exits on key stroke.

  cv::Mat img the image read from the file path.
*/
int displayImg(Mat img) {
    if ( img.empty() ) {
        return -1;
    }

    string windowName;
    windowName = "Image";

    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, img);

    char key;
    do {
        key = waitKey(0);
    } while (key != 'q');

    return 0;
}

/* 
  Main function that calls functions for reading img file, displaying the image, and listens for quit command.
*/
int main() {
    Mat img = readImgFile("../Montreal-Canadiens.jpeg");
    displayImg(img);

    return 0;
}