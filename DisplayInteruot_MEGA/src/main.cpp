#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

volatile bool flag2 = false;
volatile bool flag3 = false;
volatile bool flag18 = false;

volatile unsigned long pressStartTime = 0;

const int SoundPin = 5;

int64_t Current_TimeStamp_1;
int64_t Current_TimeStamp_2;
int64_t Current_TimeStamp_3;

int password_Check[4] = {1,2,2,1}; 
int passwordCheck(){return(password_Check[3]*1000+password_Check[2]*100+password_Check[1]*10+password_Check[0]);}
int password_Now[4] ;
int passwordNow(){return(password_Now[3]*1000+password_Now[2]*100+password_Now[1]*10+password_Now[0]);}
String password = String(password_Now[0])+ " "+ String(password_Now[1]) + " " +String(password_Now[2])+" "+String(password_Now[3]) ;
int password_count = 0 ;


LiquidCrystal_I2C lcd(0x27, 16, 2);  // (address, columns, rows)


///  สร้างฟังก์ชันสำหรับปุ่ม Interupt    ///

void isr2() {
  flag2 = true;
}

void isr3() {
  flag3 = true;
}

void isr18() {
  flag18 = true;
}
///  สร้างฟังก์ชันหน้าต่าง   ///
  void SetDisplay(String UpString,String DownString){
    lcd.clear();
    lcd.setCursor((16-UpString.length())/2,0);
    lcd.print(UpString);
    lcd.setCursor((16-DownString.length())/2,1);
    lcd.print(DownString);
  }



  int16_t Previos_Page = 0 ;
  int16_t Current_Page = 0 ;
  int16_t Next_Page = 0 ;

  class windows{
    private :
      void CussorBlinkON(){lcd.blink_on();}
      void CussorBlinkOFF(){lcd.blink_off();}
      void SetCursor(int x , int y){lcd.setCursor(x,y);}

    public :

      void ReDisplay_1(int Page){
        switch(Page){
          case -1 : {Current_Page = 0 ;break;}
          case 0 : {SetDisplay("Charge State","Batt_ __.__A");break;}
          case 1 : {SetDisplay("Source","__.__ V __.__ A");break;}
          case 2 : {SetDisplay("Battery 1","__.__ V __._%"); Next_Page = 21 ; break;}
          case 3 : {SetDisplay("Battery 2","__.__ V __._%"); Next_Page = 31 ; break;}
          case 4 : {SetDisplay("Battery 3","__.__ V __._%"); Next_Page = 41 ; break;}
          case 5 : {SetDisplay("Battery 4","__.__ V __._%"); Next_Page = 51 ; break;}
          case 6 : {SetDisplay("Load","__.__ V __.__ A") ; break;}
          case 7 : {SetDisplay("Setting","  Enter <--"); Next_Page = 80 ;break;}
          case 8 : {Current_Page = 7;break;}

          case 20 : {Current_Page = 21;break;}
          case 21 : {SetDisplay("Batt Voltage 1","__.__ V") ; break;}
          case 22 : {SetDisplay("Batt Current 1","__.__ V") ; break;}
          case 23 : {SetDisplay("Batt SOC 1"," __._ %") ; break;}
          case 24 : {SetDisplay("Batt SOH 1"," __._ %") ; break;}
          case 25 : {SetDisplay("Batt Temp 1","__._ C") ; break;}
          case 26 : {Current_Page = 25;Serial.println(Current_Page);break;}

          case 30 : {Current_Page = 31;break;}
          case 31 : {SetDisplay("Batt Voltage 2","__.__ V") ; break;}
          case 32 : {SetDisplay("Batt Current 2","__.__ V") ; break;}
          case 33 : {SetDisplay("Batt SOC 2"," __._ %") ; break;}
          case 34 : {SetDisplay("Batt SOH 2"," __._ %") ; break;}
          case 35 : {SetDisplay("Batt Temp 2","__._ C") ; break;}
          case 36 : {Current_Page = 35; Serial.println(Current_Page);break;}

          case 40 : {Current_Page = 41;break;}
          case 41 : {SetDisplay("Batt Voltage 3","__.__ V") ; break;}
          case 42 : {SetDisplay("Batt Current 3","__.__ V") ; break;}
          case 43 : {SetDisplay("Batt SOC 3"," __._ %") ; break;}
          case 44 : {SetDisplay("Batt SOH 3"," __._ %") ; break;}
          case 45 : {SetDisplay("Batt Temp 3","__._ C") ; break;}
          case 46 : {Current_Page = 45;Serial.println(Current_Page);break;}

          case 50 : {Current_Page = 51;break;}
          case 51 : {SetDisplay("Batt Voltage 4","__.__ V") ; break;}
          case 52 : {SetDisplay("Batt Current 4","__.__ V") ; break;}
          case 53 : {SetDisplay("Batt SOC 4"," __._ %") ; break;}
          case 54 : {SetDisplay("Batt SOH 4"," __._ %") ; break;}
          case 55 : {SetDisplay("Batt Temp 4","__._ C") ; break;}
          case 56 : {Current_Page = 55;Serial.println(Current_Page);break;}

          case 80 : { SetDisplay("Enter Password",password) ;
                      SetCursor(password_count*2+4 , 1);
                      CussorBlinkON(); 
                      break;
                    }
          case 81 : {Current_Page = 82 ; break;}
          case 82 : {SetDisplay("Wifi","Setting <--") ; Next_Page = 110; break;}    
          case 83 : {SetDisplay("Batt 1","Setting <--") ; Next_Page = 120; break;} 
          case 84 : {SetDisplay("Batt 2","Setting <--") ; Next_Page = 130; break;}
          case 85 : {SetDisplay("Batt 3","Setting <--") ; Next_Page = 140; break;}           
          case 86 : {SetDisplay("Batt 4","Setting <--") ; Next_Page = 150; break;}            
          case 87 : {SetDisplay("Chossing","Setting <--") ; Next_Page = 160; break;}           
          case 88 : {Current_Page = 87 ; break;}

        }
      }
  };


