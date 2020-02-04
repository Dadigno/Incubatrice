


// Analog pin used to read the NTC
#define NTC_PIN               A1
// Thermistor object
THERMISTOR thermistor(NTC_PIN,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      4490,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

// Global temperature reading


double read_thermistor(){
  double temp = thermistor.read();
  return temp/10;   // Read temperature
   
}
