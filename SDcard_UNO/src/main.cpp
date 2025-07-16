#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;  // CS อยู่ที่ขา 10

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.print("กำลังเริ่มต้น SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("✘ ล้มเหลว! เช็คสายต่อหรือ SD Card");
    return;
  }
  Serial.println("✔ สำเร็จ! SD Card ใช้งานได้");

  // ทดสอบสร้างไฟล์
  File dataFile = SD.open("test.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("สวัสดีจาก Arduino!");
    dataFile.close();
    Serial.println("✔ เขียนไฟล์สำเร็จ");
  } else {
    Serial.println("✘ ไม่สามารถเปิดไฟล์ test.txt เพื่อเขียนได้");
  }
}

void loop() {
  // ไม่ทำอะไร
}
