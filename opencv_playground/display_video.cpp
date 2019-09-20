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

int display_video() {
    
    VideoCapture cap;
    string fname;
    
    cout << "Enter the path to the video file: ";
    cin >> fname;
    
    namedWindow("Showing video");
    
    cap.open(fname);
    
    Mat frame;
    int i = 0;
    while (true) {
        cap >> frame;
        cout << "Displaying frame [" << i++ << "]." << endl;
        if (frame.empty()) {
            cout << "Video ended" << endl;
            break;
        }
        imshow("Showing video", frame);
        if (waitKey(33) >=0) { // Let's assume a frame rate of 30 FPS
            cout << "User interrupted" << endl;
            break;
        }
    }
    destroyWindow("Showing video");
    return 0;
}
