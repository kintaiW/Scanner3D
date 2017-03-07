#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <queue>

#include "Request.h"
#include "KKLock.h"

using namespace std;

class Scheduler
{

public:
  void push(Request * request);
  Request * poll();
  
private:
  queue<Request> queueScheduler;
};
#endif
