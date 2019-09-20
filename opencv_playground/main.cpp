//
//  main.cpp
//  opencv_playground
//
//  Created by HS on 9/19/19.
//  Copyright © 2019 HS. All rights reserved.
//

#include <iostream>

#include "display_image.hpp"
#include "display_video.hpp"

using namespace std;

int main(int argc, char** argv) {
    int choice;
    bool done = false;
    
    while (!done) {
        cout << "What would you like to do next?";
        cout << " (Options are 1: Display a video, 2: Display an image, 3: Quit) :" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                display_video();
                break;
            case 2:
                display_image();
                break;
            default:
                done = true;
                break;
        }
    }
    return 0;
}
