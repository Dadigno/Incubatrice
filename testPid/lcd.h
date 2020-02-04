
/************DISPLAY*************/
byte downArrow[] = {
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B10101,
    B01110,
    B00100};

byte upArrow[] = {
    B00100,
    B01110,
    B10101,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100};

byte nullC[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000};

byte arrowT = 0;
byte arrowH = 0;
volatile bool flag_time = false;

LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void init_lcd(){
  lcd.begin(20, 4);
  lcd.createChar(0, upArrow);
  lcd.createChar(1, downArrow);
  lcd.createChar(2, nullC);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("____Incubatrice_____");
}

void refreshLcd(float temp, float hum, float oldTemp, float oldHum)
{
  if (int(temp * 100) > int(oldTemp * 100))
    {
      arrowT = byte(0);
    }
    else if (temp < oldTemp)
    {
      arrowT = byte(1);
    }
    else
    {
      arrowT = byte(2);
    }
    
    if (int(hum * 100) > int(oldHum * 100))
    {
      arrowH = byte(0);
    }
    else if (hum < oldHum)
    {
      arrowH = byte(1);
    }
    else
    {
      arrowH = byte(2);
    }
    
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
