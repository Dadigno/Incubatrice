#include "DHT.h"
#include <PID_v1.h>

#define PIN_FAN 3  //
#define PIN_DHT 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


//Define Variables we'll be connecting to
double Setpoint, Input, Output, Kp=2, Ki=7, Kd=2;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
DHT dht(PIN_DHT, DHTTYPE);

void setup()
{
  dht.begin();
  Input = dht.readTemperature();
  Setpoint = 30;
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = dht.readTemperature();
  myPID.Compute();
  Serial.println("Input: " + String(Input) + "Output: " + String(Output));
  Output = map(Output,0,255,20,255);
  analogWrite(PIN_FAN, Output);
  delay(200);
}
