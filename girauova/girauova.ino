/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/
#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>

RTC_DS1307 rtc;

volatile int year_ = 0;
volatile int month_ = 0;
volatile int day_ = 0;
volatile int hour_ = 0;
volatile int minute_ = 0;
volatile int second_ = 0;
bool flag = false;

void readTime()
{
  DateTime now = rtc.now();
  year_ = now.year();
  month_ = now.month();
  day_ = now.day();
  hour_ = now.hour();
  minute_ = now.minute();
  second_ = now.second();
}

#define PIN_SERVO 3

Servo myservo;  // create servo object to control a servo

int pos = 0;

int inc = 1;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  //rtc.adjust(DateTime(2019, 5, 20, 23, 07, 0));

  myservo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object
  pos = 0;
  myservo.write(pos);                  // sets the servo position according to the scaled value
  setTimer();
  startTimer();
  delay(2000);
}

void loop() {
  if(flag){
    readTime();
  Serial.println(year_);
  flag = false;
  }
  delay(100);

}

volatile unsigned int tcnt1; //valore da cui il contatore cartirà ad ogni giro

void setTimer()
{
  //imposto i registri utili per fa funzionare il timer
  TIMSK1 &= ~(1 << TOIE1);                  //setto a zero il "timer overflow interrupt enable" così per essere sicuro che sia disattivato
  TCCR1A &= ~((1 << WGM11) | (1 << WGM10)); //setto a 0 WGM11, WGM10 e WGM12 per
  TCCR0B &= ~((1 << WGM12) | (1 << WGM13)); //impostare la modalità normal mode of operation
  TIMSK1 &= ~(1 << OCIE1A);                 //metto a zero OCIE1A per abilitare l'interrupt del compare macht A, interrupt fortnito dal comparatore fra tcnt1 e TOP (normal mode)
  TCCR1B |= (1 << CS12);                    //setto i CS1x a 101 per impostare 1024
  TCCR1B |= (1 << CS10);
  TCCR1B &= ~(1 << CS11);
  tcnt1 = 0; //carico il contatore a 65536 - 15625 per  avere un ciclo di 4 secondi
}

void startTimer()
{
  if (!(TIMSK1 && B00000001))
  {
    TCNT1 = tcnt1;            //imposto il contatore
    TIMSK1 |= (1 << TOIE1);   //setto a uno il "timer overflow interrupt enable
  }
}


ISR(TIMER1_OVF_vect) //routine chiamata quando avviene il match con il TOP
{
  TCNT1 = tcnt1;    //riporto il counter al valore iniziale da cui voglio farlo partire
  // TIMSK1 &= ~(1 << TOIE1); //disabilito l'interrupt overflow per stoppare il contatore
 flag = true;
}
