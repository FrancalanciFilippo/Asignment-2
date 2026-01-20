#include "button.h"

Button::Button(int pin) {
    this->pin = pin;
}

void Button::init(){
    pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed(){
    return digitalRead(pin) == LOW;
}