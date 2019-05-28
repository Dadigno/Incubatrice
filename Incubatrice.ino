/*
    TIMER 0:    pin 6, 5 (PD6, PD5) , usato per dalay() e millis()
    TIMER 1:    pin 9, 10   (PB1, PB2)
    TIMER 2:    PIN 11, 3   (PB3, PD3)

    ESP:
    PIN 2 e 4
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Libreria LCD I2C
#include <dht.h>

#include <PID_v1.h>
#define PIN_DHT 8
#define PIN_LIGHT 12
#define PIN_DHT_PW  3
#define PIN_FAN 9
#define SCL A5
#define SDA A4
#define ESP_TX 2
#define ESP_RX 4

/**********INTERRUPT*************/
volatile unsigned int tcnt2; //valore da cui il contatore del timer1 partirà ad ogni ciclo
volatile bool flagTimer = true;
volatile int counter = 0;
int contTimer = 0;

/*************TEMPERATURA e UMIDITA'***************/
float oldTemp = 0;
float oldHum = 0;
float oldHumidity = 0;
float hum = 0;
float temp = 0;
byte arrowT = 0;
byte arrowH = 0;
float setPoint = 37;

/************DISPLAY*************/
byte downArrow[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

byte upArrow[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte nullC[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
/*************PID CONTROL****************/
double Setpoint, Input, Output;
int WindowSize = 5000;
unsigned long windowStartTime;

/**********FUNCTION*************/
void readTime();
void refreshLcd();
bool readTempHumid();
void setTimer();
void startTimer();


dht DHT;
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
PID myPID(&Input, &Output, &Setpoint, 500, 2000, 2, DIRECT);

void setup()
{
  pinMode(PIN_DHT_PW,OUTPUT);
  pinMode(PIN_LIGHT, OUTPUT);
  Serial.begin(9600);
  windowStartTime = millis();
  Setpoint = 37.7;
  myPID.SetOutputLimits(0, WindowSize);
  myPID.SetMode(AUTOMATIC);

  setTimer();
  startTimer();

  lcd.begin(20, 4);
  lcd.createChar(0, upArrow);
  lcd.createChar(1, downArrow);
  lcd.createChar(2, nullC);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("____Incubatrice_____");
  analogWrite(PIN_FAN, 30);
  digitalWrite(PIN_LIGHT, LOW);
}

void loop()
{
  Input = temp;
  myPID.Compute();
  // turn the output pin on/off based on pid output
  if (millis() - windowStartTime > WindowSize) {
    // time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  digitalWrite(PIN_LIGHT, !(Output < (millis() - windowStartTime)));
  
  if (flagTimer) {
    TIMSK2 &= ~(1 << TOIE2);
    refreshLcd();
    if (!readTempHumid())
    {
      temp = -1;
      hum = -1;
      digitalWrite(PIN_DHT_PW, HIGH);
      delay(500);
      digitalWrite(PIN_DHT_PW, LOW);
    }
    flagTimer = false;
    TIMSK2 |= (1 << TOIE2);
  }
}

void refreshLcd()
{
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(13, 1);
  lcd.write(arrowT);
  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print("%");
  lcd.setCursor(17, 2);
  lcd.write(arrowH);
}


bool readTempHumid() {
  bool flag = 0;
  int chk = DHT.read22(PIN_DHT);
  
  switch (chk)
  {
    case DHTLIB_OK:
      hum = DHT.humidity;
      temp = DHT.temperature;
      if (int(temp * 100) > int(oldTemp * 100)) {
        arrowT = byte(0);
      } else if (temp < oldTemp) {
        arrowT = byte(1);
      } else {
        arrowT = byte(2);
      }
      if (temp != oldTemp ) {
        oldTemp = temp;
      }
      if (int(hum * 100) > int(oldHum * 100)) {
        arrowH = byte(0);
      } else if (hum < oldHum) {
        arrowH = byte(1);
      } else {
        arrowH = byte(2);
      }
      if (hum != oldHum ) {
        oldHum = hum;
      }
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
void setTimer()
{
  //inizializzo i registri utili per fa funzionare il timer
  TIMSK2 &= ~(1 << TOIE2);                  //setto a zero il "timer overflow interrupt enable" così per essere sicuro che sia disattivato
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20)); //setto a 0 WGM21, WGM20 e WGM22 per
  TCCR2B &= ~(1 << WGM22);                  //impostare la modalità normal mode of operation
  ASSR &= ~(1 << AS2);                      //metto a zero AS2 per non usare al clock
  TIMSK2 &= ~(1 << OCIE2A);                 //metto a zero OCIE2A per abilitare l'interrupt del compare macht A, interrupt fortnito dal comparatore fra tcnt2 e TOP (normal mode)
  TCCR2B |= (1 << CS22);                    //setto i CS2x a 111 per impostare 1024
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  tcnt2 = 0;                                //da cambiare nel caso si volesse cambiare la velocità
}

void startTimer()
{
  if (!(TIMSK2 && B00000001))
  {
    TCNT2 = tcnt2;          //imposto il contatore
    TIMSK2 |= (1 << TOIE2); //setto a uno il "timer overflow interrupt enable
  }
}

ISR(TIMER2_OVF_vect) //routine chiamata quando avviene il match con il TOP
{
  TCNT2 = tcnt2;    //riporto il counter al valore iniziale da cui voglio farlo partire
  contTimer++;
  if (contTimer == 300) { //4 SECONDI
    flagTimer = true;
    contTimer = 0;
  }
  //TIMSK2 &= ~(1 << TOIE2); //disabilito l'interrupt overflow per stoppare il contatore
}
