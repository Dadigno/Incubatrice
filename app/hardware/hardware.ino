
/*
    TIMER 0:    pin 6, 5 (PD6, PD5) , usato per dalay() e millis()
    TIMER 1:    pin 9, 10   (PB1, PB2)
    TIMER 2:    PIN 11, 3   (PB3, PD3)

    ESP:
    PIN 2 e 4
*/


#include "configuration_overhall.h"

#ifdef DHT_TEMP
#ifdef DHT_HUM
  #include <dht.h>
#endif
#endif

#ifdef PID_CONTROL 
  #include <PID_v1.h>
  #include "pid.h"
#endif

#ifdef LCD_SCREEN
  #include <LiquidCrystal_I2C.h> // Libreria LCD I2C
  #include "lcd.h"
#endif

#ifdef ESP
  #include "esp_communication.h"
#endif

#ifndef TIMER_COUNTER
  #include "timer_counter.h"
#endif

/*************TEMPERATURA e UMIDITA'***************/
float oldTemp = 0;
float oldHum = 0;
float oldHumidity = 0;
float hum = 0;
float temp = 0;
float setPoint = 37;

/**********FAN E LAMP*********/
float fan;
bool lamp;

/**********FUNCTION*************/
void readTime();
bool readTempHumid();
void sendData();
void sendError(int code);

/**************COMUNICAZIONE*************/
const char HEADER_DATA = 'H';
const char HEADER_ERROR = 'E';

dht DHT;

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  init_lcd();
  init_pid();
  init_dht();
  init_fan();
  init_lamp();
}

int pid_value = 0;

void loop()
{
  pid_value = pid_action(temp); //va da 0 a 255
  //x = map(pid_value, 0, 255, 255, 10);
  analogWrite(PIN_LIGHT,pid_value);
  int ack = readTempHumid();
  refreshLcd(temp, hum, oldTemp, oldHum);
    if (!ack)
    {
      temp = -1;
      hum = -1;
      digitalWrite(PIN_DHT_PW, LOW);
      delay(3000);
      digitalWrite(PIN_DHT_PW, HIGH);
      sendError(100);
    }
  /*if (counter >= 300)
  {
    counter = 0;
    TIMSK2 &= ~(1 << TOIE2);
    //sendData();
    refreshLcd(temp, hum, oldTemp, oldHum);
    if (!readTempHumid())
    {
      temp = -1;
      hum = -1;
      digitalWrite(PIN_DHT_PW, LOW);
      delay(3000);
      digitalWrite(PIN_DHT_PW, HIGH);
      sendError(100);
    }
    TIMSK2 |= (1 << TOIE2);
  }  */
}

void sendData()
{
  Serial.print(HEADER_DATA);
  Serial.print(";");
  Serial.print(temp);
  Serial.print(";");
  Serial.print(hum);
  Serial.print(";");
  Serial.print(lamp);
  Serial.print(";");
  Serial.print(fan);
  Serial.println(";");
}

void sendError(int code)
{
  Serial.print(HEADER_ERROR);
  Serial.print(";");
  Serial.print(code);
  Serial.println(";");
}


bool readTempHumid()
{
  bool flag = 0;
  int chk = DHT.read22(PIN_DHT);
  switch (chk)
  {
  case DHTLIB_OK:
  if (temp != oldTemp)
    {
      oldTemp = temp;
    }
    if (hum != oldHum)
    {
      oldHum = hum;
    }
    hum = DHT.humidity;
    temp = DHT.temperature;
    
    flag = 1;
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    flag = 0;
    break;
  case DHTLIB_ERROR_TIMEOUT:
    Serial.print("Time out error,\t");
    flag = 0;
    break;
  default:
    Serial.print("Unknown error,\t");
    flag = 0;
    break;
  }
  return flag;
}


void init_fan(){
  analogWrite(PIN_FAN, 30);
  fan = 30;
}
void init_lamp(){
  pinMode(PIN_LIGHT,OUTPUT);
  digitalWrite(PIN_LIGHT, LOW);
  lamp = false;
}
void init_dht(){
  pinMode(PIN_DHT_PW, OUTPUT);
  digitalWrite(PIN_DHT_PW, HIGH);
}
