//RF24_config 파일에 spi_speed 8000000으로 수정
#include <SPI.h> 
#include <Servo.h>
#include <nRF24L01.h>
#include <RF24.h>
int right_1 = 1; // 모터 연결선 2,3,4,5
int right_2 = 2;
int left_1 = 3;
int left_2 = 4;
int rightspdpin = 5; // 모터 속도 조절용 핀 5,6
int leftspdpin = 6;

Servo servo;
RF24 radio(8,9); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN 선언.
const byte address[6] = "12345"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기과 수신기가 동일한 주소로 해야됨.

void Readdata(int receiveDataPacket[], uint8_t readBuf[]);

void move_right();
void move_left();
void move_foward();
void move_backward();
void setup() {

  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX); //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.
  pinMode(right_1, OUTPUT);
  pinMode(right_2, OUTPUT);
  pinMode(left_1, OUTPUT);
  pinMode(left_2, OUTPUT);
//거리가 가까운 순으로 RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX 등으로 설정할 수 있습니다.

//높은 레벨(거리가 먼 경우)은 작동하는 동안 안정적인 전압을 가지도록 GND와 3.3V에 바이패스 커패시터 사용을 권장함
  radio.startListening(); //모듈을 수신기로 설정
}
unsigned long current = 0;
unsigned long before = 0;
uint8_t readBuf[4*8];
int receiveDataPacket[8] = {0,};
int state = 0;\
void loop() {
  current = millis();
  if (radio.available()) {
    
    radio.read(&readBuf, sizeof(readBuf));
    Readdata(receiveDataPacket, readBuf);
    //100밀리초마다 출력
    if(current - before > 100)
    {
      for(int i = 0; i < 8; i++)
      {  
        Serial.print(receiveDataPacket[i]); 
        Serial.print("\t");       
      }
      Serial.println(" ");
      before = current;
    }
  }
  else
    {
      Serial.println("ㅜ");
      delay(100);
      }
   int foward_backward_sign = receiveDataPacket[3];//map(int(receiveDataPacket[3]), 0, 1023, -2,2);
   int right_left_sign = receiveDataPacket[2];//map(int(receiveDataPacket[2]), 0, 1023, -2,2);
   int rightspd = map(int(receiveDataPacket[0]),0, 1023,0,255);
   int leftspd = map(int(receiveDataPacket[1]),0, 1023,0,255);
   //servo.write(angle);
   if(foward_backward_sign < 300)
     move_backward();
   else if(foward_backward_sign > 600)
     move_foward();
   else if(right_left_sign < 300)
     move_left();
   else if(right_left_sign > 600)
     move_right();
   else
     move_stop();
  
}
void move_foward()
{
  digitalWrite(right_1, 0);
  digitalWrite(right_2, 1);
  //analogWrite(rightspdpin, rightspd);
  digitalWrite(left_1, 1);
  digitalWrite(left_2, 0);  
  //analogWrite(leftspdpin, leftspd);
}
void move_left()
{
  digitalWrite(right_1, 0);
  digitalWrite(right_2, 1);
  digitalWrite(left_1, 0);
  digitalWrite(left_2, 1); 
}
void move_right()
{

  digitalWrite(right_1, 1);
  digitalWrite(right_2, 0);
  digitalWrite(left_1, 1);
  digitalWrite(left_2, 0);
}
void move_backward()
{
  
  digitalWrite(right_1, 1);
  digitalWrite(right_2, 0);
  //analogWrite(rightspdpin, rightspd);
  digitalWrite(left_1, 0);
  digitalWrite(left_2, 1);
  //analogWrite(leftspdpin, leftspd); 
}
void move_stop()
{
  digitalWrite(right_1, 0);
  digitalWrite(right_2, 0);
  digitalWrite(left_1, 0);
  digitalWrite(left_2, 0);  
}
void Readdata(int receiveDataPacket[], uint8_t readBuf[])
{
  int data[8] = {0,};
  
  data[0] += readBuf[0];
  data[0] += readBuf[1] << 8;
  data[0] += readBuf[2] << 16;
  data[0] += readBuf[3] << 24;
  data[1] += readBuf[4];
  data[1] += readBuf[5] << 8;
  data[1] += readBuf[6] << 16;
  data[1] += readBuf[7] << 24;
  data[2] += readBuf[8];
  data[2] += readBuf[9] << 8;
  data[2] += readBuf[10] << 16;
  data[2] += readBuf[11] << 24;
  data[3] += readBuf[12];
  data[3] += readBuf[13] << 8;
  data[3] += readBuf[14] << 16;
  data[3] += readBuf[15] << 24;
  data[4] += readBuf[16];
  data[4] += readBuf[17] << 8;
  data[4] += readBuf[18] << 16;
  data[4] += readBuf[19] << 24;
  data[5] += readBuf[20];
  data[5] += readBuf[21] << 8;
  data[5] += readBuf[22] << 16;
  data[5] += readBuf[23] << 24;
  data[6] += readBuf[24];
  data[6] += readBuf[25] << 8;
  data[6] += readBuf[26] << 16;
  data[6] += readBuf[27] << 24;
  data[7] += readBuf[28];
  data[7] += readBuf[29] << 8;
  data[7] += readBuf[30] << 16;
  data[7] += readBuf[31] << 24;

  for(int i = 0; i < 8; i++)
    receiveDataPacket[i] = data[i];
}
