#ifndef TASK_H
#define TASK_H

class Task {
    int myPeriod;
    int timeElapsed;

public:
    virtual void init(int period);
    virtual void tick() = 0;
    bool updateAndCheckTime(int basePeriod);
};

#endif