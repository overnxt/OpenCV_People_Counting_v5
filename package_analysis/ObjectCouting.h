#ifndef OBJECT_COUNTING_H
#define OBJECT_COUNTING_H

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv/cv.hpp>
#include "../package_tracking/cvblob/cvblob.h"
enum LaneOrientation
{
  LO_NONE       = 0,
  LO_HORIZONTAL = 1,
  LO_VERTICAL   = 2
};

enum ObjectPosition
{
  VP_NONE = 0,
  VP_A  = 1,
  VP_B  = 2
};

class ObjectCouting
{
private:
  bool firstTime;
  bool showOutput;
  int key;
  cv::Mat img_input;
  cvb::CvTracks tracks;
  std::map<cvb::CvID, std::vector<CvPoint2D64f> > points;
  LaneOrientation laneOrientation;
  std::map<cvb::CvID, ObjectPosition> positions;
  long countAB;
  long countBA;
  int img_w;
  int img_h;
  int showAB;

public:
  ObjectCouting();
  ~ObjectCouting();

  void setInput(const cv::Mat &i);
  void setTracks(const cvb::CvTracks &t);
  void process();

private:
  ObjectPosition getVehiclePosition(const CvPoint2D64f centroid);

  void saveConfig();
  void loadConfig();
};
#endif // OBJECT_COUNTING_H
