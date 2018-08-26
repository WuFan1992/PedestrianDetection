/*
 * PedestrianDetect.h
 *
 *  Created on: 23 juin 2018
 *      Author: fawu
 */

#ifndef ALGO_PEDESTRIANDETECT_H_
#define ALGO_PEDESTRIANDETECT_H_

#include "Detection.h"

class PedestrianDetect: public Detection
{
public:
	PedestrianDetect(){}
	~PedestrianDetect(){}

	void Process(void *framebuff, int height, int width);

};



#endif /* ALGO_PEDESTRIANDETECT_H_ */
