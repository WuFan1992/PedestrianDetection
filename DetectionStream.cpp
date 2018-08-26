/*
 * DetectionStream.cpp
 *
 *  Created on: 13 juin 2018
 *      Author: fawu
 */


#include <gst/allocators/gstdmabuf.h>

#include "DetectionStream.h"
#include "Gst/Pipeline.h"
#include "Algo/PedestrianDetect.h"
#include <iostream>
#include <sys/mman.h>

DetectionStream::DetectionStream():
     is_streaming_(false){
	// TODO Auto-generated constructor stub

}

DetectionStream::~DetectionStream() {
	// TODO Auto-generated destructor stub
}


void DetectionStream::streamON()
{

	sink_pipeline_ = new GstAppsinkPipeline();
	sink_pipeline_->Initialize(CreateAppsinkPipeline());
	sink_pipeline_->SetPipelineState(GST_STATE_PLAYING);


	src_pipeline_= new GstAppsrcPipeline();
	src_pipeline_->Initialize(CreateAppsrcPipeline());
	src_pipeline_->SetPipelineState(GST_STATE_PLAYING);


	is_streaming_ = true;
	this->Process();


}

void DetectionStream::streamOFF()
{
   if(is_streaming_)
	   return;

    is_streaming_ = false;
   //Set the src and app pipeline in stop condition
   src_pipeline_->SetPipelineState(GST_STATE_PAUSED);
   sink_pipeline_->SetPipelineState(GST_STATE_PAUSED);

   delete src_pipeline_;
   delete sink_pipeline_;
}


void DetectionStream::Process()
{

   	GstSample* sample;
   	GstBuffer* buffer;
   	GstCaps* caps;
   	GstStructure *structure;
   	GstMemory *memory;

   	GstMapInfo *info;


   	//void * mapping_data;
   	guint8 *mapping_data;


   	int height, width, size;
   	//int fd ; // The descriptor of memory ,which will be used in the mmap64;

   	PedestrianDetect* ped_detect = new PedestrianDetect();

    while(is_streaming_)
    {

    	if(sink_pipeline_ ->GetIsNewFrameAvailble()) {

    	   sink_pipeline_ ->GetLatestSample(&sample);
    	   caps = gst_sample_get_caps(sample);
           buffer = gst_sample_get_buffer(sample);
           structure = gst_caps_get_structure(caps,0);

           gst_structure_get_int(structure, "height",&height);
           gst_structure_get_int(structure, "width", &width);

           size = gst_buffer_get_size(buffer);

           memory = gst_buffer_get_memory(buffer,1);

           printf("memory size is %d", memory->offset);

           gst_memory_map(memory, info, GST_MAP_READ);


           //mapping_data = info->data;

          // fd = gst_dmabuf_memory_get_fd(memory);



          // mapping_data = mmap64(NULL, size, PROT_READ | PROT_WRITE , MAP_SHARED, fd,0);

          //   ped_detect->Process(mapping_data,height,width);

           // image processing for the passanger detection

       //   munmap(mapping_data, size);

          gst_buffer_ref(buffer);
          src_pipeline_->SendBuff(buffer);
          sink_pipeline_->ReleaseFrameBuffer();


    	}

    }
    delete ped_detect;

}




