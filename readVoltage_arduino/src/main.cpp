#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

Adafruit_ADS1115 ads;

const int analogPin = A0;
int16_t analogValue;
int mode;
float Voltage ;
int count = 0;
int now = millis();


void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Started to read");
  mode = millis();
  if (!ads.begin()) {
    Serial.println("ไม่พบโมดูล ADS1115. ตรวจสอบการเชื่อมต่อ I2C.");
    while (1);

  }
  ads.setGain(GAIN_SIXTEEN); // GAIN_ONE = +/-4.096V
  Serial.println("เริ่มต้นใช้งาน ADS1115 แบบ Single-Ended");
  now = millis();
}


void loop() {

  if ( millis() - now < 1000){
  analogValue = ads.readADC_Differential_0_1();
  count += 1;
  }
  else{ 
    Serial.println(count);
    count = 0;
    now = millis();
  }
}