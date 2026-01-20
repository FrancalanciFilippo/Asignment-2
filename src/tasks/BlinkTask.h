#ifndef BLINK_TASK_H
#define BLINK_TASK_H

#include <Arduino.h>
#include "Task.h"
#include "SharedData.h"
#include "../components/UserInterface.h"

class BlinkTask : public Task{
    public:
        BlinkTask(int ledPin, UserInterface* ui);
        void init(int period) override;
        void tick() override;
    private:
        int ledIndex;
        UserInterface* ui;
};

#endif BLINK_TASK_H