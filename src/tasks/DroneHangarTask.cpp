#include "DroneHangarTask.h"


DroneHangarTask::DroneHangarTask(ServoDoor* door, Button* resetButton, Sonar* sonar, Pir* pir, UserInterface* ui, MessageService* messageService, float openDistance, float closeDistance, long D1, long D2) : Task() {
    this->door = door;
    this->resetButton = resetButton;
    this->sonar = sonar;
    this->pir = pir;
    this->ui = ui;
    this->messageService = messageService;
    this->openDistance = openDistance;
    this->closeDistance = closeDistance;
    this->D1 = D1;
    this->D2 = D2;
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

    switch (currentState)
    {
    case IDLE:
        if(!preAlarmActive){
            if(messageService->messageAvailable()){
                String msg = messageService->getMessage();
                if(msg == "TAKEOFF"){
                    door->open();
                    ui->displayMessage("TAKE OFF", 1);
                    currentState = TAKE_OFF;
                    counter1 = 0;
                }
            }
        }

        break;
    case TAKE_OFF:
        if(sonar->GetDistance() >= openDistance){
            counter1++;
            if(counter1 >= duration1){
                door->close();
                ui->displayMessage("DRONE OUT", 1);
                currentState = IDLE_OUT;
                counter1 = duration1;
            }
        }
        else{
            counter1 = 0;
        }

        break;
    case IDLE_OUT:
        if(messageService->messageAvailable()){
                String msg = messageService->getMessage();
                if(msg == "LANDING" && pir->isMotionDetected()){
                    door->open();
                    ui->displayMessage("LANDING", 1);
                    currentState = LANDING;
                    counter2 = 0;
                }
            }
        break;
    case LANDING:
        if(sonar->GetDistance() <= closeDistance){
            counter2++;
            if(counter2 >= duration2){
                door->close();
                ui->displayMessage("DRONE IN", 1);
                currentState = IDLE;
                counter2 = duration2;
            }
        }
        else{
            counter2 = 0;
        }
        break;
    case ALARM:
        if(door->isDoorOpen()){
            door->close();
        }
        if(resetButton->isPressed()){
            currentState = IDLE;
            ui->displayMessage("SYSTEM RESET", 1);
            delay(1000);
            ui->displayMessage("DRONE IN", 1);
        }
        break;
    default:
        break;
    }
}

