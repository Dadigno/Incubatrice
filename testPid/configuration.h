


#define LCD_SCREEN
#define SENSOR
#define PID_
/****************/
#define PIN_RELAY 8
#define PIN_DHT 2     // Digital pin connected to the DHT sensor
#define PIN_THERMISTOR 
/**************/
#ifdef LCD_SCREEN
#include <LiquidCrystal_I2C.h> // Libreria LCD I2C
#include "lcd.h"
#endif
#ifdef SENSOR
#include "DHT.h"
#include <PID_v1.h>
#include "sensor.h"
#endif
#ifdef PID_
#include "pid.h"
#endif
/*************/
