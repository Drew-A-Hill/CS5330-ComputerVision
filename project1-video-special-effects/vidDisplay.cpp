/*
  Drew Hill
  Summer 2026 
  CS5330 Project 1

  vidDisplay.cpp

  Displays live video from a camera.
*/
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace cv;

Size getSize(VideoCapture *cap) {
    Size refS(
        cap->get(CAP_PROP_FRAME_WIDTH),
        cap->get(CAP_PROP_FRAME_HEIGHT)
    );

    return refS;
}

/*
*/
int saveVid(VideoCapture *cap, std::string filename, std::string windowName) {
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
    std::string filepath = filename + ".avi";

    Size size = getSize(cap);

    VideoWriter output;
    output.open(filepath, codec, cap->get(CAP_PROP_FPS), size, true);

    if ( !output.isOpened() ) {
        printf("Could Not Open Output Video");
        return -1;
    }

    Mat frame;

    for (;;) {
        *cap >> frame;

        if ( frame.empty() ) {
            break;
        }
        setWindowTitle(windowName, "Recording");
        imshow(windowName, frame);
        output << frame;

        char key = waitKey(10);
        if (key == 'q') {
            setWindowTitle(windowName, windowName);
            break;
        }
    }
    return 0;
}

/* 
*/
int main(int argc, char *argv[]) {
    VideoCapture *cap;

    cap = new VideoCapture(0);                                     // Creates new video capture object and opens device

    if ( !cap->isOpened() ) {
        printf("Camera can not be opened!\n");
        return -1;
    }

    // Gets width and height properties of the image
    Size size = getSize(cap);

    printf("Video size: %d x %d \n", size.height, size.width);
    
    Mat frame;
    std::string windowName = "Video";
    
    namedWindow(windowName, 1);

    for(;;) {
        windowName = "Video1";
        *cap >> frame;

        if ( frame.empty() ) {
            printf("Frame is empty");
            break;
        }

        imshow(windowName, frame);

        char key = waitKey(10);
        if ( key == 'q' ) {
            break;

        } else if (key == 's') {
            saveVid(cap, "../Test5", windowName);

        }
    }

    delete cap;
    return 0;
}