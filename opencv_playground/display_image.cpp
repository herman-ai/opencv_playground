//
//  display_image.cpp
//  opencv_playground
//
//  Created by HS on 9/19/19.
//  Copyright © 2019 HS. All rights reserved.
//

#include "display_image.hpp"


#include <iostream>
#include "opencv2/highgui/highgui.hpp"

/*
 This program displays an image loaded from the disk.
 */


using namespace cv;
using namespace std;

int display_image(int argc, char** argv) {
    if (argc < 2) {
        cout << "Fewer args than expected" << endl;
        return -1;
    }
    Mat image = imread(argv[1], 0);
    if (image.empty()) {
        cout << "Could not load the image" << endl;
        return -1;
    }
    
    //create a gui window:
    namedWindow("Window name", WINDOW_AUTOSIZE);
    imshow("Window name", image);
    
    waitKey(0);
    destroyWindow("Window name");
    return 0;
}
