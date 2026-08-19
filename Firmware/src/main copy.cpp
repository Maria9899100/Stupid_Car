 #include <Arduino.h>

 const int Echo=13;
 const int Trig=12;

 const int In1=10;
 const int In2=11;
 const int EnA=8;

 const int In3=14;
 const int In4=15;
 const int EnB=9;
 const long threshold=1;  //distance
 long dur




void setup(){
  
    Serial.begin(9600);
pinMode(Echo,INPUT);
pinMode(Trig,OUTPUT);
pinMode(In1,OUTPUT);
pinMode(In2,OUTPUT);
pinMode(EnA,OUTPUT);
pinMode(In3,OUTPUT);
pinMode(In4,OUTPUT);
pinMode(EnB,OUTPUT);
}
void loop(){}