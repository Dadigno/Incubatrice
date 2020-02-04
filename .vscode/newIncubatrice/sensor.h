#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(PIN_DHT, DHTTYPE);



void init_dht(){
  dht.begin();
}

double read_hum(){
  return dht.readHumidity();
}

double read_temp(){
  return dht.readTemperature();
}
