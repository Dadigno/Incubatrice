
/*************PID CONTROL****************/
double Setpoint, Input, Output;
int WindowSize = 5000;
unsigned long windowStartTime;
int dimming = 255;
volatile bool flag_int = false;

PID myPID(&Input, &Output, &Setpoint, 40, 5, 2, DIRECT);


int x = 0;
void zero_crossing_int()
{
  flag_int = true;
  delayMicroseconds(35*x);
  digitalWrite(PIN_LIGHT,HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_LIGHT,LOW);
}

void init_pid() 
{
  pinMode(PIN_ZC, INPUT);
  Setpoint = 37.7;
  myPID.SetMode(AUTOMATIC);
  //attachInterrupt(digitalPinToInterrupt(PIN_ZC), zero_crossing_int, RISING);
}

int pid_action(float temp)
{
  Input = temp;
  myPID.Compute();
  //Serial.println(Output);
  return Output;
}
