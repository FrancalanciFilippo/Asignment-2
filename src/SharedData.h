
#ifndef SHARED_DATA_H
#define SHARED_DATA_H

enum GlobalState {
  IDLE,
  TAKE_OFF,
  IDLE_OUT,
  LANDING,
  ALARM
};

extern volatile GlobalState currentState; 
extern volatile bool preAlarmActive;

#endif
