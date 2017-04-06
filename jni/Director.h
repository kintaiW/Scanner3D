//
// Created by kintai on 17-3-29.
//

#ifndef OPENCAMERA_CODE_DIRECTOR_H
#define OPENCAMERA_CODE_DIRECTOR_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>
#include <vector>
#include <string>

#include "ProcessImage.h"
#include "FutureLog.h"

class Director {

public:
    static Director * getInstance();
    int addTask(int num);
    int run();
    int initProgram();
    int exitProgram();
    int initTask();
    int initThread(int num);
    int process();
    bool checkTask(int * num);
    int stopAll();

    int startProcess();
    void setImagePath(char * path);
    inline std::string getImagePath() { return folderPath;}

    inline bool hasTask() { return !scheduler.empty(); }
private:
    Director();
    ~Director();
    ProcessImage * _processImg;

    //
#ifdef TEST_PC
    int THREAD_MAX = 8;
#else
    int THREAD_MAX = 2;
#endif
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable conv;
    bool SHUTDOWN;
    int TASKSTART = 0;//the first image num
    std::atomic_int ENDFLAG = {TASKSTART}; //the threadpool end flag
    int TASKNUM = 40;//the last image num
    //
    std::queue<int> scheduler;
    //
    std::string folderPath;
};


#endif //OPENCAMERA_CODE_DIRECTOR_H
