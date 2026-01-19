#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "tasks/Task.h"

#define MAX_TASKS 10

class Scheduler {
    int basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];
    unsigned long lastScheduleTime;

public:
    Scheduler();

    /* Initializes the scheduler with the base tick period */
    void init(int basePeriod);

    /* Adds a new task to the scheduling list. Returns false if list is full */
    bool addTask(Task* task);

    /* Main loop function: checks time and runs tasks if needed */
    void schedule();
};

#endif
