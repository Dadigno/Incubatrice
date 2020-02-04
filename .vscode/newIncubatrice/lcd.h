
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

double old_bedT, old_hum, old_t;

void refreshLcd(double bedT, double hum, double t)
{
  if (int(t * 100) > int(old_bedT * 100))
    {
      arrowT = byte(0);
    }
    else if (bedT < old_bedT)
    {
      arrowT = byte(1);
    }
    else
    {
      //arrowT = byte(2);
    }
    
    if (int(hum * 100) > int(old_hum * 100))
    {
      arrowH = byte(0);
    }
    else if (hum < old_hum)
    {
      arrowH = byte(1);
    }
    else
    {
      //arrowH = byte(2);
    }
    
  lcd.setCursor(0, 1);
  lcd.print("Floor T: ");
  lcd.print(bedT);
  lcd.print("C");
  lcd.setCursor(17, 1);
  lcd.write(arrowT);
  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print("%");
  lcd.setCursor(17, 2);
  lcd.write(arrowH);
  lcd.setCursor(0, 3);
  lcd.print("SP:");
  lcd.print(Setpoint);
  lcd.print(" Temp:");
  lcd.print(t);
  old_bedT = bedT;
  old_hum = hum;
  old_t = t;
  
}
