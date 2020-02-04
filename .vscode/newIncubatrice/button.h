init_button() {
  pinMode(PIN_BT1, INPUT);
  pinMode(PIN_BT2, INPUT);
}
short state = 0;
byte st;
byte old_st;

button_hanlder() {
  st |= (digitalRead(PIN_BT1) << 0);
  st |= (digitalRead(PIN_BT2) << 1);
  Serial.println(st,BIN); 
  if(state == 0){
    state++;
  }else if(state == 1 && old_st == st){
    state = 0;
    switch(st){
      case 1:
      //aumenta
      Setpoint += 0.1;
      break;
      case 2:
      Setpoint -= 0.1;
      //diminuisci
      break;
    } 
  }
  old_st = st;
  st = 0;
}
