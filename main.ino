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

void(* resetBoard) (void) = 0; // software reset

void setup() {
  delay(1000);
  // debug at 9600 bps
  Serial.begin(9600);
  // ---------------------------
  pinMode(A4, INPUT);

  // soil moisture sensor
  // -- signal range: [0,876]
  pinMode(MOISTURE, INPUT);

  // temperature sensor
  // -- signal range: [20,365]
  pinMode(TMP36, INPUT);

  // photoresistor
  pinMode(PHOTO_R, INPUT);

  // light bulb
  pinMode(LIGHT, OUTPUT);
  // LED
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);

  // cooling system (motor fan)

  // irrigation indicator (LED)

  // LCD: print data

  // ---------------------------
  // LCD: set cols and rows
  lcd.begin(16, 2);
  lcd.print("SmartFarm System");
  lcd.setCursor(0, 1);
  lcd.print("--- Welcome ---");
  // light testing
  digitalWrite(LIGHT, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_R, HIGH);
  delay(2000);
  lcd.clear();
  // reset
  digitalWrite(LIGHT, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, LOW);

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
  celsius = map(temperatureRaw, 20, 365, -40, 125);
  moisture = (moisture * 1.1) / 100.0;
  lightness = lightness / 100.0;
  lcd.setCursor(0, 0);
  lcd.print("T:      ");
  lcd.setCursor(2, 0);
  lcd.print((int)celsius);
  lcd.setCursor(5, 0);
  lcd.print("  ");

  // Actions
  // -----------
  // Env Lightness
  // lightness < 400 ? night : daytime
  // analog range [6,692]
  digitalWrite(LIGHT, LOW);
  if (lightness < 400) {
    digitalWrite(LIGHT, HIGH);
    lcd.setCursor(14, 0);
    lcd.print("NI");
  } else {
    lcd.setCursor(14, 0);
    lcd.print("DA");

  }

  // -----------
  // Env Temperature
  lcd.setCursor(6, 0);
  lcd.print("FAN:   ");
  analogWrite(FAN, 0);
  if (celsius > 27.0) {
    analogWrite(FAN, 255);
    lcd.setCursor(6, 0);
    lcd.print("FAN:ON ");
  } else {
    lcd.setCursor(6, 0);
    lcd.print("FAN:OFF ");
  }

  // -----------
  // Soil Moisture
  lcd.setCursor(0, 1);
  lcd.print("MTR:    ");
  lcd.setCursor(4, 1);
  lcd.print((int) moisture);
  lcd.setCursor(8, 1);
  lcd.print("IRG:   ");
  analogWrite(LED_G, 0);
  analogWrite(LED_R, 0);
  if (moisture < 900.0)
  // the sensor in tinkercad max at aournd 893
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
