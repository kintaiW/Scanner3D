//
// Created by kintai on 17-3-29.
//

#include "Director.h"

//std::mutex mtx;
//std::condition_variable conv;

Director *
Director::getInstance() {
    static Director s_instance;//static local variable ,one of single pattern method implement
    return &s_instance;
}

Director::Director():
SHUTDOWN(false),
_processImg(nullptr){}

Director::~Director() {}
//add task to scheduler
int
Director::addTask(int num) {
    scheduler.push(num);
}
//the jni interface to run process image , Director::getInstance()->run()
int
Director::run() {
    initProgram();
    initTask();
    initThread(THREAD_MAX);
    while (true) {
        if ( ENDFLAG == TASKNUM ) {
            if ( stopAll() == -1 ) {
                LOGK("NOW EXIT %s\n",LOG_TAG);
                break;
            }
        }
    }
    exitProgram();
}
//init~ program use single pattern,maybe add display programm at soon by OpenGL ES (ex:_glProgram)
int
Director::initProgram() {
#if TEST_PC
    _processImg = new ProcessImage();
#else
    _processImg = new ProcessImage(getImagePath());
#endif
}
int
Director::exitProgram() {
    delete _processImg;
}
//initialize the task scheduler
int
Director::initTask() {
    for( int i= TASKSTART; i<TASKNUM; ++i ) {
        addTask(i);
    }
}
//initialize thread, add set thread num  method at soon
int
Director::initThread(int num) {
    for( int i=0; i<num; ++i)
        threads.emplace_back( std::thread(std::bind(&Director::process,this)) );
}

//thread pool use process image and generate point cloud
int
Director::process() {
    LOGK("pid %lu created\n",std::this_thread::get_id());
    while ( !SHUTDOWN ) {
        int * taskNum;
        if ( checkTask(taskNum) ) {
            _processImg->run(*taskNum);
            ENDFLAG+=1;
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            LOGK("pid %lu run %d\n",std::this_thread::get_id(),*taskNum);
        }
    }
}
//Then lock the task scheduler ,promise only task per thread
bool
Director::checkTask(int * taskNum) {
    std::unique_lock<std::mutex> lck(mtx);
    //wait a new task,but in this program is not need,because of the task queue is add at first
    if ( !hasTask() ) {
            conv.wait(lck);
    } else {
        *taskNum = scheduler.front();
        scheduler.pop();
        return true;
    }
    return false;
}
//stop and release all thread resource
int
Director::stopAll() {
    if (SHUTDOWN) return -1;
    SHUTDOWN = true;

    conv.notify_all();

    for(auto& th:threads) th.join();
    LOGK("end all threads %s\n",LOG_TAG);
}
//create a new thread to run,
int
Director::startProcess()
{
    std::thread( std::bind(&Director::run,this) ).detach();
}
//
void
Director::setImagePath(char * s)
{
    folderPath = std::string(s);
}
//the flag TEST_PC set in Makefile,use run this program at PC (ex:Ubuntu)
#ifdef TEST_PC
int
main() {
    Director::getInstance()->run();
    LOGK("end main threads %s\n",LOG_TAG);
}
#endif

