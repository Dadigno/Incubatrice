
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

#include <LiquidCrystal.h>
LiquidCrystal lcd(9, NULL, 8, 4, 5, 6, 7);
const int analogOutpin = 10;
int year_=0;
int month_=0;
int day_=0;
int hour_=0;
int minute_=0;
int second_=0;
   
const int bt1 = A0;      //INPUT
const int bt2 = A1;
const int bt3 = A2;     
const int bt4 = A3;

int button=0;
int button_web=0;
int bt1state = 0;         
int bt2state = 0; 
int bt3state = 0; 
int bt4state = 0; 
int bt1_n=0;

const int out1 = 2;    //OUTPUT
const int out2 = 3;
const int out3 = 11;
const int out4 = 12;

struct prog_1 { 
  int type;     //indentificatore del tipo di programma
  int out; 
  int inter;
  int minute_;  
 };
 prog_1 variable = { 0 , 0 , 0 , 00};
int program[4];
/*struct prog_2 {
  int type;
  int out;
  int start;
  int finish;
};
 prog_2 variable2 = { 0 , 0 , 0 , 0};*/
 
int prog_selected=0;
void setup()  
{ 
  Serial.begin(9600);
  analogWrite (analogOutpin, 20);
  lcd.begin(16,2);
  lcd.clear();
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(bt3, INPUT);
  pinMode(bt4, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  digitalWrite(out1,HIGH);
  digitalWrite(out2,HIGH);
  
  #ifdef AVR
  Wire.begin();
  #else
  Wire1.begin(); 
  #endif
  rtc.begin(); 
   // rtc.adjust(DateTime(2016, 12, 12, 18, 41, 0));


  lcd.clear();
  lcd.print("___ORENGDUINO___");
  lcd.setCursor(0,1);
  lcd.print(" Temporizzatore ");
  Serial.println("Connesso");
}





void menu()
{  
   lcd.clear();
   lcd.print("------MODE------");
   while(1){
    select_bt();
    if (button==4 || button_web==52){
      switch(bt1_n){
       case 1:
        manual();  //manuale, consente controllare singolarmente ogni uscita (totale uscite 4)
        break;
       case 2:
        //select_program();    //seleziona programma
        break;
       case 3:
        new_program();       //crea programma
        break;
       case 4:               //mostra ora
        show_time();
        break;
       case 5:       //avvio programma
        play();
        break;
       case 6:
        lcd.clear();
        loop();
        break;
        }
       }
   if (button==1 || button_web==49){
     bt1_n=bt1_n+1;
     switch(bt1_n){
      case 1:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("------MODE------");
       lcd.setCursor(0,1);
       lcd.print("Manual");
       Serial.println("Manual");
       break;
      case 2:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("------MODE------");
       lcd.setCursor(0,1);
       lcd.print("Select Program");
       Serial.println("Select Program");
       break;
      case 3:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("------MODE------");
       lcd.setCursor(0,1);
       lcd.print("New Program");
       Serial.println("New Program");
       break;
      case 4:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("------MODE------");
       lcd.setCursor(0,1);
       lcd.print("Show time");
       Serial.println("Show time");
       break;
      case 5:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("------MODE------");
       lcd.setCursor(0,1);
       lcd.print("Play");
       Serial.println("Play");
       break;
      case 6:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("------MODE------");
       lcd.setCursor(0,1);
       lcd.print("Back");
       Serial.println("Back");
       break;
      case 7:
       bt1_n=0;
       break;
      }
     }
     
     delay(200);
     button=0;
     button_web=0;
    }
    
}


  
void select_bt(){
  button_web=Serial.read();
  bt1state = digitalRead(bt1);
  bt2state = digitalRead(bt2);
  bt3state = digitalRead(bt3);
  bt4state = digitalRead(bt4);
if(bt1state==HIGH){
  button = 1;
  }
  else{
    if(bt2state==HIGH){
      button = 2;
      }
      else{
        if(bt3state==HIGH){
          button = 3;
          }
          else{
            if(bt4state==HIGH){
              button = 4;
              }}}}
              
}
              
void manual(){
   lcd.clear();
   lcd.print("-----MANUAL-----");
   bt1_n=0;
   while(1){
    select_bt();
    if (button==2 || button_web==50){
      switch(bt1_n){
       case 1:        //RELE
        digitalWrite(out1, HIGH);  
        break;
       case 2:
        digitalWrite(out2, HIGH);   
        break;
       case 3:  
        digitalWrite(out3, HIGH);
        break;
       case 4:  
        digitalWrite(out4, HIGH);
        break;
        }
       }
     else{
       if(button==3 || button_web==51){
         switch(bt1_n){
           case 1:        //RELE
            digitalWrite(out1, LOW);  
            break;
           case 2:
            digitalWrite(out2, LOW);   
            break;
           case 3:  
            digitalWrite(out3, LOW);
            break;
           case 4:  
            digitalWrite(out4, LOW);
            break;
           }
         }
       }
      if (button==4 && bt1_n==5 || button_web==49 && bt1_n==5){
        button=0;
        button_web=0;
        bt1_n=0;
        menu();
        }
   if (button==1 || button_web==49){
     bt1_n=bt1_n+1;
     switch(bt1_n){
      case 1:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-----MANUAL-----");
       lcd.setCursor(0,1);
       lcd.print("Valvola 1");
       break;
      case 2:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-----MANUAL-----");
       lcd.setCursor(0,1);
       lcd.print("Valvola 2");
       break;
      case 3:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-----MANUAL-----");
       lcd.setCursor(0,1);
       lcd.print("Valvola 3");
       break;
      case 4:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-----MANUAL-----");
       lcd.setCursor(0,1);
       lcd.print("Valvola 4");
       break;
      case 5:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-----MANUAL-----");
       lcd.setCursor(0,1);
       lcd.print("Back");
       break;
      case 6:
        bt1_n=0;
        break;
       }
     }
     delay(200);
     button=0;
     button_web=0;
    }
   
} 
void display_time(){
        DateTime now = rtc.now();  // Read data from the RTC Chip
        lcd.clear();
        lcd.print(now.year(), DEC);
        lcd.print("/");
        lcd.print(now.month(), DEC);
        lcd.print("/");
        lcd.print(now.day(), DEC);
        lcd.setCursor(0,2);
        lcd.print(now.hour(), DEC);
        lcd.print(":");
        lcd.print(now.minute(), DEC);
        lcd.print(":");
        lcd.print(now.second(), DEC);
        }
void show_time()
{  lcd.clear();
   lcd.print("--Current time--");
   bt1_n=0;
   while(1){
    select_bt();
    if (button==4){
      switch(bt1_n){
       case 2:
         bt1_n=0;
         button=0;
         button_web=0;
         menu();   
        break;
         }
       }
   if (button==1 || button_web==49){
     bt1_n=bt1_n+1;
     switch(bt1_n){
      case 1:
       display_time();
       break;
      case 2:
       lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("Back");
       break;
      case 3:
       bt1_n=0;
       break;
       }
     }
    delay(200);
     button=0;
     button_web=0;
    }
 
}
void read_time()
{
  DateTime now = rtc.now();
  year_=now.year();
  month_=now.month();
  day_=now.day();
  hour_=now.hour();
  minute_=now.minute();
  second_=now.second();
  delay(10);
}

void new_program()
{
   bt1_n=0;
   lcd.clear();
   lcd.print("--New  Program--");
   lcd.setCursor(0,1);
   lcd.print("Select output");
   while(1){
    select_bt();
    if (button==4 || button_web==52){
      switch(bt1_n){
       case 1:
       program[1]=2;
       select_start();
       //new_program_inter();
        break;
       case 2:
       program[1]=3;
       select_start();
       //new_program_inter();
        break;
        case 3:  
        break;
       case 4:  
        break;
       case 5:
         lcd.clear();
         loop();
         break;
        }
       }
   if (button==1 || button_web==49){
     bt1_n=bt1_n+1;
     switch(bt1_n){
      case 1:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("--New  Program--");
       lcd.setCursor(0,1);
       lcd.print("Out 1");
       break;
      case 2:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("--New  Program--");
       lcd.setCursor(0,1);
       lcd.print("Out 2");
       break;
      case 3:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("--New  Program--");
       lcd.setCursor(0,1);
       lcd.print("Out 3");
       break;
      case 4:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("--New  Program--");
       lcd.setCursor(0,1);
       lcd.print("Out 4");
       break;
      case 5:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("--New  Program--");
       lcd.setCursor(0,1);
       lcd.print("Back");
       break;
      case 6:
       bt1_n=0;
       break;
      }
     }
     delay(200);
     button=0;
     button_web=0;
    }
}

void select_start(){
   bt1_n=0;
   button=0;
   lcd.clear();
   lcd.print("--New  Program--");
   lcd.setCursor(0,1);
   lcd.print("Select start");
   int val=0;
   delay(1000);
   while(1){
     select_bt();
    if (button==2 || button_web==50){
       if(val==23){
        val=0;
         }
       else{ val=val+1;}
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("--New  Program--");
       lcd.setCursor(0,1);
       lcd.print(val);
      }
     else {
       if (button==3 || button_web==51){
         if(val==0){
         val=23;
           }
         else{ val=val-1;}
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("--New  Program--");
         lcd.setCursor(0,1);
         lcd.print(val);
      }
      else {
        if (button==4 || button_web==52){
         program[2]=val;
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("--New  Program--");
         lcd.setCursor(0,1);
         lcd.print("time=");
         lcd.print(val);
         delay(2000);
         select_finish();
       }
         }
          }
     delay(200);
     button=0;
     button_web=0;    
     }
     
}
  
void select_finish(){
   bt1_n=0;
   button=0;
   lcd.clear();
   lcd.print("--New  Program--");
   lcd.setCursor(0,1);
   lcd.print("Select finish");
   int val=0;
   delay(1000);
   while(1){
     select_bt();
    if (button==2 || button_web==50){
       if(val==23){
        val=0;
         }
       else{ val=val+1;}
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("--New  Program--");
       lcd.setCursor(0,1);
       lcd.print(val);
      }
     else {
       if (button==3 || button_web==51){
         if(val==0){
         val=23;
           }
         else{ val=val-1;}
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("--New  Program--");
         lcd.setCursor(0,1);
         lcd.print(val);
      }
      else {
        if (button==4 || button_web==52){
         program[3]=val;
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("--New  Program--");
         lcd.setCursor(0,1);
         lcd.print("minute=");
         lcd.print(val);
         delay(2000);
         menu();
       }
         }
          }
     delay(200);
     button=0; 
     button_web=0;   
     }
     
}




void select_program()
{
   bt1_n=0;
   lcd.clear();
   lcd.print("--Set Program--");
   lcd.setCursor(0,1);
   lcd.print("Select program");
   while(1){
    select_bt();
    if (button==4 || button_web==52){
      switch(bt1_n){
       case 1:
        prog_selected=1;
        break;
       case 2:
        prog_selected=2;
        break;
       case 3:
        prog_selected=3;
        break;
       case 4:
        prog_selected=4;
        break;
       case 5:
         lcd.clear();
         loop();
         break;
        }
       }
   if (button==1 || button_web==49){
     bt1_n=bt1_n+1;
     switch(bt1_n){
      case 1:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-Select Program-");
       lcd.setCursor(0,1);
       lcd.print("Programma 1");
       break;
      case 2:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-Select Program-");
       lcd.setCursor(0,1);
       lcd.print("Programma 2");
       break;
      case 3:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-Select Program-");
       lcd.setCursor(0,1);
       lcd.print("Programma 3");
       break;
      case 4:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-Select Program-");
       lcd.setCursor(0,1);
       lcd.print("Programma 4");
       break;
      case 5:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("-Select Program-");
       lcd.setCursor(0,1);
       lcd.print("Back");
       break;
      case 6:
       bt1_n=0;
       break;
      }
     }
     delay(200);
     button=0;
     button_web=0;
    }
}

void play(){
lcd.clear();
lcd.print("___ORENGDUINO___");
lcd.setCursor(0,1);
lcd.print("_-_-AVVIATO!-_-_");

  while(1){
    read_time();
    Serial.print(hour_);
    Serial.print("  ");
    Serial.print(program[1]);
    Serial.print("  ");
    Serial.print(program[2]);
    Serial.print("  ");
    Serial.println(program[3]);
    if(hour_==program[2]){
      digitalWrite(program[1], LOW);
      }else{if(hour_==program[3]){
        digitalWrite(program[1], HIGH);
        }
       }
}
}



void loop(){
  lcd.clear();
  select_bt();
  Serial.println(button_web);
  lcd.print("___ORENGDUINO___");
  lcd.setCursor(0,1);
  lcd.print(" Temporizzatore ");
  delay(100);
  if(button==1 || button_web==49){
    while(1){
      menu();
    }
  }
}
 
  



