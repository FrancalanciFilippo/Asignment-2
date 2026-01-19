#ifndef TASK_H
#define TASK_H

class Task {
    int myPeriod;
    int timeElapsed;

public:
    /* Initializes the task with its execution period */
    virtual void init(int period);

    /* Main logic of the task, to be implemented by subclasses */
    virtual void tick() = 0;

    /* Updates internal timer and returns true if it's time to execute tick() */
    bool updateAndCheckTime(int basePeriod);
};

#endif