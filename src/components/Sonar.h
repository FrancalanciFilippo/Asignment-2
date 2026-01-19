#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>

class Sonar {
    public:
        Sonar(int pinTrigger, int pinEcho);
        void init();
        long GetDistance();
    private:
        int pinTrigger;
        int pinEcho;
};

#endif