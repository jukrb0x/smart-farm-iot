/*
  Smart Farm System
*/
#include <LiquidCrystal.h>


#define LIGHT 7
#define TMP36 A5
#define PhotoR A2
#define MOISTURE A3
#define FAN 13


// lcd pin = uno pin
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  // debug at 9600 bps
  Serial.begin(9600);
  // ---------------------------
  
  // soil moisture sensor
  // -- signal range: [0,876]
  pinMode(MOISTURE, INPUT);
  
  // temperature sensor
  // -- signal range: [20,358]
  pinMode(TMP36, INPUT);
  
  // photoresistor
  pinMode(PhotoR, INPUT);
  
  // light bulb
  pinMode(LIGHT, OUTPUT);
  
  
  // cooling system (motor fan)
  
  // irrigation indicator (LED)
  
  
  // LCD: print data

  // ---------------------------
  // LCD: set cols and rows
  lcd.begin(16, 2);
  lcd.print("SmartFarm System");
  lcd.setCursor(0, 1);
  lcd.print("--- Welcome ---");
  digitalWrite(LIGHT, HIGH); // light testing
  delay(2000);
  lcd.clear();
  digitalWrite(LIGHT, LOW);
  
  
}

void loop()
{
  float celsius, lightness, moisture;
  float temperatureRaw;
  lcd.setCursor(0, 1);
  lcd.print("SmFS");
  
  // gathering data
  for (int i = 0; i <= 100; i++) 
  { 
    moisture = moisture + analogRead(MOISTURE); 
    temperatureRaw = temperatureRaw + analogRead(TMP36);
    lightness = lightness + analogRead(PhotoR);
    delay(1); 
  }
  temperatureRaw = temperatureRaw / 100.0;
  celsius = map(temperatureRaw, 20, 358, -40, 125);
  moisture = moisture / 100.0;
  lightness = lightness / 100.0;

  // Action
  // lightness < 400 ? night : daytime
  digitalWrite(LIGHT, LOW);
  if(lightness < 400)
  {
    digitalWrite(LIGHT, HIGH);
  }
  
  analogWrite(FAN, 0);
  if(celsius > 27.0)
  {
    analogWrite(FAN, 255);
  }
  
  // Print to LCD
  lcd.setCursor(5,1);


}
