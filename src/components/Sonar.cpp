#include "Sonar.h"

Sonar::Sonar(int pinTrigger, int pinEcho) {
    this->pinTrigger = pinTrigger;
    this->pinEcho = pinEcho;
}

void Sonar::init() {
    pinMode(pinTrigger, OUTPUT);
    pinMode(pinEcho, INPUT);
}

long Sonar::GetDistance() {
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(2); 
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);
    long duration = pulseIn(pinEcho, HIGH);
    long distance = duration/58;

    return distance;
}