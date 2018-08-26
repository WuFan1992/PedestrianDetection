/*
 * GstAppsinkPipeline.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: fawu
 */

#include "GstAppsinkPipeline.h"
#include "GstPipeline.h"
#include "../common/common.h"




GstAppsinkPipeline::GstAppsinkPipeline():
                    retrieve_buff_(0),
                    current_buff_(0)
{


}


GstAppsinkPipeline::~GstAppsinkPipeline()
{

}



void GstAppsinkPipeline::Initialize(std::string pipelineInString)
{

    GstPipelineBasic::InitialisationPipelineWithString(pipelineInString);

    //Set Appsink
    appsink_ = GstPipelineBasic::GetElementByName(APPSINK_NAME);
    GstAppSinkCallbacks appsink_callback;
    appsink_callback.new_preroll = GstAppsinkPipeline::NewPrerollCallback;
    appsink_callback.new_sample = GstAppsinkPipeline::NewSampleCallback;
    appsink_callback.eos = GstAppsinkPipeline::EndofStream;
    gst_app_sink_set_drop(GST_APP_SINK(appsink_),true);
    gst_app_sink_set_callbacks(GST_APP_SINK(appsink_), &appsink_callback, this,(GDestroyNotify)GstAppsinkPipeline::DestoryCallBack);


}

GstFlowReturn GstAppsinkPipeline::NewPrerollCallback(GstAppSink *appsink, gpointer user_data)
{
     GstSample *sample_temp = gst_app_sink_pull_preroll(appsink);
     gst_sample_unref(sample_temp);
     return GST_FLOW_OK;

}


GstFlowReturn GstAppsinkPipeline::NewSampleCallback(GstAppSink *appsink, gpointer user_data)
{
	((GstAppsinkPipeline*)user_data)->ReceiveNewSample();
	return GST_FLOW_OK;


}

void GstAppsinkPipeline::EndofStream(GstAppSink *appsink, gpointer user_data)
{
   UNUSED(appsink);
   UNUSED(user_data);
}



/** This fonction is used to Get the latest sample stocked in CurrentBuff (get from the callback from the appsink)
 *  and put it in the sample
 *
 */

bool GstAppsinkPipeline::GetLatestSample(GstSample **sample)
{
    if(retrieve_buff_ == 0)
    {
    	if(current_buff_ != 0)
    	{
    		retrieve_buff_ = current_buff_;
    		current_buff_ = 0;
    		(*sample) = retrieve_buff_;
    	}

    }else
    {
    	(*sample) = NULL;
    	return false;

    }

	return true;

}

bool GstAppsinkPipeline::GetIsNewFrameAvailble()
{
   return (retrieve_buff_ == 0) && (current_buff_ != 0);

}

void GstAppsinkPipeline::ReceiveNewSample()
{

	GstSample *sample = gst_app_sink_pull_sample(GST_APP_SINK(appsink_));

   	if(sample)
   	{
   		if(current_buff_!= 0)
   		{
   			gst_sample_unref(current_buff_);

   		}
   	current_buff_ = sample;
   	}
}

void GstAppsinkPipeline::DestoryCallBack(gpointer user_data)
{
 UNUSED(user_data);
// Do nothing
}


void GstAppsinkPipeline::ReleaseFrameBuffer()
{
   if(retrieve_buff_)
   {
	   gst_sample_unref(retrieve_buff_);
   }
   retrieve_buff_ = 0;
}

void GstAppsinkPipeline::set_is_streaming()
{
	if (current_buff_)
	        gst_sample_unref(current_buff_);
	current_buff_ = 0;

}

