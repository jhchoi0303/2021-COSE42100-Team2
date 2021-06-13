#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define OLED_RESET 4
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>      
#define C 262 
#define D 294 
#define E 330  
#define G 392 
#define A 440 
#define B 494 
#define BUFF_SIZE 256 

int SWITCH1 = 1;
int SWITCH2 = 2;
int SWITCH3 = 3;
 
int piezo=8; //초음파 거리 측정 단일음 피에조, 온도 센서
int vibrator=12; //초음파 거리 측정 진동
int trigPin = 7; //초음파 거리 측정
int echoPin =A2; //초음파 거리 측정
int trigPin2=11; //앞쪽 초음파 센서
int echoPin2=A3; //앞쪽 초음파 센서
int LED = 13; //초음파 거리 측정 LED 빨간색
int N;
double duration,distance;
double duration2, distance2;
int light_Pin = A1;   // 조도 센서
int light_sense;       //조도 센서
int ledPin = 9;     // 조도 센서 위한 LED- 초록색

const int PulseWire = 0;      
const int LED13 = 13;         
int Threshold = 550;          
int N_bpm=120;
int M_bpm=30;
int BPMLED = 4; //심장 박동, 흰색
int piezo2=10; //심작 박동 위한 피에조(여러음)
int notes[20] = { G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C}; 
int tempo = 300;

PulseSensorPlayground pulseSensor;  

int bRx = 5; //블루투스의 RX와 연결한 부분
int bTx = 6; //블루투스의 TX와 연결한 부분

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(bTx,bRx);
//왼쪽 인자는 아두이노에서 Rx로 사용하는 핀
//오른족 인자는 Tx로 사용하는 핀

uint8_t buffer[BUFF_SIZE];
uint8_t index = 0;
uint8_t data;

char cbuffer[BUFF_SIZE];


int ind1, ind2,  ind3;
String user;
String age="";
String emergency="";


int androidCmd; 



void setup()  
{ 
  Serial.begin(9600);
  bluetooth.begin(9600);

  
  //Serial.println("Adafruit MLX90614 test"); 
  mlx.begin(); 

  //초음파 거리 측정
  pinMode(LED, OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(piezo, OUTPUT);
  pinMode(vibrator, OUTPUT); 
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT); 
  lcd.init();
  lcd.backlight();
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  pinMode(SWITCH3, INPUT_PULLUP);
  
  pinMode(ledPin, OUTPUT); //조도 센서

  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  
  }
}
 
 
void loop()
{ 
  String inputString = "";  
  while(bluetooth.available()){
    //안드로이드 앱으로부터 수신기능
    inputString= bluetooth.readString();
  }
  
  //시리얼 보드에서 안드로이드 앱으로 송신기능.
  //     if(Serial.available())
  // {
  //   char toSend = (char)Serial.read();
  //   bluetooth.print(toSend);
  // }

    
  if(!inputString.equals("")){

      //android app에서 inputString은 "Name: 이태경Age:1~13Emergency Command:helpme"와 같은 형태로 들어온다. 
      int lengthofstring = inputString.length();
      ind1 = inputString.indexOf(':'); 
      ind2 = inputString.indexOf(':', ind1+1 );
      ind3 = inputString.indexOf(':', ind2+1 );


      //위에 있는 inputString을 쪼개서 이태경은 user에, 1~13은 age에,helpme는 emergency로 들어간다.
      user = inputString.substring(ind1+2, ind2-3); 
      age = inputString.substring(ind2+1, ind3-18);  
      emergency = inputString.substring(ind3+1, lengthofstring-1);

      
      Serial.println("===========사용자 정보========");
      Serial.println(user);
      Serial.println(age);
      Serial.println(emergency);

      //안드로이드 앱으로 송신. 받아들인 inputString을 그대로 송신은 가능.
      // char* cString = (char*) malloc(sizeof(char)*(inputString.length() + 1));
      // inputString.toCharArray(cString, inputString.length() + 1);
      // bluetooth.write(cString);
      
      inputString = "";
  }
      
  //초음파 센서 거리 측정
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);

  digitalWrite(trigPin2,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2,LOW);
  duration2 = pulseIn(echoPin2,HIGH);
  
  distance = duration / 29 / 2;
  distance2 = duration2 / 29 / 2;
  N=50;
  delay(100);


  if( distance2 <50 || distance<50){
    digitalWrite(LED,HIGH);
    digitalWrite(piezo,HIGH);
    digitalWrite(vibrator,HIGH);
  }
  else{
    digitalWrite(LED,LOW);  
    digitalWrite(piezo,LOW);
    digitalWrite(vibrator,LOW);
  }

