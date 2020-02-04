
/***********************
 * Configuration basic *
 **********************/
#define SERIAL_PORT 0
#define BAUDRATE 9600
#define POWER_SUPPLY
#define NAME_MACHINE "Incubatrice iot"

/***********************
 *      Systems        *
 **********************/
#define LAMP
#define LCD_SCREEN
#define ESP
#undef ESP
#define FAN
#define PID_CONTROL
#define DHT_SENSOR
#define DHT_HUM
#define DHT_TEMP

#undef TIMER_COUNTER
#define TIMER_COUNTER


/***********************
 *     Pin setup       *
 **********************/


#define PIN_DHT 8
#define PIN_LIGHT 12
#define PIN_DHT_PW 4
#define PIN_FAN 9
#define SCL A5
#define SDA A4
//#define ESP_TX 2
//#define ESP_RX 4
#define PIN_ZC 2
#define PIN_TIME 3


/********************
 *  Basic library   *
 *******************/

 #include <Wire.h>
