/*
 * PedestrianDetect.cpp
 *
 *  Created on: 23 juin 2018
 *      Author: fawu
 */
#include "PedestrianDetect.h"
#include <vector>


using namespace cv;

void PedestrianDetect::Process(void *framebuff, int height, int width)
{
    std::vector<Rect> detect_regions;

	Mat image_one_frame = Mat(height, width, CV_8UC3, (char*)framebuff, Mat::AUTO_STEP);

    /*
    HOGDescriptor hog(Size(64,128),Size(16,16),Size(8,8), Size(8,8),9);

    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    hog.detectMultiScale(image_one_frame, detect_regions,0,Size(8,8),Size(32,32),1.05,1);

    for(int i = 0; i< detect_regions.size(); i++)
    {
    	rectangle(image_one_frame, detect_regions[i], Scalar(255,255,0), 2);

    }

    waitKey();
    */
}



