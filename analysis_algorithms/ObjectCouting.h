#ifndef OBJECT_COUNTING_H
#define OBJECT_COUNTING_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>
#include "../tracking_algorithms/cvblob/cvblob.h"
using std::vector;
using std::map;
using cv::Mat;
using cv::putText;
using cv::line;
using cv::circle;
using cv::waitKey;
enum class LaneOrientation
{
  LO_NONE       = 0,
  LO_HORIZONTAL = 1,
  LO_VERTICAL   = 2
};

enum class ObjectPosition
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
  Mat img_input;
  cvb::CvTracks tracks;
  map<cvb::CvID, vector<CvPoint2D64f> > points;
  LaneOrientation laneOrientation;
  map<cvb::CvID, ObjectPosition> positions;
  long countAB;
  long countBA;
  int img_w;
  int img_h;
  int showAB;

public:
  ObjectCouting();
  ~ObjectCouting();

  void setInput(const Mat &imgInput);
  void setTracks(const cvb::CvTracks &srcTracks);
  void process();

private:
  ObjectPosition getVehiclePosition(const CvPoint2D64f centroid);

  void saveConfig();
  void loadConfig();
};
#endif // OBJECT_COUNTING_H
