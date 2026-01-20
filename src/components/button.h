#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
    public:
        Button(int pin);
        void init();
        bool isPressed();
    private:
        int pin;
};

#endif