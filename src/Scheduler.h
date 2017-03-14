#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <queue>

#include "Request.h"

using namespace std;

class Scheduler
{

public:
  bool isValid = true;
  void push(Request & request);
  int poll(Request & request);
  Request & poll();
  inline bool hasTask(){ return !queueScheduler.empty();}
  inline int getSize(){return queueScheduler.size();}
private:
  queue<Request> queueScheduler;
};
#endif
