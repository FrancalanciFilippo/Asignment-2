#include "DroneHangarTask.h"


DroneHangarTask::DroneHangarTask(ServoDoor* door, Button* resetButton, Sonar* sonar, Pir* pir, UserInterface* ui, MessageService* messageService, float distDroneIn, float distDroneOut, long D1, long D2) : Task() {
    this->door = door;
    this->resetButton = resetButton;
    this->sonar = sonar;
    this->pir = pir;
    this->ui = ui;
    this->messageService = messageService;
    this->distDroneIn = distDroneIn;
    this->distDroneOut = distDroneOut;
    this->D1 = D1;
    this->D2 = D2;
    this->canLand = false;
}

void DroneHangarTask::init(int period) {
    Task::init(period);
    this->duration1 = D1/period;
    this->duration2 = D2/period;
    counter1 = 0;
    counter2 = 0;
    door->close();
    ui->setLedState(0, true);
}

void DroneHangarTask::tick() {

    switch(currentState)
    {
    case IDLE:
    {
        if(!preAlarmActive){
            if(messageService->messageAvailable()){
                String msg = messageService->getMessage();
                if(msg == "TAKEOFF"){
                    door->open();
                    ui->displayMessage("TAKE OFF", 2);
                    messageService->sendMessage(DRONE, "TAKEING OFF");
                    currentState = TAKE_OFF;
                    counter1 = 0;
                    return;
                }
                else{
                    messageService->sendMessage(ERROR, "INVALID COMMAND");
                }
            }
        }
        break;
    }
    case TAKE_OFF:
    {
        int distanceOff = sonar->GetDistance();
        if(distanceOff >= distDroneIn){
            counter1++;
            if(counter1 >= duration1){
                door->close();
                ui->displayMessage("DRONE OUT", 2);
                messageService->sendMessage(DRONE, "OPERATING");
                ui->setLedState(0, false);
                currentState = IDLE_OUT;
                counter1 = duration1;
            }
        }
        else{
            counter1 = 0;
        }
        break;
    }
    case IDLE_OUT:
    {
        if(messageService->messageAvailable()){
            String msg = messageService->getMessage();
            if(msg == "LANDING"){
                messageService->sendMessage(DRONE, "WAITING FOR PIR");
                canLand = true;
                return;
            }
            else{
                messageService->sendMessage(ERROR, "INVALID COMMAND");
            }
        }
        if(canLand && pir->isMotionDetected()){
                door->open();
                ui->displayMessage("LANDING", 2);
                messageService->sendMessage(DRONE, "LANDING");
                currentState = LANDING;
                counter2 = 0;
                return;
            }
        break;
    }
        
    case LANDING:
        {
            int distanceLand = sonar->GetDistance();
        messageService->sendMessage(DISTANCE, String(distanceLand));
        if(distanceLand <= distDroneOut){
            counter2++;
            if(counter2 >= duration2){
                door->close();
                ui->displayMessage("DRONE IN", 2);
                messageService->sendMessage(DRONE, "RESTING");
                ui->setLedState(0, true);
                currentState = IDLE;
                counter2 = duration2;
                canLand = false;
            }
        }
        else{
            counter2 = 0;
        }
        break;
        }
    case ALARM:
    {
        if(door->isDoorOpen()){
            door->close();
        }
        if(resetButton->isPressed()){
            currentState = IDLE;
            ui->displayMessage("SYSTEM RESET", 1);
            ui->setLedState(2, false);
            delay(1000);
            messageService->sendMessage(HANGAR, "NORMAL");
            ui->displayMessage("DRONE HANGAR", 1);
            ui->displayMessage("DRONE IN", 2);
        }
        break;
    }
    default:
        break;
    }
}

