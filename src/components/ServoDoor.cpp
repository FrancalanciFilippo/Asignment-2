#include "ServoDoor.h"

ServoDoor::ServoDoor(int pin) {
    this->pin = pin;
}

void ServoDoor::init() {
    servo.attach(pin);
    close();
}
void ServoDoor::open(){
    servo.write(90);
}

void ServoDoor::close(){
    servo.write(0);
}