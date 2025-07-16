#include <Arduino.h>
#include <SPI.h>

const int slaveCS = 53; // ขา CS (Slave Select)

bool checkSPISlave() {
  byte received;

  digitalWrite(slaveCS, LOW);  // เลือกอุปกรณ์
  delayMicroseconds(10);       // รอให้ Stable

  received = SPI.transfer(0x55); // ส่งข้อมูลทดสอบ

  digitalWrite(slaveCS, HIGH); // ยกเลิกเลือก

  // เช็คค่าที่ตอบกลับ
  if (received != 0x00 && received != 0xFF) {
    return true;  // ได้ค่าบางอย่างกลับมา แปลว่ามี Slave ตอบ
  } else {
    return false; // อาจไม่มีอุปกรณ์ต่อ
  }
}

void setup() {
  Serial.begin(9600);

  // เริ่ม SPI
  SPI.begin();
  pinMode(slaveCS, OUTPUT);
  digitalWrite(slaveCS, HIGH); // ไม่เลือก Slave ไว้ก่อน

  delay(1000);
  Serial.println("เริ่มตรวจสอบ Slave SPI...");

  bool found = checkSPISlave();

  if (found) {
    Serial.println("✅ พบอุปกรณ์ SPI Slave เชื่อมต่ออยู่!");
  } else {
    Serial.println("❌ ไม่พบการตอบสนองจาก SPI Slave");
  }
}

void loop() {
  // ไม่ต้องทำอะไร
}


