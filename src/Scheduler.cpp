#include "Scheduler.h"

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

int Scheduler::poll(Request & request)
{
    if(queueScheduler.empty()) return -1;
    request = queueScheduler.front();
    queueScheduler.pop();
    return 0;
}
