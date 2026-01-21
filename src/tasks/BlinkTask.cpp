#include "BlinkTask.h"

BlinkTask::BlinkTask(int ledIndex, UserInterface* ui) : Task() {
    this->ledIndex = ledIndex;
    this->ui = ui;
}

void BlinkTask::init(int period) {
    Task::init(period);
    ui->setLedState(ledIndex, false);
}

void BlinkTask::tick() {
    if(currentState == TAKE_OFF || currentState == LANDING) {
        ui->toggleLed(ledIndex);
    }
    else {
        ui->setLedState(ledIndex, false);
    }
    
}