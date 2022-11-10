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

byte customCharPlaying[8] = {
        0b11000,
        0b11100,
        0b11110,
        0b11111,
        0b11111,
        0b11110,
        0b11100,
        0b11000
};

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
    // irrigation indicator (LED)
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);

    // cooling system (motor fan)
    pinMode(FAN, OUTPUT);

    // ---------------------------
    // LCD setups
    lcd.begin(16, 2);
    lcd.print("SmartFarm System");
    lcd.setCursor(0, 1);
    lcd.print("--- Welcome ---");
    // LCD custom character
    lcd.createChar(0, customCharPlaying);
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
    lcd.setCursor(15, 1);
    lcd.write((byte) 0); // playing character
    delay(1000); // working frequency
    lcd.setCursor(15, 1);
    lcd.print(" ");
    float celsius, lightness, moisture;
    float temperatureRaw;

    // DATA GATHERING
    //in average number for accuracy
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

    // display temperature
    lcd.setCursor(0, 0);
    lcd.print("T:      ");
    lcd.setCursor(2, 0);
    lcd.print((int) celsius);
    lcd.setCursor(5, 0);
    lcd.print("  ");

    // SMART FARM ACTIONS
    // -----------
    // Env Lightness
    // -----------
    // lightness < 400 ? night : daytime
    // analog range [6,692]
    if (lightness < 400) {
        // lightbulb ON
        digitalWrite(LIGHT, HIGH);
        lcd.setCursor(14, 0);
        lcd.print("NI");
    } else {
        // lightbulb OFF
        digitalWrite(LIGHT, LOW);
        lcd.setCursor(14, 0);
        lcd.print("DA");
    }

    // -----------
    // Env Temperature
    // Cooling system
    // -----------
    lcd.setCursor(6, 0);
    lcd.print("FAN:   ");
    if (celsius > 27.0) {
        analogWrite(FAN, 155);
        lcd.setCursor(6, 0);
        lcd.print("FAN:L1 ");
        if (celsius > 40.0) {
            analogWrite(FAN, 255);
            lcd.setCursor(6, 0);
            lcd.print("FAN:L2 ");
        }
    } else {
        analogWrite(FAN, 0);
        lcd.setCursor(6, 0);
        lcd.print("FAN:OFF ");
    }

    // -----------
    // Soil Moisture
    // Irrigation system
    // -----------
    lcd.setCursor(0, 1);
    lcd.print("MTR:    ");
    lcd.setCursor(4, 1);
    lcd.print((int) moisture);
    lcd.setCursor(8, 1);
    lcd.print("IRG:   ");
    if (moisture < 900.0)
        // the sensor in tinkercad max at aournd 893
    {
        lcd.setCursor(8, 1);
        lcd.print("IRG:ON "); // Green LED ON
        analogWrite(LED_G, 255);
        analogWrite(LED_R, 0);
    } else {
        lcd.setCursor(8, 1);
        lcd.print("IRG:OFF"); // Red LED ON
        analogWrite(LED_G, 0);
        analogWrite(LED_R, 255);
    }
}
