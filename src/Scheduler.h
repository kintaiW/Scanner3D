#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <queue>

#include "Request.h"
#include "KKLock.h"

using namespace std;

class Scheduler
{

public:
  void push(Request & request);
  void poll(Request & request);
  Request & poll();
#if 1 
  inline bool hasTask(){ return !queueScheduler.empty();}
#else
  inline bool hasTask(){ return queueScheduler.size()==0? false:true;}
#endif
  inline int getSize(){return queueScheduler.size();}
private:
  queue<Request> queueScheduler;
};
#endif
