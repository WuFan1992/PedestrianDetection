/*
 * GstAppsrcPipeline.h
 *
 *  Created on: 15 juin 2018
 *      Author: fawu
 */

#include <gst/app/gstappsrc.h>

#ifndef GST_GSTAPPSRCPIPELINE_H_
#define GST_GSTAPPSRCPIPELINE_H_

#include "GstPipelineBasic.h"


class GstAppsrcPipeline : public GstPipelineBasic
{
public:
	GstAppsrcPipeline();
	virtual ~GstAppsrcPipeline();

	void Initialize(std::string pipeline_with_string);
	bool SendBuff(GstBuffer * buff);

private:
	bool need_data_;
	GstElement *appsrc_;

	static void NeedDataCallBack(GstAppSrc *src, guint length, gpointer user_data);
    static void EnoughDataCallBack(GstAppSrc *src, gpointer user_data);
    static gboolean SeekDataCallBack(GstAppSrc *src, guint64 offset, gpointer user_data);
	static void DestroyCallBack(GstAppsrcPipeline *appsrc_pipeline);


};

#endif /* GST_GSTAPPSRCPIPELINE_H_ */