/// 온도 센서
  if(mlx.readObjectTempC()>80){
    digitalWrite(piezo, HIGH);
    digitalWrite(vibrator, HIGH);
    delay(1000); 
    digitalWrite(piezo, LOW); 
    digitalWrite(vibrator, LOW);
  }
 
  // lcd 모니터
  if (digitalRead(SWITCH1) == LOW){
      lcd.setCursor(0, 0);
      lcd.print("Call");
      delay(200); 
      lcd.setCursor(0, 1);
      lcd.print("010-1234-5678!");
      delay(200); 
    }
    else if (digitalRead(SWITCH2) == LOW){
      lcd.setCursor(0, 0);
      lcd.print("Emergency!");
      delay(200); 
      lcd.setCursor(0, 1);
      lcd.print("Call 119 !");
      delay(200); 
    }
    else if (digitalRead(SWITCH3) == LOW){
      //만약 emergency command 값이 지정되었을 때(bluetooth로 정보가 수신되었을때) 사용자가 앱을 통해 입력한 emergency command를 출력
       if(!emergency.equals("")){
         lcd.setCursor(0, 0);
         lcd.print(emergency);
         delay(200);  
         }
       else{
        lcd.setCursor(0, 0);
        lcd.print("I'm Speechless disorder, Help me!");
        delay(200); 
        lcd.setCursor(0, 1);
        lcd.print("Help me!");
        delay(200); 
       }
    }
    delay(200);
    lcd.clear(); 

  //조도센서
  light_sense = analogRead(light_Pin); 
  digitalWrite(ledPin, HIGH);

   if (light_sense< 400) {
  digitalWrite(ledPin, LOW);
  } else {
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  delay(300);
  }

int myBPM = pulseSensor.getBeatsPerMinute();  
  
                      
if (pulseSensor.sawStartOfBeat()) {   
   if(age.equals("1~13")){ //어린이
    if(myBPM>130 || myBPM <60 ){
    for (int i = 0; i < 1; i++) {
      tone (piezo2, notes[ i ], tempo); //LED 깜빡 깜빡
      digitalWrite(BPMLED,HIGH);
      delay(100);
      digitalWrite(BPMLED,LOW);
      delay(100); 
     }
     noTone(piezo2);
    }
}
  else if(age.equals("14~50")){ //성인
    if(myBPM>105 || myBPM<55 ){
    for (int i = 0; i < 1; i++) {
      tone (piezo2, notes[ i ], tempo); //LED 깜빡 깜빡
      digitalWrite(BPMLED,HIGH);
      delay(100);
      digitalWrite(BPMLED,LOW);
      delay(100); 
     }
     noTone(piezo2);
    }
}
  else if(age.equals("51~")){ //노인
    if(myBPM>80 || myBPM<50 ){
    for (int i = 0; i < 1; i++) {
      tone (piezo2, notes[ i ], tempo); //LED 깜빡 깜빡
      digitalWrite(BPMLED,HIGH);
      delay(100);
      digitalWrite(BPMLED,LOW);
      delay(100); 
     }
     noTone(piezo2);
}
}
  
     else{   //만약 age값이 지정되지 않았을 때, bluetooth로 정보가 제대로 수신되지 않았을때, 평균 수치
  if(myBPM>130 || myBPM<55 ){
    for (int i = 0; i < 20; i++) {
      tone (piezo2, notes[ i ], tempo); 
      digitalWrite(BPMLED,HIGH);
      delay(100);
      digitalWrite(BPMLED,LOW);
      delay(100); 
     }
     noTone(piezo2);
  } 
     }
  
}
  delay(200);   
}