///  สร้างฟังก์ปุ่มกด   ///


  windows window;
  void Button1Pressed(){
    switch (Current_Page)
    {
    case 80:
      if(password_Now[password_count]>0){password_Now[password_count] -= 1;}
      password = String(password_Now[0])+ " "+ String(password_Now[1]) + " " +String(password_Now[2])+" "+String(password_Now[3]);
      window.ReDisplay_1(Current_Page);
      break;
    
    default:
      Current_Page -= 1 ;
      Serial.println(Current_Page);
      window.ReDisplay_1(Current_Page);
      break;
    }
  }
  void Button1Hold(){
    
    SetDisplay("Button 1","Hold");
  }
  void Button2Pressed(){
    switch (Current_Page)
    {
    case 80:
      if(password_Now[password_count]<9){password_Now[password_count] += 1;}
      password = String(password_Now[0])+ " "+ String(password_Now[1]) + " " +String(password_Now[2])+" "+String(password_Now[3]);
      window.ReDisplay_1(Current_Page);
      break;
    
    default:
      Current_Page += 1 ;
      Serial.println(Current_Page);
      window.ReDisplay_1(Current_Page);
      break;
    }
  
    
  }
  void Button2Hold(){
    
    SetDisplay("Button 2","Hold");
  }
  void Button3Pressed(){
    switch (Current_Page)
    {
    case 80:
      password_count+=1;
      if(password_count == 4){
        password_count = 0;
        if(passwordNow() == passwordCheck()){
          Current_Page = 82;
        }
        password_Now[0] = 0;password_Now[1] = 0;password_Now[2] = 0;password_Now[3] = 0;
        password = String(password_Now[0])+ " "+ String(password_Now[1]) + " " +String(password_Now[2])+" "+String(password_Now[3]);
      }
      window.ReDisplay_1(Current_Page);
      
      break;
    
    default:
      Previos_Page = Current_Page;
      Current_Page = Next_Page ;
      window.ReDisplay_1(Current_Page);
      Serial.println(Current_Page);
      break;
    }
  }
  void Button3Hold(){
    
    switch (Current_Page)
    {
    case 80:
      
      break;
    
    default:
      Next_Page = Current_Page;
      Current_Page = Previos_Page ;
      window.ReDisplay_1(Current_Page);
      Serial.println(Current_Page);
      break;
    }
    
  }


///  เริ่มการทำงาน    ///

void setup() {
  lcd.init();          // เริ่มต้น LCD
  lcd.backlight();      // เปิดไฟพื้นหลัง
  lcd.clear();          // ล้างหน้าจอ
  

  SetDisplay("LSC Module   ","   Welcome >_<");
  delay(800);
  lcd.clear();
  window.ReDisplay_1(Current_Page);


  Serial.begin(9600);

  // ตั้งค่าปุ่มให้เป็น INPUT_PULLUP
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(SoundPin, OUTPUT);

  // ผูก interrupt กับขา
  attachInterrupt(digitalPinToInterrupt(2), isr2, FALLING);    // Interrupt 0
  attachInterrupt(digitalPinToInterrupt(3), isr3, FALLING);    // Interrupt 1
  attachInterrupt(digitalPinToInterrupt(18), isr18, FALLING);  // Interrupt 5
}

void loop() {

   if (flag2) {
    digitalWrite(SoundPin,1);
    Current_TimeStamp_1 = millis();
    while(digitalRead(2) == LOW){}
    if(millis()-Current_TimeStamp_1 < 1000) { Button1Pressed();}
    else{ Button1Hold(); }
    digitalWrite(SoundPin,0);
    flag2 = false;
  } 

  if (flag3) {
    digitalWrite(SoundPin,1);
    Current_TimeStamp_2 = millis();
    while(digitalRead(3) == LOW){}
    if(millis()-Current_TimeStamp_2 < 1000) { Button2Pressed();}
    else{ Button2Hold(); }
    digitalWrite(SoundPin,0);
    flag3 = false;
  }
  if (flag18) {
    Current_TimeStamp_3 = millis();
    while(digitalRead(18) == LOW){}
    if(millis()-Current_TimeStamp_3 < 1000) { Button3Pressed();}
    else{ Button3Hold(); }
    flag18 = false;
  }
}

