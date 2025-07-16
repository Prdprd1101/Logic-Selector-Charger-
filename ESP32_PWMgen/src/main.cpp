
#include <Esp.h> 

// กำหนดค่าคงที่
const int pwmFreq = 50000;      // ความถี่ PWM 50 kHz
const int pwmChannel = 0;       // เลือกช่อง PWM (มีได้หลายช่อง)
const int pwmResolution = 8;    // ความละเอียด 8 บิต (ค่าที่ตั้งได้คือ 0-255)
const int pwmPin = 18;          // กำหนดขา GPIO ที่ใช้ PWM

// ตั้งค่าเริ่มต้น Duty Cycle (ค่าระหว่าง 0-255)
int dutyCycle = 127;  // ประมาณ 50%

void setup() {
  // ตั้งค่า PWM
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(pwmPin, pwmChannel);

  // กำหนดค่าเริ่มต้น Duty Cycle
  ledcWrite(pwmChannel, dutyCycle);
}

void loop() {
  // ตัวอย่าง: ปรับ Duty Cycle ทีละ 10 ทุกวินาที
  dutyCycle += 10;
  if (dutyCycle > 255) dutyCycle = 0;

  ledcWrite(pwmChannel, dutyCycle);
  delay(1000);
}
