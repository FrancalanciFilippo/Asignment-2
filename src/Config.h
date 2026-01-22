#ifndef CONFIG_H
#define CONFIG_H

// --- PINS CONFIGURATION ---
#define PIN_SONAR_TRIG 7
#define PIN_SONAR_ECHO 8
#define PIN_PIR 2
#define PIN_TEMP_SENSOR A0 
#define PIN_SERVO 9 
#define PIN_LED_1 11 
#define PIN_LED_2 12 
#define PIN_LED_3 13 
#define PIN_BUTTON_RESET 3

// --- LCD CONFIGURATION ---
#define LCD_ADDRESS 0x27 
#define LCD_COLS 16
#define LCD_ROWS 2

// --- SYSTEM PARAMETERS (Distances cm) ---
#define DIST_DRONE_OUT 10  
#define DIST_DRONE_IN 50

// --- SYSTEM PARAMETERS (Times ms) ---
#define TIME_CHECK_OUT 3000 
#define TIME_CHECK_IN 3000 
#define TIME_PRE_ALARM 2000 
#define TIME_ALARM 5000 

// --- SYSTEM PARAMETERS (Temperature C) ---
#define TEMP_PRE_ALARM 25.0 
#define TEMP_ALARM 30.0 

// --- TASK PERIODS (ms) ---
#define PERIOD_HANGAR_TASK 100
#define PERIOD_TEMP_TASK 500
#define PERIOD_BLINK_TASK 500

#endif