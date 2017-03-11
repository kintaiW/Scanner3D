#ifndef _SCANNER_H
#define _SCANNER_H

#include <initializer_list>
#include <string>
#include <map>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>

#include "Image.h"
#include "Request.h"
#include "Scheduler.h"
#include "PointProcessor.h"

using namespace std;

typedef PointProcessor * Processor;
#define THREAD_NUM 5

class Scanner
{
protected:
  Scheduler scheduler;

  int threadNum = 1;
  static pthread_mutex_t command_mutex_;
  static pthread_cond_t command_cond_;
public:
  Scanner();
  Scanner create(Processor p);
  Scanner addPath(string path);
  Scanner addPath(initializer_list<string> lst);

  void run();
  void waitTime(int time);
  void checkThread();
  void extractAndAddRequest(Image &image);
  Scanner thread(int threadNum);
  int stopAll();
  int pollRequest(Request & request);
  int tasks = 60;
private:
  Processor p;
  void addRequest(Request & request);
  //thread pool function
  pthread_attr_t attr;
  
  static struct timeval now;
  static struct timespec outtime;
  static void initializeThreads(Scanner & scanner);
  static void * process(void * arg);
  static bool shutdown_;
  static int icurr_thread_num_;
  static map<pthread_t,int> thread_id_map_;
};

#endif
