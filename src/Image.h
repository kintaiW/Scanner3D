#ifndef _IMAGE_H
#define _IMAGE_H

#include <initializer_list>
#include <string>
#include <queue>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Request.h"

using namespace std;
using namespace cv;

struct ImageQueue
{
  queue<Request> paths;
};

class Image
{
public:
  Image();
  ~Image();

  void addImage(Request * request);
private:
  ImageQueue iq;
  Request request;
  Mat mat;
  //vector<Request> startRequests = new vector<Request>();
};

#endif
