


#define LCD_SCREEN
#define SENSOR
#define PID_
#define BUTTON
/****************/
#define PIN_RELAY 8
#define PIN_DHT 2     // Digital pin connected to the DHT sensor
#define PIN_THERMISTOR 
#define PIN_BT1 3
#define PIN_BT2 4
/**************/
#ifdef PID_
#include <PID_v1.h>
#include "pid.h"
#endif
#ifdef LCD_SCREEN
#include <LiquidCrystal_I2C.h> // Libreria LCD I2C
#include "lcd.h"
#endif
#ifdef SENSOR
#include "DHT.h"
#include "sensor.h"
#endif
#ifdef PIN_THERMISTOR 
#include "thermistor.h"
#include "HardwareSerial.h"
#include "therm.h"
#endif
#ifdef BUTTON
#include "button.h"
#endif


/*************/
