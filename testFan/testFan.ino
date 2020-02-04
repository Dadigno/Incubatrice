void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("avanti");
  for(int i = 0; i <= 255; i+=1){
    analogWrite(9,i);
    delay(100);
  }
  delay(4000);
  Serial.println("indietro");
  for(int i = 255; i >= 0; i-=1){
    analogWrite(9,i);
    delay(100);
  }
  delay(4000);

}
