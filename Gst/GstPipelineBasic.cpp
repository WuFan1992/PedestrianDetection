/*
 * GstPipelineBasic.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: fawu
 */

#include "GstPipelineBasic.h"
#include <gst/gst.h>


GstPipelineBasic::GstPipelineBasic(void)
{
    EnsureGstreamerInitialization();

}

GstPipelineBasic::~GstPipelineBasic(void)
{

    FreePipeline();
}


void GstPipelineBasic::GstMessageWatch(GstBus *bus , GstMessage *msg, GstPipelineBasic *pipeline)
{
   /*Parse message*/
   if(msg!= NULL)
   {
	   GError *err;
	   gchar *debug_info;

	   switch (GST_MESSAGE_TYPE(msg)){
	     case GST_MESSAGE_ERROR:
	    	 gst_message_parse_error(msg,&err,&debug_info);
	    	 g_printerr("Error received from element %s : %s\n",GST_OBJECT_NAME(msg->src), err->message);
	    	 g_printerr("Debugging information: %s\n",debug_info? debug_info : "none");
	    	 g_clear_error(&err);
	    	 g_free(debug_info);
	    	 break;

	     case GST_MESSAGE_EOS:
	    	 g_print("End-of-stream Received\n");
	    	 break;

	     case GST_MESSAGE_STATE_CHANGED:
	    	 GstState old_state, new_state;
	    	 gst_message_parse_state_changed(msg,&old_state,&new_state,NULL);
	    	 g_print("Element %s changed state from %s to %s \n",
	    			 GST_OBJECT(msg->src),
					 gst_element_state_get_name(old_state),
					 gst_element_state_get_name(new_state));
	    	 break;

	     default:
	    	 /*We should not reach here*/
	    	 g_printerr("Unexpected message received. \n");
	    	 break;

	   }

	   gst_message_unref(msg);

	   }
   }

void GstPipelineBasic::RunningMainLoop()
{
    GMainLoop *loop = g_main_loop_new(NULL,FALSE);
    g_main_loop_run(loop);
}

bool GstPipelineBasic::SetPipelineState(GstState state)
{
     GstStateChangeReturn ret = gst_element_set_state(pipeline_,state);

     if(ret == GST_STATE_CHANGE_FAILURE)
     {
    	 g_printerr("Unable to set the pipeline to the playing state");
    	 gst_object_unref(pipeline_);
    	 return false;

     }
     return true;

}

GstState GstPipelineBasic::GetPipelineState()
{
    GstState new_state;
    gst_element_get_state(pipeline_, &new_state,NULL,GST_CLOCK_TIME_NONE);
    return new_state;
}


void GstPipelineBasic::InitialisationPipelineWithString(std::string pipelineString)
{

   /*Create Pipeline with the given string*/
    GError *error = NULL;
    pipeline_ = gst_parse_launch(pipelineString.c_str(),&error);


   /*Listen to bus and treat the information*/
    m_bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline_));
    gst_bus_add_watch(m_bus,(GstBusFunc)GstPipelineBasic::GstMessageWatch,this);

    //GstMessage *msg = gst_bus_timed_pop_filtered (m_bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

   /*Run the main loop to receive the message from the bus  */
    //g_main_loop_thread = std::thread(&GstPipelineBasic::RunningMainLoop,this);

}


void GstPipelineBasic::EnsureGstreamerInitialization()
{
    if(!gst_is_initialized())
    {
    	int argc = 0;
    	char **argv = new char*[2];

    	argv[argc++] = "--gst-version";
    	argv[argc++] = "--gst-debug-level=1";

    	gst_init(&argc, &argv);

        delete argv;

        {
        	guint major=0;
        	guint minor=0;
        	guint micro=0;
        	guint nano=0;

        	gst_version(&major,&minor, &micro,&nano);

        	std::cout<<"Gstreamer Version is "<< major << " . "<< minor << " . "<< micro << " . " << nano << std::endl;

        }
    }


}

/*Get the element which is the pipeline with his name*/
GstElement * GstPipelineBasic::GetElementByName(std::string element_name)
{
   return gst_bin_get_by_name(GST_BIN(pipeline_),element_name.c_str());

}



void GstPipelineBasic::FreePipeline()
{
	gst_element_set_state(pipeline_ , GST_STATE_NULL);
	gst_object_unref(m_bus);
	gst_object_unref(pipeline_);

}



