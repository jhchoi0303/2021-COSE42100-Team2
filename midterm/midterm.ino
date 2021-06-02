

//초음파 & 온도
#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define OLED_RESET 4
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#define C 262 
#define D 294 
#define E 330  
#define G 392 
#define A 440 
#define B 494 

int SWITCH1 = 1;
int SWITCH2 = 2;
int SWITCH3 = 3;
 
int piezo=8;
int vibrator=12;
int trigPin = 7;
int echoPin =A2;
int LED = 13;
int N;
double duration,distance;

int light_Pin = A1;   //
int light_sense;       //
int ledPin = 9;     // 

const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
int N_bpm=120;
int M=30;
int BPMLED = 4;
int piezo2=10;
int notes[20] = { G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C}; 
int tempo = 300;

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

int bRx = 5; //블루투스의 RX와 연결한 부분
int bTx = 6; //블루투스의 TX와 연결한 부분

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(bTx,bRx);
//원칙은 왼쪽 인자는 아두이노에서 Rx로 사용하는 핀
//오른족 인자는 Tx로 사용하는 핀

//int ledPin = 13; // Built-in LED
int androidCmd; // Command message from Android
String msg;


void setup()  
{           
  Serial.begin(9600);

  bluetooth.begin(9600);
  msg="";
  
  pinMode(piezo, OUTPUT);
  Serial.println("Adafruit MLX90614 test"); 
  mlx.begin(); 
  pinMode(vibrator, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  lcd.init();
  lcd.backlight();
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  pinMode(SWITCH3, INPUT_PULLUP);
  
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600); 

     if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}
 
 
void loop()
{ 
  // To read message received from other Bluetooth Device /// 블루투스
  if (bluetooth.available() > 0)
  { // Check if there is data coming
    msg = bluetooth.readString(); // Read the message as String
    Serial.println("Android Command " + msg);
    int ind1 = msg.indexOf(':');
    String age = msg.substring(ind1+1,msg.length()); 
  }
  
  ///// lcd 모니터
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
      lcd.setCursor(0, 0);
      lcd.print("I'm Speechless disorder, Help me!");
      delay(200); 
      lcd.setCursor(0, 1);
      lcd.print("Help me!");
      delay(200); 
    }
    delay(200);
    lcd.clear(); 

   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  light_sense = analogRead(light_Pin); 
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = duration / 29 / 2;
  N = 50;
  
/// 온도 센서
  if(mlx.readObjectTempC()<20){
    digitalWrite(piezo, HIGH);
    digitalWrite(vibrator, HIGH);
    delay(1000); 
    digitalWrite(piezo, LOW); 
    digitalWrite(vibrator, LOW);
  }

 //// 초음파 센서
  if(distance<N){
    digitalWrite(LED,HIGH);
    digitalWrite(piezo,HIGH);
    digitalWrite(vibrator,HIGH);
  }
  else{
    digitalWrite(LED,LOW);  
    digitalWrite(piezo,LOW);
    digitalWrite(vibrator,LOW);
  }
  
 /////////////////////////////////// 조도 센서
 digitalWrite(ledPin, HIGH);

   if (light_sense< 400) {
  digitalWrite(ledPin, LOW);
  } else {
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  delay(300);
  }

//////////////////////////////////// 심장 박동
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".

//digitalWrite(BPMLED,HIGH);

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
  if(myBPM>N_bpm || myBPM<M){
    
     //Serial.print("123131231312213"); 
    for (int i = 0; i < 20; i++) {
      
      tone (piezo2, notes[ i ], tempo);//LED 깜빡 깜빡
      digitalWrite(BPMLED,HIGH);
      delay(100);
      digitalWrite(BPMLED,LOW);
      delay(100); 
     }
     noTone(piezo2);
  } 
  // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
}
  delay(200);                    // considered best practice in a simple sketch.

  
  
}
