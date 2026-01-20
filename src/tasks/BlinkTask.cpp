#include "BlinkTask.h"

BlinkTask::BlinkTask(int ledPin, UserInterface* ui) : Task() {
    this->ledIndex = ledPin;
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