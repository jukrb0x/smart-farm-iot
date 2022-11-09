/*
  Smart Farm System
*/
#include <LiquidCrystal.h>

#define TMP36 A5
#define LIGHT 7
#define PhotoR A2


// lcd pin = uno pin
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  // debug at 9600 bps
  Serial.begin(9600);
  
  // LCD: set cols and rows
  lcd.begin(16, 2);
  lcd.print("SmartFarm System");
  lcd.setCursor(0, 1);
  lcd.print("Welcome");
  delay(2000);
  lcd.clear();
  
  // soil moisture sensor
 // pinMode();
  
  // tempature sensor
  pinMode(TMP36, INPUT);
  
  // photoresistor
  // Analog signal range: [6,679]
  pinMode(PhotoR, INPUT);
  
  // light bulb
  pinMode(LIGHT, OUTPUT);
  
  
  // cooling system (motor fan)
  
  // irrigation indicator (LED)
  
  
  // LCD: print data

//       digitalWrite(LIGHT, HIGH);
}

void loop()
{
  float temperature, lighteness, moisture;
  lcd.setCursor(0, 1);
  lcd.print("SmFS");
  // 338/165 = 2.048

  temperature = map(analogRead(TMP36), 20, 358, -40, 125);
  // Serial.println(temperature);
  lcd.setCursor(5,1);
  Serial.println(analogRead(PhotoR));

  delay(1000);
  digitalWrite(LIGHT, LOW);
   delay(1000);
  digitalWrite(LIGHT, HIGH);
}
