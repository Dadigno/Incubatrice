#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(PIN_DHT, DHTTYPE);

double temp = 0, hum = 0, oldTemp = 0, oldHum = 0;

void init_dht(){
  dht.begin();
  
}

double read_dht(){
  oldHum = hum;
  oldTemp = temp;
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  refreshLcd(temp, hum, oldTemp, oldHum); 
  return temp;
}
