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

  void addImage(Request request);

private:
//  ImageQueue iq;
  vector<Request> targetRequests;
  Request request;
  Mat mat;
//  csc::Mutex i_mutex;
  //vector<Request> startRequests = new vector<Request>();
};

#endif
