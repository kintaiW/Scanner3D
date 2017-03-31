//
// Created by kintai on 17-3-29.
//

#ifndef OPENCAMERA_CODE_DIRECTOR_H
#define OPENCAMERA_CODE_DIRECTOR_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

#include "ProcessImage.h"
#include "FutureLog.h"

class Director {

public:
    static Director * getInstance();
    int addTask(int num);
    int run();
    int initProgram();
    int initTask();
    int initThread(int num);
    int process();
    bool checkTask(int * num);
    int stopAll();

    inline bool hasTask() { return !scheduler.empty(); }
private:
    Director();
    ~Director();

    ProcessImage * _processImg;
    //
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable conv;
    bool SHUTDOWN;
    //
    std::queue<int> scheduler;
};


#endif //OPENCAMERA_CODE_DIRECTOR_H
