
#ifndef SHARED_DATA_H
#define SHARED_DATA_H

enum GlobalState {
  IDLE,
  TAKE_OFF,
  IDLE_OUT,
  LANDING,
  PRE_ALLARM,
  ALARM
};

extern GlobalState currentState; 

#endif
