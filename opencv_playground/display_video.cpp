//
//  display_video.cpp
//  opencv_playground
//
//  Created by HS on 9/19/19.
//  Copyright © 2019 HS. All rights reserved.
//

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "display_video.hpp"

using namespace cv;
using namespace std;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0;

VideoCapture g_cap;

void onTrackBarSlide(int pos, void *) {
    g_cap.set(CAP_PROP_POS_FRAMES, pos);
    if (!g_dontset) {
        g_run = 1;
    }
    g_dontset = 0;
}

int display_video() {
    
    string fname;
    bool done = false;
    
    cout << "Enter the path to the video file: ";
    cin >> fname;
    
    namedWindow("VIDEO", WINDOW_AUTOSIZE);
    
    
    g_cap.open(fname);
    
    int frames = (int) g_cap.get(CAP_PROP_FRAME_COUNT);
    int tmpw = (int) g_cap.get(CAP_PROP_FRAME_WIDTH);
    int tmph = (int) g_cap.get(CAP_PROP_FRAME_HEIGHT);
    
    createTrackbar("Position", "VIDEO", &g_slider_position, frames, onTrackBarSlide);
    
    cout << "Number of frames = " << frames << endl;
    cout << "Width of each frame = " << tmpw << endl;
    cout << "Height of each frame = " << tmph << endl;
    
    
    Mat frame;

    while (!done) {
        if (g_run != 0) {
            g_cap >> frame;
            int pos = (int)g_cap.get(CAP_PROP_POS_FRAMES);
            cout << "Displaying frame [" << pos << "]." << endl;
            if (frame.empty()) {
                cout << "Video ended" << endl;
                break;
            }
            setTrackbarPos("Position", "VIDEO", pos);
            g_run--;
            g_dontset = 1;
        }
        imshow("VIDEO", frame);
        char ch = waitKey(33);
        ch = tolower(ch);
        switch (ch) {
            case 's' :
                cout << "Single stepping through the video" << endl;
                g_run = 1;
                break;
            case 'r':
                g_run = -1;
                cout << "Run mode" << endl;
                break;
            case 27:    //escape key
                cout << "User wants to stop video" << endl;
                done = true;
                break;
        }
    }
    destroyWindow("VIDEO");
    return 0;
}
