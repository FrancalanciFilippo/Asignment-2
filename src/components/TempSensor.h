#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include <Arduino.h>

class TempSensor {
    public:
        TempSensor(int pin);
        void init();
        float readTemperature();
    private:
        int pin;
};

#endif