#include "UserInterface.h"

UserInterface::UserInterface(int lcd_addr, int lcd_cols, int lcd_rows, int led1pin, int led2pin, int led3pin) {
    this->ledPins[0] = led1pin;
    this->ledPins[1] = led2pin;
    this->ledPins[2] = led3pin;
    this->lcdAddress = lcd_addr;
    this->cols = lcd_cols;
    this->rows = lcd_rows;
}

void UserInterface::init() {
    lcd = new LiquidCrystal_I2C(lcdAddress, cols, rows);
    lcd->init();
    lcd->backlight();
    for (int i = 0; i < 3; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}

void UserInterface::clear(int row) {
    lcd->setCursor(0, row-1);
    lcd->print("                ");
}

void UserInterface::displayMessage(const String &message, int row){
    clear(row);
    lcd->setCursor(0, row-1);
    lcd->print(message);
}

void UserInterface::setLedState(int ledIndex, bool state) {
    if (ledIndex < 0 || ledIndex >= 3) return;
    digitalWrite(ledPins[ledIndex], state ? HIGH : LOW);
    ledStates[ledIndex] = state;
}

void UserInterface::toggleLed(int ledIndex) {
    if (ledIndex < 0 || ledIndex >= 3) return;
    bool newState = !ledStates[ledIndex];
    setLedState(ledIndex, newState);
}