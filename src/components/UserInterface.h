#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class UserInterface {
    public:
        UserInterface(int lcd_addr, int lcd_cols, int lcd_rows, int led1pin, int led2pin, int led3pin);
        void init();
        void displayMessage(const String &message, int row);
        
        void setLedState(int ledIndex, bool state);
        void blinkLed(int ledIndex);
    private:
        LiquidCrystal_I2C* lcd;
        int ledPins[3];
        bool ledStates[3] = {false, false, false};
        int rows;
        int cols;
        int lcdAddress;
        void clear(int row);
};

#endif