/*
  Smart Farm
*/
#include <LiquidCrystal.h>
#define TMP36_VAL A5
// #define 

// lcd pin = uno pin
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  // debug
  Serial.begin(9600);
  
  // set lcd cols and rows
  lcd.begin(16, 2);
  lcd.print("SmartFarm System");
  
  // soil moisture sensor
  pinMode();
  
  // tempature sensor
  pinMode(TMP36_VAL, INPUT);
  
  // motor (fan) -- cooling system
  
  // irrigation (LED)
  
  
}

void loop()
{
  lcd.setCursor(0, 1);
  lcd.print("SmFS");
  // 338/165 = 2.048
  float temperature;
  temperature = map(analogRead(TMP36_VAL), 20, 358, -40, 125);
  Serial.println(temperature);
}
