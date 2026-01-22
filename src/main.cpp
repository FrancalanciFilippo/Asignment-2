#include <Arduino.h>
#include "SharedData.h"
#include "Config.h"
#include "Scheduler.h"
#include "tasks/Task.h"
#include "components/Button.h"
#include "components/Pir.h"
#include "components/ServoDoor.h"
#include "components/Sonar.h"
#include "components/TempSensor.h"
#include "components/UserInterface.h"
#include "serial/MessageService.h"
#include "tasks/DroneHangarTask.h"
#include "tasks/TempMonitorTask.h"
#include "tasks/BlinkTask.h"

GlobalState volatile currentState = IDLE;
bool volatile preAlarmActive = false;

Button resetButton(PIN_BUTTON_RESET);
Pir pirSensor(PIN_PIR);
ServoDoor servoDoor(PIN_SERVO);
Sonar sonarSensor(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
TempSensor tempSensor(PIN_TEMP_SENSOR);
UserInterface userInterface(LCD_ADDRESS, LCD_COLS, LCD_ROWS, PIN_LED_1, PIN_LED_2, PIN_LED_3);
MessageService messageService;

DroneHangarTask droneHangarTask(&servoDoor, &resetButton, &sonarSensor, &pirSensor, &userInterface, &messageService, DIST_DRONE_IN, DIST_DRONE_OUT, TIME_CHECK_OUT, TIME_CHECK_IN);
TempMonitorTask tempMonitorTask(&tempSensor, &userInterface, &messageService, TEMP_PRE_ALARM, TEMP_ALARM, TIME_PRE_ALARM, TIME_ALARM);
BlinkTask blinkTask(1, &userInterface);

Scheduler scheduler;

void initComponents() {
  resetButton.init();
  pirSensor.init();
  servoDoor.init();
  sonarSensor.init();
  tempSensor.init();
  userInterface.init();
  messageService.init();
}
void initTasks() {
  droneHangarTask.init(PERIOD_HANGAR_TASK);
  tempMonitorTask.init(PERIOD_TEMP_TASK);
  blinkTask.init(PERIOD_BLINK_TASK);
}

void setup() {
  initComponents();
  initTasks();
  scheduler.init(100);
  scheduler.addTask(&droneHangarTask);
  scheduler.addTask(&tempMonitorTask);
  scheduler.addTask(&blinkTask);
  userInterface.displayMessage("DRONE HANGAR", 1);
  userInterface.displayMessage("DRONE IN", 2);
  messageService.sendMessage(HANGAR, "NORMAL");
  messageService.sendMessage(DRONE, "RESTING");
}



void loop() {
  scheduler.schedule();
}