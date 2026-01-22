#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "tasks/Task.h"

#define MAX_TASKS 10

class Scheduler {
    unsigned int basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];
    unsigned long lastScheduleTime;

public:
    Scheduler();
    void init(int basePeriod);
    bool addTask(Task* task);
    void schedule();
};

#endif
