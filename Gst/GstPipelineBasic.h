/*
 * GstPipelineBasic.h
 *
 *  Created on: 18 avr. 2018
 *      Author: fawu
 */

#ifndef GST_GSTPIPELINEBASIC_H_
#define GST_GSTPIPELINEBASIC_H_

#include <iostream>
#include <thread>
#include <gst/gst.h>

class GstPipelineBasic
{
public:
	GstPipelineBasic();
	~GstPipelineBasic();

    void InitialisationPipelineWithString(std::string pipelineString);

    bool SetPipelineState(GstState state);
    GstState GetPipelineState();

    GstElement* GetElementByName(std::string element_name);



    GstElement *pipeline_;
    GstBus *m_bus;

private:
       void EnsureGstreamerInitialization();
       void FreePipeline();
       static void GstMessageWatch(GstBus *bus, GstMessage *message, GstPipelineBasic * pipeline);
       void RunningMainLoop();



       std::thread g_main_loop_thread;

};











#endif /* GST_GSTPIPELINEBASIC_H_ */
