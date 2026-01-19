#include "Scheduler.h"
#include <Arduino.h>

Scheduler::Scheduler() {
    basePeriod = 0;
    nTasks = 0;
    lastScheduleTime = 0;
}

void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    lastScheduleTime = millis();
}

bool Scheduler::addTask(Task* task) {
    if (nTasks < MAX_TASKS) {
        taskList[nTasks] = task;
        nTasks++;
        return true;
    } else {
        return false; 
    }
}

void Scheduler::schedule() {
    unsigned long currentTime = millis();
    
    if (currentTime - lastScheduleTime >= basePeriod) {
        lastScheduleTime += basePeriod;

        for (int i = 0; i < nTasks; i++) {
            if (taskList[i]->updateAndCheckTime(basePeriod)) {
                taskList[i]->tick();
            }
        }
    }
}
