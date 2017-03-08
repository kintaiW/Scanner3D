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
  Image image;
  Scheduler scheduler;

  int threadNum = 1;
  static pthread_mutex_t command_mutex_;
  static pthread_cond_t command_cond_;
public:
  Scanner();
//  Scanner(Processor p);
//  ~Scanner();

  Scanner test1();
  //Scanner test2();
  Scanner create(void (*func) (Image&));
  Scanner create(Processor p);
  Scanner addPath(string path);
  Scanner addPath(initializer_list<string> lst);

  void bind();
  void run();
  void * loop();
  void processRequest(Request * request);
  void waitTime(int time);
  void checkThread();
  Scanner thread(int threadNum);
private:
  Processor p;
  void addRequest(Request * request);
  //thread pool function
  pthread_attr_t attr;
  
  static struct timeval now;
  static struct timespec outtime;
  static void startThread(Request * request);
  static void initializeThreads();
  static void * process(void * arg);
  static void addThread();
  static void deleteThread();
  static bool shutdown_;
  static int icurr_thread_num_;
  static map<pthread_t,int> thread_id_map_;
};

#endif
