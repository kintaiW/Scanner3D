//
// Created by kintai on 17-3-29.
//

#include "Director.h"

//std::mutex mtx;
//std::condition_variable conv;

Director *
Director::getInstance() {
    static Director s_instance;
    return &s_instance;
}

Director::Director():
SHUTDOWN(false){}

Director::~Director() {
    delete _processImg;
}

int
Director::addTask(int num) {
    scheduler.push(num);
}

int
Director::run() {
    initProgram();
    initTask();
    initThread(8);
    while (true) {
        if ( !hasTask() ) {
            if ( stopAll() == -1 ) {
                LOGK("NOW EXIT %s\n",LOG_TAG);
                break;
            }
        }
    }
}

int
Director::initProgram() {
    _processImg = new ProcessImage();
}

int
Director::initTask() {
    for( int i=0; i<40; ++i ) {
        addTask(i);
    }
}

int
Director::initThread(int num) {
    for( int i=0; i<num; ++i)
        threads.push_back( std::thread(std::bind(&Director::process,this)) );
}

//thread pool use process image and generate point cloud
int
Director::process() {
    LOGK("pid %lu created\n",std::this_thread::get_id());
    while ( !SHUTDOWN ) {
        int * taskNum;
        if ( checkTask(taskNum) ) {
            _processImg->run(*taskNum);
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            LOGK("pid %lu run %d\n",std::this_thread::get_id(),*taskNum);
        }
    }
}
//
bool
Director::checkTask(int * taskNum) {
    std::unique_lock<std::mutex> lck(mtx);
    //wait a new task,but in this program is not need,because of the task queue is add at first
    while ( !hasTask() && !SHUTDOWN ) {
            conv.wait(lck);
    }
    if ( hasTask() ) {
        *taskNum = scheduler.front();
        scheduler.pop();
        return true;
    }
    return false;
}

int
Director::stopAll() {
    if (SHUTDOWN) return -1;
    SHUTDOWN = true;
    LOGK("end all threads %s\n",LOG_TAG);
    conv.notify_all();

    for(auto& th:threads) th.join();
}

#ifdef TEST_PC
int
main() {
    Director::getInstance()->run();
    LOGK("end main threads %s\n",LOG_TAG);
}
#endif