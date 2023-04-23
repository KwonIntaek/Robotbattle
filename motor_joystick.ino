#include<Servo.h>
int Motor1=4;
int Motor2=5;
int Motorpower=3;
float xjoy;
float yjoy;

void setup() {
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  
}

void loop() {
  xjoy=map(analogRead(A0),0,1023,0,255);
  int rpmx=(abs(xjoy-127)*1.9);

  if (xjoy>128){
    analogWrite(Motorpower,rpmx);
    digitalWrite(Motor1,LOW);
    digitalWrite(Motor2,HIGH);
  }
  else if (xjoy<128){
    analogWrite(Motorpower,rpmx);
    digitalWrite(Motor1,HIGH);
    digitalWrite(Motor2,LOW);
  }
  else{
    digitalWrite(Motor1,HIGH);
    digitalWrite(Motor2,HIGH);
  }

}
