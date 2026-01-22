#ifndef DRONE_HANGAR_TASK_H
#define DRONE_HANGAR_TASK_H

#include <Arduino.h>
#include "Task.h"
#include "../components/Button.h"
#include "../components/ServoDoor.h"
#include "../components/Sonar.h"
#include "../components/Pir.h"
#include "../components/UserInterface.h"
#include "../serial/MessageService.h"
#include "SharedData.h"

class DroneHangarTask : public Task {
public:
    DroneHangarTask(ServoDoor* door, Button* resetButton, Sonar* sonar, Pir* pir, UserInterface* ui, MessageService* messageService, float distDroneIn, float distDroneOut, long D1, long D2);
    void init(int period) override;
    void tick() override;
private:
    ServoDoor* door;
    Button* resetButton;
    Sonar* sonar;
    Pir* pir;
    UserInterface* ui;
    MessageService* messageService;
    float distDroneIn;
    float distDroneOut;
    long D1;
    long D2;
    int duration1;
    int duration2;
    int counter1;
    int counter2;
    bool canLand;
};


#endif