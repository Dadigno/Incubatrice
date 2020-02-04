double Setpoint, Input, Output, Kp=200, Ki=4, Kd=2;
int WindowSize = 5000;
unsigned long windowStartTime;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void init_pid(){
  windowStartTime = millis();
  Setpoint = 35;
  myPID.SetOutputLimits(0, WindowSize);
  myPID.SetMode(AUTOMATIC);
}


void calc_pid(double temp){
  Input = temp;
  myPID.Compute();
  if (millis() - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime) digitalWrite(PIN_RELAY, LOW);
  else digitalWrite(PIN_RELAY, HIGH);
}
