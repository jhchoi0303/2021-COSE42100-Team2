#include "ADXL335.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(2, 3);
ADXL335 accelerometer;

int voice_recogn=0;
int ledpin = 8;
void setup(){
  Serial.begin(9600);                
  accelerometer.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  delay(500);
pinMode(ledpin, OUTPUT);
  mySerial.begin(9600);
  delay(500);
  mySerial.write(0xAA); // compact mode 사용
  mySerial.write(0x37);
  delay(500);
  mySerial.write(0xAA); // 그룹1 음성 명령어 imported
  mySerial.write(0x21);
  Serial.println("The settings are complete");
}
 
void loop(){

while(mySerial.available())
 {
   Serial.println("voice input");
   voice_recogn=mySerial.read();
   if (voice_recogn==21){
    digitalWrite(ledpin, HIGH);
    delay(500);
    digitalWrite(ledpin, LOW);
   }
   Serial.println(voice_recogn);
   
  
 }
 int x,y,z;
 accelerometer.getXYZ(&x,&y,&z);

  float xadc,yadc,az;
  accelerometer.getAcceleration(&xadc,&yadc,&az);
  //Serial.println("accleration of X/Y/Z: ");
  xadc = xadc * 150;
//  Serial.print(xadc);
//  Serial.println(" g");
  yadc = yadc * 150;
//  Serial.print(yadc);
//  Serial.println(" g");
//  Serial.print(az);
//  Serial.println(" g");
  delay(500);
  if(Serial.available()){         
  byte buf[5];
  byte tmp;
  tmp=Serial.readBytes(buf,5);
 
    for(int i=0;i<5;i++){
      Serial.println((int)buf[i]);
    }

  int angle1=(12-(int)buf[4])*10;
  int angle2=(12-(int)buf[3])*10;
  int angle3=(12-(int)buf[2])*10;
  int angle4=(12-(int)buf[1])*10;
  int angle5=(12-(int)buf[0])*10;
if(((angle1>=70)&&(angle1<=82))&&((angle2>=77)&&(angle2<=95))&&((angle3>=70)&&(angle3<=86))&&((angle4>=73)&&(angle4<=85))&&((angle5>=0)&&(angle5<=45)))
//Serial.println('A');
lcd.print("A");
if(((angle1>=0)&&(angle1<=10))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=12))&&((angle4>=0)&&(angle4<=10))&&((angle5>=65)&&(angle5<=80)))
//Serial.println('B');
lcd.print("B");
if(((angle1>=40)&&(angle1<=72))&&((angle2>=50)&&(angle2<=90))&&((angle3>=51)&&(angle3<=75))&&((angle4>=42)&&(angle4<=66))&&((angle5>=34)&&(angle5<=50)))
//Serial.println('C');
lcd.print("C");
if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&!(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
//Serial.println('D');
lcd.print("D");
if(((angle1>=68)&&(angle1<=88))&&((angle2>=68)&&(angle2<=90))&&((angle3>=50)&&(angle3<=80))&&((angle4>=54)&&(angle4<=80))&&((angle5>=58)&&(angle5<=88)))
//Serial.println('E');
lcd.print("E");
if(((angle1>=0)&&(angle1<=10))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=10))&&((angle4>=15)&&(angle4<=45))&&((angle5>=34)&&(angle5<=65)))
//Serial.println('F');
lcd.print("F");
if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))&&(((xadc>=400)&&(xadc<=420))&&((yadc>=340)&&(yadc<=360))))
//Serial.println('G');
lcd.print("G");
if(((angle1>=70)&&(angle1<=85))&&((angle2>=75)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=50)&&(angle5<=65))&&!(((xadc>=410)&&(xadc<=420))&&((yadc>=368)&&(yadc<=380))))
//Serial.println('H');
lcd.print("H");
if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=70))&&((angle3>=50)&&(angle3<=70))&&((angle4>=50)&&(angle4<=70))&&((angle5>=50)&&(angle5<=85)&&((xadc>=410)&&(xadc<=420))&&((yadc>=330)&&(yadc<=370))))
//Serial.println('I');
lcd.print("I");
if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=70))&&((angle3>=50)&&(angle3<=70))&&((angle4>=50)&&(angle4<=70))&&((angle5>=50)&&(angle5<=85))&&(!((xadc>=410)&&(xadc<=420))&&((yadc>=355)&&(yadc<=370))))
//Serial.println('J');
lcd.print("J");
if(((angle1>=60)&&(angle1<=75))&&((angle2>=60)&&(angle2<=85))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=15))&&((angle5>=30)&&(angle5<=55))&&(((xadc>=404)&&(xadc<=415))&&((yadc>=368)&&(yadc<=380))))
//Serial.println('K');
lcd.print("K");
if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=70)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))&&(((xadc>=390)&&(xadc<=405))&&((yadc>=360)&&(yadc<=380)))&&!((xadc>=270)&&(xadc<=300))&&((yadc>=360)&&(yadc<=390)))
//Serial.println('L');
lcd.print("L");
if(((angle1>=40)&&(angle1<=61))&&((angle2>=72)&&(angle2<=84))&&((angle3>=45)&&(angle3<=65))&&((angle4>=62)&&(angle4<=75))&&((angle5>=65)&&(angle5<=86)))
//Serial.println('M');
lcd.print("M");
if(((angle1>=54)&&(angle1<=70))&&((angle2>=50)&&(angle2<=61))&&((angle3>=48)&&(angle3<=66))&&((angle4>=60)&&(angle4<=76))&&((angle5>=50)&&(angle5<=65))&&(((xadc>=400)&&(xadc<=435))&&((yadc>=350)&&(yadc<=390))))
//Serial.println('N');
lcd.print("N");
if(((angle1>=68)&&(angle1<=88))&&((angle2>=68)&&(angle2<=90))&&((angle3>=50)&&(angle3<=80))&&((angle4>=54)&&(angle4<=80))&&((angle5>=0)&&(angle5<=30)))
//Serial.println('O');
lcd.print("O");
if(((angle1>=60)&&(angle1<=75))&&((angle2>=60)&&(angle2<=85))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=15))&&((angle5>=30)&&(angle5<=55))&&(((xadc>=270)&&(xadc<=290))&&((yadc>=360)&&(yadc<=380))))
//Serial.println('P');
lcd.print("P");
if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))&&(((xadc>=270)&&(xadc<=300))&&((yadc>=360)&&(yadc<=390))))
//Serial.println('Q');
lcd.print("Q");
if(((angle1>=40)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=20)&&(angle3<=45))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
//Serial.println('R');
lcd.print("R");
if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=80)&&(angle3<=90))&&((angle4>=80)&&(angle4<=90))&&((angle5>=60)&&(angle5<=80)))
//Serial.println('S');
lcd.print("S");
if(((angle1>=40)&&(angle1<=61))&&((angle2>=72)&&(angle2<=84))&&((angle3>=45)&&(angle3<=65))&&((angle4>=44)&&(angle4<=63))&&((angle5>=65)&&(angle5<=86)))
//Serial.println('T');
lcd.print("T");
if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80)))
//Serial.println('U');
lcd.print("U");
if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80))) 
//Serial.println('V');
lcd.print("V");
if(((angle1>=70)&&(angle1<=90))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80)))
//Serial.println('W');
lcd.print("W");
if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=80)&&(angle4<=89))&&((angle5>=45)&&(angle5<=80)))//&&!(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
//Serial.println('X');
lcd.print("X");
if(((angle1>=0)&&(angle1<=10))&&((angle2>=70)&&(angle2<=90))&&((angle3>=60)&&(angle3<=80))&&((angle4>=80)&&(angle4<=90))&&((angle5>=15)&&(angle5<=35)))
//Serial.println('Y');
lcd.print("Y");
if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
//Serial.println('Z');
lcd.print("Z");

delay(200);
  }  
}
