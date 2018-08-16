﻿#include "ObjectCouting.h"

namespace FAV1
{
  IplImage* img_input1 = 0;
  IplImage* img_input2 = 0;
  int roi_x0 = 0;
  int roi_y0 = 0;
  int roi_x1 = 0;
  int roi_y1 = 0;
  int numOfRec = 0;
  int startDraw = 0;
  bool roi_defined = false;
  bool use_roi = true;
}

ObjectCouting::ObjectCouting(QString hostname): firstTime(true), showOutput(true), key(0), countAB(0), countBA(0), showAB(0), serverApi{hostname}
{
    //cv::namedWindow("Object Counting", cv::WINDOW_NORMAL);
    std::cout << "ObjectCouting()" << std::endl;
}

ObjectCouting::~ObjectCouting()
{
    std::cout << "Total A->B: " << countAB << " | Total B->A: " << countBA << endl;
    std::cout << "~ObjectCouting()" << std::endl;
}

void ObjectCouting::setInput(const Mat &imgInput)
{
  //i.copyTo(img_input);
  img_input = imgInput;
}

void ObjectCouting::setTracks(const cvb::CvTracks &srcTracks)
{
  tracks = srcTracks;
}

ObjectPosition ObjectCouting::getObjectPosition(const CvPoint2D64f centroid)
{
  ObjectPosition objectPosition = ObjectPosition::VP_NONE;

  if(laneOrientation == LaneOrientation::LO_HORIZONTAL)
  {
    if(centroid.x < FAV1::roi_x0)
    {
      putText(img_input, "STATE: A", Point(10,img_h/2), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      objectPosition = ObjectPosition::VP_A;
    }
    
    if(centroid.x > FAV1::roi_x0)
    {
      putText(img_input, "STATE: B", Point(10,img_h/2), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      objectPosition = ObjectPosition::VP_B;
    }
  }

  if(laneOrientation == LaneOrientation::LO_VERTICAL)
  {
    if(centroid.y > FAV1::roi_y0)
    {
      putText(img_input, "STATE: A", Point(10,img_h/2), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      objectPosition = ObjectPosition::VP_A;
    }
    
    if(centroid.y < FAV1::roi_y0)
    {
      putText(img_input, "STATE: B", Point(10,img_h/2), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      objectPosition = ObjectPosition::VP_B;
    }
  }

  return objectPosition;
}

void ObjectCouting::process()
{
  if(img_input.empty())
    return;

  img_w = img_input.size().width;
  img_h = img_input.size().height;

  loadConfig();

  //--------------------------------------------------------------------------

  if(FAV1::use_roi == true && FAV1::roi_defined == false && firstTime == true)
  {
    do
    {
      putText(img_input, "Please, set the counting line", cv::Point(10,15), cv::FONT_HERSHEY_PLAIN, 1, Scalar(0,0,255));
      //imshow("Object Couting", img_input);
      //FAV1::img_input1 = new IplImage(img_input);
      //cvSetMouseCallback("VehicleCouting", FAV1::VehicleCouting_on_mouse, NULL);
      //key = waitKey(0);
      //delete FAV1::img_input1;

      if(FAV1::roi_defined)
      {
        std::cout << "Counting line defined (" << FAV1::roi_x0 << "," << FAV1::roi_y0 << "," << FAV1::roi_x1 << "," << FAV1::roi_y1 << ")" << std::endl;
        break;
      }
      else
        std::cout << "Counting line undefined!" << std::endl;
    }while(1);
  }

  if(FAV1::use_roi == true && FAV1::roi_defined == true)
    line(img_input, Point(FAV1::roi_x0,FAV1::roi_y0), Point(FAV1::roi_x1,FAV1::roi_y1), Scalar(0,0,255));
  
  bool ROI_OK = false;
  
  if(FAV1::use_roi == true && FAV1::roi_defined == true)
    ROI_OK = true;

  if(ROI_OK)
  {
    laneOrientation = LaneOrientation::LO_NONE;

    if(abs(FAV1::roi_x0 - FAV1::roi_x1) < abs(FAV1::roi_y0 - FAV1::roi_y1))
    {
      if(!firstTime)
        putText(img_input, "HORIZONTAL", Point(10,15), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      laneOrientation = LaneOrientation::LO_HORIZONTAL;

      putText(img_input, "(A)", Point(FAV1::roi_x0-32,FAV1::roi_y0), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      putText(img_input, "(B)", Point(FAV1::roi_x0+12,FAV1::roi_y0), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
    }

    if(abs(FAV1::roi_x0 - FAV1::roi_x1) > abs(FAV1::roi_y0 - FAV1::roi_y1))
    {
      if(!firstTime)
        putText(img_input, "VERTICAL", Point(10,15), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      laneOrientation = LaneOrientation::LO_VERTICAL;

      putText(img_input, "(A)", Point(FAV1::roi_x0,FAV1::roi_y0+22), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
      putText(img_input, "(B)", Point(FAV1::roi_x0,FAV1::roi_y0-12), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
    }
  }

  //--------------------------------------------------------------------------

  for(map<cvb::CvID,cvb::CvTrack*>::iterator it = tracks.begin() ; it != tracks.end(); it++)
  {
    //std::cout << (*it).first << " => " << (*it).second << std::endl;
    cvb::CvID id = (*it).first;
    cvb::CvTrack* track = (*it).second;

    CvPoint2D64f centroid = track->centroid;
    /*
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "0)id:" << id << " (" << centroid.x << "," << centroid.y << ")" << std::endl;
    std::cout << "track->active:" << track->active << std::endl;
    std::cout << "track->inactive:" << track->inactive << std::endl;
    std::cout << "track->lifetime:" << track->lifetime << std::endl;
    */
    
    //----------------------------------------------------------------------------

    if(track->inactive == 0)
    {
      if(positions.count(id) > 0)
      {
        map<cvb::CvID, ObjectPosition>::iterator it2 = positions.find(id);
        ObjectPosition old_position = it2->second;

        ObjectPosition current_position = getObjectPosition(centroid);

        if(current_position != old_position)
        {
          if(old_position == ObjectPosition::VP_A && current_position == ObjectPosition::VP_B)
          {
              countAB++;
              qDebug() << "Passenger form A->B: " << countAB;
              serverApi.updateLatLongBus(3, countBA, countBA, countAB, countAB);
          }

          if(old_position == ObjectPosition::VP_B && current_position == ObjectPosition::VP_A)
          {
              countBA++;
              qDebug() << "Passenger form B->A: " << countBA;
              serverApi.updateLatLongBus(3, countBA, countBA, countAB, countAB);
          }
          positions.erase(positions.find(id));
        }
      }
      else
      {
        ObjectPosition vehiclePosition = getObjectPosition(centroid);

        if(vehiclePosition != ObjectPosition::VP_NONE)
          positions.insert(std::pair<cvb::CvID, ObjectPosition>(id,vehiclePosition));
      }
    }
    else
    {
      if(positions.count(id) > 0)
        positions.erase(positions.find(id));
    }

    //----------------------------------------------------------------------------

    if(points.count(id) > 0)
    {
      map<cvb::CvID, vector<CvPoint2D64f>>::iterator it2 = points.find(id);
      vector<CvPoint2D64f> centroids = it2->second;
      
      vector<CvPoint2D64f> centroids2;
      if(track->inactive == 0 && centroids.size() < 30)
      {
        centroids2.push_back(centroid);
      
        for(vector<CvPoint2D64f>::iterator it3 = centroids.begin() ; it3 != centroids.end(); it3++)
        {
          centroids2.push_back(*it3);
        }

        for(vector<CvPoint2D64f>::iterator it3 = centroids2.begin() ; it3 != centroids2.end(); it3++)
        {
          circle(img_input, Point((*it3).x,(*it3).y), 3, Scalar(255,255,255), -1);
        }
      
        points.erase(it2);
        points.insert(std::pair<cvb::CvID, vector<CvPoint2D64f>>(id,centroids2));
      }
      else
      {
        points.erase(it2);
      }
    }
    else
    {
      if(track->inactive == 0)
      {
        vector<CvPoint2D64f> centroids;
        centroids.push_back(centroid);
        points.insert(std::pair<cvb::CvID, vector<CvPoint2D64f>>(id,centroids));
      }
    }

    //cv::waitKey(0);
  }
  
  //--------------------------------------------------------------------------

  std::string countABstr = "A->B: " + std::to_string(countAB);
  std::string countBAstr = "B->A: " + std::to_string(countBA);

  if(showAB == 0)
  {
    putText(img_input, countABstr, Point(10, img_h - 60), cv::FONT_HERSHEY_DUPLEX, 1, Scalar(0, 100, 0));
    putText(img_input, countBAstr, Point(10, img_h - 8), cv::FONT_HERSHEY_DUPLEX, 1, Scalar(0, 100, 0));
  }
  
  if(showAB == 1)
    putText(img_input, countABstr, Point(10, img_h - 8), cv::FONT_HERSHEY_DUPLEX, 1, Scalar(0, 100, 0));
  
  if(showAB == 2)
    putText(img_input, countBAstr, Point(10, img_h - 8), cv::FONT_HERSHEY_DUPLEX, 1, Scalar(0, 100, 0));

  if(showOutput)
    imshow("Object Counting", img_input);

  if(firstTime)
    saveConfig();

  firstTime = false;
}

void ObjectCouting::saveConfig()
{
  CvFileStorage* fs = cvOpenFileStorage("config/VehicleCouting.xml", 0, CV_STORAGE_WRITE);

  cvWriteInt(fs, "showOutput", showOutput);
  cvWriteInt(fs, "showAB", showAB);
  
  cvWriteInt(fs, "fav1_use_roi", FAV1::use_roi);
  cvWriteInt(fs, "fav1_roi_defined", FAV1::roi_defined);
  cvWriteInt(fs, "fav1_roi_x0", FAV1::roi_x0);
  cvWriteInt(fs, "fav1_roi_y0", FAV1::roi_y0);
  cvWriteInt(fs, "fav1_roi_x1", FAV1::roi_x1);
  cvWriteInt(fs, "fav1_roi_y1", FAV1::roi_y1);
  
  cvReleaseFileStorage(&fs);
}

void ObjectCouting::loadConfig()
{
  CvFileStorage* fs = cvOpenFileStorage("config/VehicleCouting.xml", 0, CV_STORAGE_READ);

  showOutput = cvReadIntByName(fs, 0, "showOutput", true);
  showAB = cvReadIntByName(fs, 0, "showAB", 1);
  
  FAV1::use_roi = cvReadIntByName(fs, 0, "fav1_use_roi", true);
  FAV1::roi_defined = cvReadIntByName(fs, 0, "fav1_roi_defined", false);
  FAV1::roi_x0 = cvReadIntByName(fs, 0, "fav1_roi_x0", 0);
  FAV1::roi_y0 = cvReadIntByName(fs, 0, "fav1_roi_y0", 0);
  FAV1::roi_x1 = cvReadIntByName(fs, 0, "fav1_roi_x1", 0);
  FAV1::roi_y1 = cvReadIntByName(fs, 0, "fav1_roi_y1", 0);
  
  cvReleaseFileStorage(&fs);
}
