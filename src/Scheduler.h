#ifndef _SCHEDULER_H
#define _SCHEDULER_H

//#include <vector>
#include <queue>
#include "Request.h"

using namespace std;

struct QueueRequest
{
  queue<Request> paths;
};

class Scheduler
{

public:
  void push(Request * request);
  inline QueueRequest getRequests(){return this->m;}
  
private:
  QueueRequest m;
};
#endif
