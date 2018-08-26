/*
 * Detection.h
 *
 *  Created on: 23 juin 2018
 *      Author: fawu
 */

#ifndef ALGO_DETECTION_H_
#define ALGO_DETECTION_H_


#include <opencv2/opencv.hpp>

class Detection
{
public:
	Detection()
	{}
	~Detection()
	{}
	virtual void Process(void *framebuffer, int height, int width){}

};



#endif /* ALGO_DETECTION_H_ */
