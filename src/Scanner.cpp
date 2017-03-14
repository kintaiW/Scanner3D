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

Scanner Scanner::create(Processor p)
{
  processor = p;
  return *this;
}

void * Scanner::process(void * arg)
{
  printf("pid %lu created, arg %p\n",pthread_self(),arg);
  while (true)
  {
    pthread_mutex_lock(&command_mutex_);
    while ( !((Scanner *)arg)->scheduler.hasTask() && !shutdown_)
    {
      pthread_cond_wait(&command_cond_, &command_mutex_);
    }

    if(shutdown_)
    {
      pthread_mutex_unlock(&command_mutex_);
      printf("thread %lu will exit\n",pthread_self());
      pthread_exit(NULL);
    }

    Request request;
    ((Scanner*)arg)->pollRequest(request);
    pthread_mutex_unlock(&command_mutex_);

    Image image(request);
    processor->process(image);
//    ((Scanner*)arg)->extractAndAddRequest(image);
    printf("pid %lu run %s\n",pthread_self(),image.getName());
  }
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
/*
 *add path to scheduler
 *
 *@param request
 * */
void Scanner::addRequest(Request & request)
{
  scheduler.push(request);
  pthread_cond_signal(&command_cond_);
}
/*
 *add local image path
 *
 * @param local image folder path
 * */
Scanner Scanner::addLocalPath(string path)
{
  for(int i = 1; i<=(360/angle); i++){
    string basePath = path;
    string file(basePath.append( (to_string(i)).c_str() ) + ".jpeg");
    Request request(file,i);
    addRequest(request);
  }
  return *this;
}

int Scanner::pollRequest(Request & request)
{
  count+=1;
  return scheduler.poll(request);
}
/*
 *
 *
 * */
void Scanner::run()
{
  initializeThreads(*this);
  while (true)
  {
    if( count == tasks)
    {
      if ( this->stopAll(*this) == -1)
      {
        printf("NOW exit\n");
        break;
//        exit(0);
      }
    }
  }
}

int Scanner::stopAll(Scanner & scanner)
{
  if(shutdown_) return -1;
  printf("end all threads\n");
  shutdown_ = true;
  pthread_cond_broadcast(&command_cond_);

  for(int i=0; i<scanner.threadNum; i++)
    pthread_join(pthread_id[i],NULL);

  free(pthread_id);
  pthread_id = NULL;
  pthread_mutex_destroy(&command_mutex_);
  pthread_cond_destroy(&command_cond_);
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

void Scanner::initializeThreads(Scanner & scanner)
{
  pthread_id = (pthread_t*)malloc(sizeof(pthread_t) * scanner.threadNum);
  for (int i=0; i<scanner.threadNum; i++)
  {
    pthread_create(&pthread_id[i], NULL, Scanner::process, (void*)&scanner);
  }
}

void Scanner::waitTime(int val)
{
  gettimeofday(&now, NULL);
  outtime.tv_sec = now.tv_sec + val;
  outtime.tv_nsec = now.tv_usec * 1000;
  pthread_cond_timedwait(&command_cond_, &command_mutex_, &outtime);
  pthread_cond_signal(&command_cond_);
}

void Scanner::extractAndAddRequest(Image & image)
{
  Request request = image.getTargetRequest();
  if (request.isValid) {
    addRequest(request);
  }
}
