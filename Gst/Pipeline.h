/*
 * Pipeline.h
 *
 *  Created on: 14 juin 2018
 *      Author: fawu
 */

#ifndef GST_PIPELINE_H_
#define GST_PIPELINE_H_

#include <string>
#include <sstream>

#define LINK " ! "

std::string CreateAppsinkPipeline()
{
    std::stringstream pipeline_string;

    pipeline_string
	<< "filesrc location=test.avi"
	<< LINK
	<< "decodebin"
	<< LINK
	<< "videoconvert"
	<< LINK
	<< "appsink caps=video/x-raw,format=BGR  name= app_sink";
    //<< "autovideosink";
    return pipeline_string.str();
}




std::string CreateAppsrcPipeline()
{
   std::stringstream pipeline_string;

   pipeline_string
   << "appsrc caps=video/x-raw,format=(string)BGR,width=(int)320,height=(int)288 name=app_src"
   << LINK
   << "videoconvert"
   << LINK
   << "autovideosink";

   return pipeline_string.str();

}

#endif /* GST_PIPELINE_H_ */


