/*
 * GstAppsrcPipeline.cpp
 *
 *  Created on: 15 juin 2018
 *      Author: fawu
 */

#include "GstAppsrcPipeline.h"
#include "../common/common.h"
#include "GstPipeline.h"

GstAppsrcPipeline::GstAppsrcPipeline():need_data_(false) {
	// TODO Auto-generated constructor stub

}

GstAppsrcPipeline::~GstAppsrcPipeline() {
	// TODO Auto-generated destructor stub
}

void GstAppsrcPipeline::Initialize(std::string pipelineInString)
{
	GstPipelineBasic::InitialisationPipelineWithString(pipelineInString);

	appsrc_ = GstPipelineBasic::GetElementByName(APPSRC_NAME);

	GstAppSrcCallbacks appsrc_callback;
	appsrc_callback.need_data = GstAppsrcPipeline::NeedDataCallBack;
	appsrc_callback.enough_data = GstAppsrcPipeline::EnoughDataCallBack;
	appsrc_callback.seek_data = GstAppsrcPipeline::SeekDataCallBack;

    gst_app_src_set_callbacks(GST_APP_SRC(appsrc_), &appsrc_callback, this, (GDestroyNotify)GstAppsrcPipeline::DestroyCallBack);

}

void GstAppsrcPipeline::DestroyCallBack(GstAppsrcPipeline* appsrc_pipeline)
{
    // Do Nothing

}


bool GstAppsrcPipeline::SendBuff(GstBuffer* buffer)
{
   if(buffer)
	   if(need_data_)
	   {
		   GstFlowReturn ret = gst_app_src_push_buffer((GstAppSrc*)appsrc_, buffer);

	   }

   return true;
}

 void GstAppsrcPipeline::NeedDataCallBack(GstAppSrc *src, guint length, gpointer user_data)
{
    GstAppsrcPipeline* appsrc_pipeline = (GstAppsrcPipeline*)(user_data);
    appsrc_pipeline->need_data_ = true;

    UNUSED(src);
    UNUSED(length);

}

void GstAppsrcPipeline::EnoughDataCallBack(GstAppSrc *src, gpointer user_data)
{
	GstAppsrcPipeline* appsrc_pipeline = (GstAppsrcPipeline*)(user_data);
	appsrc_pipeline->need_data_ = false;

	UNUSED(src);
}

gboolean  GstAppsrcPipeline::SeekDataCallBack(GstAppSrc *src, guint64 offset, gpointer user_data)
{
	UNUSED(src);
	UNUSED(offset);
	UNUSED(user_data);
	return true;
}
