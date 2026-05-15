/*
  Drew Hill
  Summer 2026 
  CS5330 Project 1

  vidDisplay.cpp

  Displays live video from a camera.
*/
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

/*
*/
bool keyStrokeHandler(char key) {
        if ( key == 'q' ) {
            return true;
        } else {
            return false;
        }
}

/*
  
*/
int main(int argc, char *argv[]) {
    VideoCapture *cap;
    Mat frame;

    cap = new VideoCapture(0);

    if ( !cap->isOpened() ) {
        printf("Camera can not be opened!\n");
        return -1;
    }

    Size refS(
        (int) cap->get(CAP_PROP_FRAME_WIDTH),
        (int) cap->get(CAP_PROP_FRAME_HEIGHT)
    );

    printf("Video size: %d x %d \n", refS.height, refS.width);

    namedWindow("Video", 1);

    for(;;) {
        *cap >> frame;

        if ( frame.empty() ) {
            printf("Frame is empty");
            break;
        }

        imshow("Video", frame);

        char key = waitKey(10);
        if ( keyStrokeHandler(key) == true ) {
            break;
        } 
    }

    delete cap;
    return 0;
}