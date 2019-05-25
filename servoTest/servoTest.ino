// Sweep
// by BARRAGAN 
// This example code is in the public domain.
 
#include <Servo.h>
 
Servo myservo;
 
int pos = 0;
 
void setup()
{
  myservo.attach(3);
}
 
void loop()
{
  for(pos = 0; pos < 180; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for(pos = 180; pos>=1; pos-=1)
  {
    myservo.write(pos);
    delay(15);
  }
}
