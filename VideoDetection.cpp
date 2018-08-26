//============================================================================
// Name        : VideoDetection.cpp
// Author      : Fan WU
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <gst/gst.h>
#include "DetectionStream.h"

int main(int argc, char *argv[])
{
  gst_init (&argc, &argv);

  DetectionStream detection_stream;
  detection_stream.streamON();

  std::cout << "Enter to leave!" << std::endl;

  detection_stream.streamOFF();



   return 0;
}
