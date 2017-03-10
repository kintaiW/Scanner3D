#include "Scheduler.h"

csc::Mutex s_mutex;
queue<Request> queueScheduler;

void Scheduler::push(Request & request)
{
  queueScheduler.push(request); 
}

Request& Scheduler::poll()
{
  Request * request = new Request(queueScheduler.front().file.c_str());
  queueScheduler.pop(); 
  return *request;
}

void Scheduler::poll(Request & request)
{
  request = queueScheduler.front();
  queueScheduler.pop();
}
