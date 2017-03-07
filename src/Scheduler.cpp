#include "Scheduler.h"

csc::Mutex s_mutex;
queue<Request> queueScheduler;

void Scheduler::push(Request * request)
{
  queueScheduler.push(*request); 
}

Request* Scheduler::poll()
{
  if(queueScheduler.size() == 0) return (Request*)NULL;
  Request request = queueScheduler.front();
  queueScheduler.pop(); 
  return &request;
}
