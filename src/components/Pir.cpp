#include "Pir.h"

Pir::Pir(int pin){
    this->pin = pin;
}

void Pir::init(){
    pinMode(pin,INPUT);
}

bool Pir::isMotionDetected(){
    return digitalRead(pin) == HIGH;
}