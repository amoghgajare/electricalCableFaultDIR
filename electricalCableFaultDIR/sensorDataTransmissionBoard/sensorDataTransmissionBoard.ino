#include "dht.h"
#include <NewPing.h> 
#define dht_apin A2
#define tempPin A0
#define disPin A5
#define gasPin 3 
#define irPin 7 
#include<RH_ASK.h>
#include<SPI.h>
RH_ASK rf_driver;
dht DHT;
const int trigPin = 8;
const int echoPin = 10;
long duration;
double distance;
NewPing sonar(trigPin, echoPin, 40);
float checkTemp(){
int val = analogRead(tempPin);
float mv = (val/1024.0)*6500; 
float cel1 = mv/100;
return cel1;
}
char checkHum(){
DHT.read11(dht_apin);
delay(50);
if((DHT.humidity)>70){
return 'u';
  }
else{return 'g';}
} 
void setup() {
rf_driver.init();
pinMode(irPin,INPUT);
pinMode(tempPin,INPUT);
pinMode(gasPin,INPUT);
pinMode(dht_apin,INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); 
pinMode(disPin,INPUT); 
Serial.begin(9600);
}
void loop() {
int dist = sonar.ping_cm();
if((dist<6 && dist!=0)||(digitalRead(irPin)==LOW)){
const char *msg9 = "Obstacle Detected    ";
rf_driver.send((uint8_t *)msg9, strlen(msg9));
rf_driver.waitPacketSent();
delay(10);}
else{
const char *msg10 = "Forward Path Clear   ";
rf_driver.send((uint8_t *)msg10, strlen(msg10));
rf_driver.waitPacketSent();
delay(10);}
float r=((analogRead(disPin)));
delay(10);
if(r<=950){
const char *msg8 = "Discharge Detected   ";
rf_driver.send((uint8_t *)msg8, strlen(msg8));
rf_driver.waitPacketSent();
delay(10);}
else{
const char *msg7 = "No Discharge Detected";
rf_driver.send((uint8_t *)msg7, strlen(msg7));
rf_driver.waitPacketSent();
delay(10);}
if(checkTemp()>=300){
const char *msg = "High Temp Detected  ";
rf_driver.send((uint8_t *)msg, strlen(msg));
rf_driver.waitPacketSent();
}
else{
 const char *msg1 = "Normal Temp Detected  ";
rf_driver.send((uint8_t *)msg1, strlen(msg1));
rf_driver.waitPacketSent(); 
}
delay(10);
if(digitalRead(gasPin)==false){
const char *msg2 = "Gas Leakage Detected  ";
rf_driver.send((uint8_t *)msg2, strlen(msg2));
rf_driver.waitPacketSent();
}
else{
const char *msg3 = "Normal Gas Level     ";
rf_driver.send((uint8_t *)msg3, strlen(msg3));
rf_driver.waitPacketSent(); 
}
delay(10);
if(checkHum()=='u'){
const char *msg4 = "High Moisture Levels ";
rf_driver.send((uint8_t *)msg4, strlen(msg4));
rf_driver.waitPacketSent();
}
else{
const char *msg5 = "Normal Moisture Level ";
rf_driver.send((uint8_t *)msg5, strlen(msg5));
rf_driver.waitPacketSent(); 
}
delay(10);

}
