//센서와 연결된 아날로그 핀 설정
int flexpin1 = A4; 
int flexpin2 = A3; 
int flexpin3 = A2; 
int flexpin4 = A1; 
int flexpin5 = A0; 
void setup() {
  // 시리얼 통신을 열고 속도를 9600로 설정한다.
    Serial.begin(9600); 
}

void loop() {
  //센서값을 저장할 변수 설정
  int flexVal1,flexVal2,flexVal3,flexVal4,flexVal5; 
  // 센서로 부터 보내오는 값을 입력 받는다.(0-1023)
  flexVal1 = analogRead(flexpin1);
  delay(100);
  flexVal2 = analogRead(flexpin2);
  delay(100);
  flexVal3 = analogRead(flexpin3);
  delay(100);
  flexVal4 = analogRead(flexpin4);
  delay(100);
  flexVal5 = analogRead(flexpin5); 
  delay(100);

  byte array1[5];

  array1[0] = flexVal1;
  delay(50);
  array1[1] = flexVal2;
  delay(50);
  array1[2] = flexVal3;
  delay(50);
  array1[3] = flexVal4;
  delay(50);
  array1[4] = flexVal5;
  delay(50);
  
  
  Serial.write(array1 ,5);
   
  delay(1000);
}
