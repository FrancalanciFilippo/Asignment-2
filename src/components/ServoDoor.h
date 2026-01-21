#ifndef SERVODOOR_H
#define SERVODOOR_H

#include <Arduino.h>
#include <Servo.h>

class ServoDoor {
    public:
        ServoDoor(int pin);
        void init();
        void open();
        void close();
        bool isDoorOpen();
    private:
        Servo servo;
        int pin;
        bool isOpen;
};

#endif