#include "Scanner.h"

pthread_mutex_t Scanner::command_mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Scanner::command_cond_ = PTHREAD_COND_INITIALIZER;
bool Scanner::shutdown_ = false;
int Scanner::icurr_thread_num_ = THREAD_NUM;
map<pthread_t,int> Scanner::thread_id_map_;
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
  Image image;
  processor->process(image);
}
/*
 *add image to scanner
 *
 *@param string_list string
 *@return this
 **/
Scanner Scanner::addPath(string path)
{
  addRequest(new Request(path));
  return *this;
}

Scanner Scanner::addPath(initializer_list<string> lst)
{
  for(auto beg=lst.begin(); beg!=lst.end(); ++beg)
    addRequest(new Request(*beg));
  return *this;
}
/*
 *add path to scheduler 
 *
 *@param request
 * */
void Scanner::addRequest(Request * request)
{
  scheduler.push(request);
}
/*
 *
 *
 * */
void Scanner::run()
{
  //initializeThreads();
  while ( !shutdown_ && 1) {
    pthread_mutex_lock(&command_mutex_);

//    if ( 1 == thread_id_map_[pthread_self()]){
//      pthread_mutex_unlock(&command_mutex_);
//      printf
//    }
    Request * request = scheduler.poll();


    if (request == NULL) {
      pthread_mutex_unlock(&command_mutex_);
      pthread_cond_wait(&command_cond_,&command_mutex_);
    } else {
      Request requestFinal = *request;
      pthread_mutex_unlock(&command_mutex_);

      startThread(&requestFinal);
//      processRequest(&requestFinal);
    }
    //if need to shutdown thread pool
    if (shutdown_) {
      pthread_mutex_unlock(&command_mutex_);
      printf("thread %u will exit\n", pthread_self());
      pthread_exit(NULL);
    }
    //check thread number is special
    if ( threadNum == thread_id_map_.size()) {
      pthread_cond_wait(&command_cond_,&command_mutex_);
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

void Scanner::startThread(Request * request)
{
  pthread_t tempThread;
  pthread_create(&tempThread, NULL, Scanner::process, request);
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
  if(1 );
}

void Scanner::deleteThread()
{
  int size = icurr_thread_num_ - THREAD_NUM;
  map<pthread_t,int>::iterator iter = thread_id_map_.begin();
  for(int i=0; i<size; ++i, ++iter)
    iter->second = 1;
}
