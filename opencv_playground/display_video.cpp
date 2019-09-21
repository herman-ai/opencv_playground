//
//  display_video.cpp
//  opencv_playground
//
//  Created by HS on 9/19/19.
//  Copyright © 2019 HS. All rights reserved.
//

#include <iostream>
#include "opencv2/opencv.hpp"

#include "display_video.hpp"

using namespace cv;
using namespace std;

int g_slider_position = 0;
int g_run = 1;
int g_sampling = 1;

VideoCapture g_cap;

void onTrackBarSlide(int pos, void *) {
    g_cap.set(CAP_PROP_POS_FRAMES, pos);
    cout << "In the event handler" << endl;
    g_run = 1;

}

int display_video() {
    
    VideoWriter writer;
    
    string fname;
    bool done = false;
    
    cout << "Enter the path to the video file: ";
    cin >> fname;
    
    namedWindow("VIDEO", WINDOW_AUTOSIZE);
    namedWindow("OUT", WINDOW_AUTOSIZE);
    
    
    g_cap.open(fname);
    
    int frames = (int) g_cap.get(CAP_PROP_FRAME_COUNT);
    int tmpw = (int) g_cap.get(CAP_PROP_FRAME_WIDTH);
    int tmph = (int) g_cap.get(CAP_PROP_FRAME_HEIGHT);
    int fps = (int) g_cap.get(CAP_PROP_FPS);
    
    
    writer.open("/Users/hermansahota/Downloads/SampleVideo_output.mp4", g_cap.get(CAP_PROP_FOURCC), fps, Size(tmpw, tmph));
    
    createTrackbar("Position", "VIDEO", &g_slider_position, frames, onTrackBarSlide);
    createTrackbar("Sampler", "VIDEO", &g_sampling, 8);
    
    cout << "Number of frames = " << frames << endl;
    cout << "Width of each frame = " << tmpw << endl;
    cout << "Height of each frame = " << tmph << endl;
    
    
    Mat frame, oframe;

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
        }
        imshow("VIDEO", frame);
        GaussianBlur(frame, oframe, Size(5,5), 3);
        GaussianBlur(oframe, oframe, Size(5,5), 3);
        GaussianBlur(oframe, oframe, Size(5,5), 3);
        GaussianBlur(oframe, oframe, Size(5,5), 3);
        for (int i=1; i<g_sampling; i*=2) {
            pyrDown(oframe, oframe);
        }
//        cvtCol1or(oframe, oframe, COLOR_BGR2GRAY);
//        Canny(frame, oframe, 10, 100);
//        logPolar(oframe, oframe, Point2f(frame.rows/2, frame.cols/2), 40, WARP_FILL_OUTLIERS);
//        pyrDown(oframe, oframe);
        
        imshow("OUT", oframe);
        writer << frame;
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
    destroyWindow("OUT");
    waitKey(1); // hack to make the window close on destroyWindow call
    return 0;
}
