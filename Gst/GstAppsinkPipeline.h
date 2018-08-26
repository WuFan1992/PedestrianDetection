/*
 * GstAppsinkPipeline.h
 *
 *  Created on: 20 avr. 2018
 *      Author: fawu
 */


#include <gst/app/gstappsink.h>

#ifndef GST_GSTAPPSINKPIPELINE_H_
#define GST_GSTAPPSINKPIPELINE_H_

#include "GstPipelineBasic.h"



class GstAppsinkPipeline : public GstPipelineBasic
{

public :
	GstAppsinkPipeline();
	~GstAppsinkPipeline();

	void Initialize(std::string pipeline_with_string);


	bool GetLatestSample(GstSample **sample);
	void ReleaseFrameBuffer();
	bool GetIsNewFrameAvailble();

	 void set_is_streaming();


private:

   GstSample *retrieve_buff_;  // the buffer to the image process , set 0 when one process is finished
   GstSample *current_buff_;   // the buffer from appsink sample, set 0 when pass his buffer to retrieveBuff


   // In the process , it need to pass currentBuff to retrieveBuff and then set the currentBuff to 0 to wait it from sample

      GstElement *appsink_;


   void ReceiveNewSample();

   static GstFlowReturn  NewPrerollCallback(GstAppSink *appsink, gpointer user_data);
   static GstFlowReturn  NewSampleCallback(GstAppSink *appsink, gpointer user_data);
   static void EndofStream(GstAppSink *appsink, gpointer user_data);
   static void DestoryCallBack(gpointer user_data);

};










#endif /* GST_GSTAPPSINKPIPELINE_H_ */
