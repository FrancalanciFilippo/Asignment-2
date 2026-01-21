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
    isOpen = true;
}

void ServoDoor::close(){
    servo.write(0);
    isOpen = false;
}

bool ServoDoor::isDoorOpen(){
    return isOpen;
}