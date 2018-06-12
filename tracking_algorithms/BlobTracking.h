#ifndef BLOB_TRACKING_H
#define BLOB_TRACKING_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "cvblob/cvblob.h"

class BlobTracking
{
private:
  bool firstTime;
  int minArea;
  int maxArea;
  
  bool debugTrack;
  bool debugBlob;
  bool showBlobMask;
  bool showOutput;

  cvb::CvTracks tracks;
  void saveConfig();
  void loadConfig();

public:
  BlobTracking();
  ~BlobTracking();

  void process(const cv::Mat &img_input, const cv::Mat &img_mask, cv::Mat &img_output);
  const cvb::CvTracks getTracks();
};

#endif // BLOB_TRACKING_H
