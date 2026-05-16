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
int saveVid(VideoCapture *cap, std::string filename) {
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
        output << frame;

        char key = waitKey(10);
        if (key == 'q') {
            break;
        }
    }
    return 0;
}

// /*
//   Handles keystrokes.

//   char key the key stroke used to envoke action.
// */
// bool keyStrokeHandler(char key, VideoCapture *cap) {
//         if ( key == 'q' ) {
//             return true;
//         } else {
//             return false;
//         }
// }

// /*
//   Displays the live video from local camera.

//   VideoCapture *cap a pointer to the VideoCapture object 
// */
// int displayVideo(VideoCapture *cap) {
//     Mat frame;
//     std::string windowName = "Video";
    
//     namedWindow(windowName, 1);

//     for(;;) {
//         windowName = "Video1";
//         *cap >> frame;

//         if ( frame.empty() ) {
//             printf("Frame is empty");
//             break;
//         }

//         imshow(windowName, frame);

//         char key = waitKey(10);
//         if ( key == 'q' ) {
//             break;
//         } 
//     }
//     return 0;
// }

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
            saveVid(cap, "./Test2");
        }
    }

    delete cap;
    return 0;
}