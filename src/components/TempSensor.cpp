#include "TempSensor.h"

TempSensor::TempSensor(int pin){
    this->pin = pin;
}

void TempSensor::init(){
    pinMode(pin, INPUT);
}

float TempSensor::readTemperature(){
    int sensorValue = analogRead(pin);
    float voltage = sensorValue * (5.0 / 1023.0);
    float temperatureC = (voltage - 0.5) * 100.0;
    return temperatureC;
}