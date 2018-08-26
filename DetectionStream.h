/*
 * DetectionStream.h
 *
 *  Created on: 13 juin 2018
 *      Author: fawu
 */

#ifndef DETECTIONSTREAM_H_
#define DETECTIONSTREAM_H_

#include "Gst/GstAppsinkPipeline.h"
#include "Gst/GstAppsrcPipeline.h"

class DetectionStream {
public:
	DetectionStream();
	virtual ~DetectionStream();

	void streamON();
	void streamOFF();
	void Process();

private:
	GstAppsinkPipeline *sink_pipeline_;
    GstAppsrcPipeline *src_pipeline_;
	bool is_streaming_;


};

#endif /* DETECTIONSTREAM_H_ */
