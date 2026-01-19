#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

class Pir {
  public:
    Pir(int pin);
    void init();
    bool isMotionDetected();

  private:
    int pin;
};

#endif