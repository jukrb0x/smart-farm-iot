/*
  Smart Farm System
*/
#include <LiquidCrystal.h>
#include <math.h>


#define LIGHT 7
#define TMP36 A5
#define PHOTO_R A2
#define MOISTURE A3
#define FAN 9
#define LED_G A0
#define LED_R A1

// lcd pin = uno pin
const int rs = 12,
  en = 11,
  d4 = 5,
  d5 = 4,
  d6 = 3,
  d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
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
  pinMode(PHOTO_R, INPUT);

  // light bulb
  pinMode(LIGHT, OUTPUT);
  // LED

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
  //delay(2000);
  lcd.clear();
  digitalWrite(LIGHT, LOW);

}

void loop() {

  float celsius, lightness, moisture;
  float temperatureRaw;

  // gathering data
  for (int i = 0; i <= 100; i++) {
    moisture = moisture + analogRead(MOISTURE);
    temperatureRaw = temperatureRaw + analogRead(TMP36);
    lightness = lightness + analogRead(PHOTO_R);
    delay(1);
  }
  temperatureRaw = temperatureRaw / 100.0;
  celsius = map(temperatureRaw, 20, 358, -40, 125);
  moisture = moisture / 100.0;
  lightness = lightness / 100.0;
  lcd.setCursor(0, 0);
  lcd.print("T:      ");
  lcd.setCursor(2, 0);
  lcd.print(celsius);
  lcd.setCursor(6, 0);
  lcd.print(" ");

  // Actions
  // -----------
  // Env Lightness
  // lightness < 400 ? night : daytime
  digitalWrite(LIGHT, LOW);
  if (lightness < 400) {
    digitalWrite(LIGHT, HIGH);
    lcd.setCursor(15, 0);
    lcd.print("N");
  } else {
    lcd.setCursor(15, 0);
    lcd.print("D");

  }

  // -----------
  // Env Temperature
  lcd.setCursor(7, 0);
  lcd.print("FAN:OFF");
  analogWrite(FAN, 0);
  if (celsius > 27.0) {
    analogWrite(FAN, 255);
    lcd.setCursor(7, 0);
    lcd.print("FAN:ON ");
  }

  // -----------
  // Soil Moisture
  lcd.setCursor(0, 1);
  lcd.print("MTR:");
  lcd.print((int) moisture);
  lcd.setCursor(8, 1);
  lcd.print("IRG:   ");
  analogWrite(LED_G, 0);
  analogWrite(LED_R, 0);
  if (moisture < 900.0)
  // the sensor in tinkercad max at aournd 983
  {

    lcd.setCursor(8, 1);
    lcd.print("IRG:ON ");
    analogWrite(LED_G, 255);
    analogWrite(LED_R, 0);
  } else {
    lcd.setCursor(8, 1);
    lcd.print("IRG:OFF");
    analogWrite(LED_G, 0);
    analogWrite(LED_R, 255);
  }
  delay(500);
}
