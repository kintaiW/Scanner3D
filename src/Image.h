#ifndef _IMAGE_H
#define _IMAGE_H

#include <initializer_list>
#include <string>
#include <vector>
//#include <queue>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Request.h"
#include "KKLock.h"

using namespace std;
using namespace cv;

//struct ImageQueue
//{
//  queue<Request> paths;
//};

class Image
{
public:
  Image();
  ~Image();

  Image(string & filename);
  Image( Request & filename);
  void addImage(Request request);
  void addImage(int number);
  void addImage(string folder,int number);
  Mat image_new(string& filename);
  void show();
  inline const char * getName(){return this->filename.c_str();}
  inline vector<Request> getTargetRequests(){return this->targetRequests;}
  inline Request getTargetRequest(){return this->targetRequest;}
  //opencv
  Mat getROI();
  Image captureLaser();
  int centerOfMass();
private:
  vector<Request> targetRequests;
  Request targetRequest;
  Request request;
  string filename;
  Mat mat;
};
bool compareContourAreas(vector<Point> contour1, vector<Point> contour2);
#endif
