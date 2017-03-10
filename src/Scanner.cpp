#include "Scanner.h"

pthread_mutex_t Scanner::command_mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Scanner::command_cond_ = PTHREAD_COND_INITIALIZER;
bool Scanner::shutdown_ = false;
int Scanner::icurr_thread_num_ = THREAD_NUM;
map<pthread_t,int> Scanner::thread_id_map_;
struct timeval Scanner::now;
struct timespec Scanner::outtime;
Processor processor;
Scheduler scheduler;

/*
 *
 * */
Scanner::Scanner(){}

Scanner Scanner::test1(){printf("test1 success!");return *this;}

Scanner Scanner::create(void(*func)(Image & image))
{
  return *this;
}

Scanner Scanner::create(Processor p)
{
  processor = p;
  return *this;
}

void * Scanner::process(void * arg)
{
  pthread_detach(pthread_self());
  printf("pid: %d\n",(unsigned int)pthread_self());
#if 0
  Image image(*(string *)arg);
#else
  printf("process %s\n",(*(((Task *)arg)->path)).c_str());
  Image image(*(((Task *)arg)->path));
#endif
//  ((Scanner*)(((Task *)arg)->obj))->waitTime(1);
  processor->process(image);
  ((Scanner*)(((Task *)arg)->obj))->extractAndAddRequest(image);
 // extractAndAddRequest(image);
  pthread_exit(NULL);
}
/*
 *add image to scanner
 *
 *@param string_list string
 *@return this
 **/
Scanner Scanner::addPath(string path)
{
  Request request(path);
  addRequest(request);
  return *this;
}

//Scanner Scanner::addPath(initializer_list<string> lst)
//{
//  for(auto beg=lst.begin(); beg!=lst.end(); ++beg)
//    addRequest(new Request(*beg));
//  return *this;
//}
/*
 *add path to scheduler
 *
 *@param request
 * */
void Scanner::addRequest(Request & request)
{
  scheduler.push(request);
}
/*
 *
 *
 * */
void Scanner::run()
{
  //start to get image and process
  while ( !shutdown_ && 1) {
   // printf("thread num %d\n",thread_id_map_.size());
//    waitTime(2);
    pthread_mutex_lock(&command_mutex_);
    //find the dead thread and remove it from thread_id_map_
//    if ( !thread_id_map_.empty() ) {
//      deleteThread();
//      pthread_mutex_unlock(&command_mutex_);
//    }
    //check thread number is special *must be short == >long,could not be long ==> short*
    //control the total of alive thread
#if 0
    if ( thread_id_map_.size() == this->threadNum) {
      checkThread();
      deleteThread();
      pthread_mutex_unlock(&command_mutex_);
      continue;
    }
#endif
    //waiting,until a new task coming,startThread at now
    if ( scheduler.hasTask() ) {
      Request requestFinal;
      scheduler.poll(requestFinal);
#if 0
      startThread(requestFinal);
#else
//      printf("run: %s\n",requestFinal.file.c_str());
      task = Task {path:&(requestFinal.file),obj:(void*)this};
      pthread_mutex_unlock(&command_mutex_);
      startThread(task);
#endif
    } else {
//      printf("no task coming\n");
      waitTime(1);
      pthread_mutex_unlock(&command_mutex_);
    }
  }
}
/*
 *
 *
 * */
void Scanner::processRequest(Request * request)
{
  printf("start to deal with image!\n");
  Image image;
  processor->process(image);
}
/*start with more than one threads
 *
 *@param threadNum threadNum
 *@return *this
 * */
Scanner Scanner::thread(int threadNum)
{
  this->threadNum = threadNum;
  if (threadNum <= 0) {
    printf("error threadNum should be more than one!\n");
  }
  return *this;
}

void Scanner::startThread(Request & request)
{
  string * path = &(request.file);
  pthread_t tempThread;
  pthread_create(&tempThread, NULL, Scanner::process, path);
  thread_id_map_[tempThread] = 0;
}

void Scanner::startThread(Task & task)
{
//  printf("startThread %s\n",(*(task.path)).c_str());
//  printf("startThread %p\n",task.obj);
//  string * path = &(request.file);
  pthread_t tempThread;
  pthread_create(&tempThread, NULL, Scanner::process, &task);
  thread_id_map_[tempThread] = 0;
}

void Scanner::initializeThreads()
{
  for (int i=0; i< THREAD_NUM; i++)
  {
    pthread_t tempThread;
    pthread_create(&tempThread, NULL, Scanner::process, NULL);
    thread_id_map_[tempThread] = 0;
  }
}

void Scanner::addThread()
{
  if(1);
}

void Scanner::deleteThread()
{
  for(map<pthread_t,int>::iterator iter = thread_id_map_.begin(); iter!=thread_id_map_.end();iter++)
    if( iter->second == 1)
      thread_id_map_.erase(iter);
}

void Scanner::waitTime(int val)
{
  gettimeofday(&now, NULL);
  outtime.tv_sec = now.tv_sec + val;
  outtime.tv_nsec = now.tv_usec * 1000;
  pthread_cond_timedwait(&command_cond_, &command_mutex_, &outtime);
}

void Scanner::checkThread()
{
  for(map<pthread_t,int>::iterator iter = thread_id_map_.begin(); iter!=thread_id_map_.end();iter++){
    int kill_rc = pthread_kill(iter->first,0);
    if( kill_rc == ESRCH )
      iter->second = 1;
  }
}

void Scanner::extractAndAddRequest(Image & image)
{
  Request request = image.getTargetRequest();
  printf("extract %s\n",request.file.c_str());
  if (request.isValid) {
    addRequest(request);
  }
}
