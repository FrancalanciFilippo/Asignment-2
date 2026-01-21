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

Button* resetButton;
Pir* pirSensor;
ServoDoor* servoDoor;
Sonar* sonarSensor;
TempSensor* tempSensor;
UserInterface* userInterface;
MessageService* messageService;

DroneHangarTask* droneHangarTask;
TempMonitorTask* tempMonitorTask;
BlinkTask* blinkTask;

Scheduler scheduler;

// put function declarations here:
int myFunction(int, int);

void initComponents() {
  resetButton->init();
  pirSensor->init();
  servoDoor->init();
  sonarSensor->init();
  tempSensor->init();
  userInterface->init();
  messageService->init();
}
void initTasks() {
  droneHangarTask->init(PERIOD_HANGAR_TASK);
  tempMonitorTask->init(PERIOD_TEMP_TASK);
  blinkTask->init(PERIOD_BLINK_TASK);
}

void setup() {
  resetButton = new Button(PIN_BUTTON_RESET);
  pirSensor = new Pir(PIN_PIR);
  servoDoor = new ServoDoor(PIN_SERVO);
  sonarSensor = new Sonar(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
  tempSensor = new TempSensor(PIN_TEMP_SENSOR);
  userInterface = new UserInterface(LCD_ADDRESS, LCD_COLS, LCD_ROWS, PIN_LED_1, PIN_LED_2, PIN_LED_3);
  messageService = new MessageService();
  initComponents();
  droneHangarTask = new DroneHangarTask(servoDoor, resetButton, sonarSensor, pirSensor, userInterface, messageService, DIST_DRONE_OUT, DIST_DRONE_IN, TIME_CHECK_OUT, TIME_CHECK_IN);
  tempMonitorTask = new TempMonitorTask(tempSensor, userInterface, TEMP_PRE_ALARM, TEMP_ALARM, TIME_PRE_ALARM, TIME_ALARM);
  blinkTask = new BlinkTask(1, userInterface);
  initTasks();
  scheduler.init(100);
  scheduler.addTask(droneHangarTask);
  scheduler.addTask(tempMonitorTask);
  scheduler.addTask(blinkTask);

}



void loop() {
  scheduler.schedule();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}