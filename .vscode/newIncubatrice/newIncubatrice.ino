#include "configuration.h"

void setup(){
  Serial.begin(9600);
  init_lcd();
  init_pid();
  init_dht();
  Serial.println("Pronto");
}

void loop(){
  double t = read_temp();
  double hum = read_hum();
  double bedT = read_thermistor();
  calc_pid(bedT);
  refreshLcd(bedT,hum,t);
  button_hanlder();
  //Serial.println(Setpoint);
  
  delay(100);
}
