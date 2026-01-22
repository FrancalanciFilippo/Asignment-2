#include "TempMonitorTask.h"

TempMonitorTask::TempMonitorTask(TempSensor* tempSensor, UserInterface* ui, MessageService* messageService, float temp1, float temp2, long T3, long T4) : Task() {
    this->tempSensor = tempSensor;
    this->ui = ui;
    this->temp1 = temp1;
    this->temp2 = temp2;
    this->T3 = T3;
    this->T4 = T4;
    this->messageService = messageService;
}

void TempMonitorTask::init(int period) {
    Task::init(period);
    this->time3 = T3/period;
    this->time4 = T4/period;
    counterT3 = 0;
    counterT4 = 0;
}

void TempMonitorTask::tick() {
    
    if(currentState == ALARM){
        return;
    }
    float temperature = tempSensor->readTemperature();

    if(currentState == IDLE || currentState == LANDING || currentState == TAKE_OFF){
        handleAlarm(temperature);
        handlePreAlarm(temperature);
    }
    else{
        counterT3 = 0;
        counterT4 = 0;
        preAlarmActive = false;
    }
}

void TempMonitorTask::handlePreAlarm(float temperature) {
    if(temperature >= temp1){
        counterT3++;
        if(counterT3 >= time3){
            preAlarmActive = true;
            counterT3 = time3;
        }
    }
    else{
        counterT3 = 0;
        if(preAlarmActive){
            preAlarmActive = false;
        }
    }
}

void TempMonitorTask::handleAlarm(float temperature) {
    if(temperature >= temp2){
        counterT4++;
        if(counterT4 >= time4){
            currentState = ALARM;
            ui->displayMessage("ALARM!", 1);
            ui->setLedState(2, true);
            messageService->sendMessage(HANGAR, "ALARM");
            counterT4 = time4;
        }
    }
    else{
        counterT4 = 0;
    }
}