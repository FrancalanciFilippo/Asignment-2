#ifndef TEMP_MONITOR_TASK_H
#define TEMP_MONITOR_TASK_H

#include <Arduino.h>
#include "Task.h"
#include "../components/TempSensor.h"
#include "../components/UserInterface.h"
#include "SharedData.h"

class TempMonitorTask : public Task {
    public:
        TempMonitorTask(TempSensor* tempSensor, UserInterface* ui, float temp1, float temp2, long T3, long T4);
        void init(int period) override;
        void tick() override;
    private:
        TempSensor* tempSensor;
        UserInterface* ui;
        float temp1;
        float temp2;
        float T3;
        float T4;
        int time3;
        int time4;
        int counterT3;
        int counterT4;
        void handlePreAlarm(float temperature);
        void handleAlarm(float temperature);
};

#endif