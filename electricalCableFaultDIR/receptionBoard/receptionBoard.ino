#include <RH_ASK.h>
#include <SPI.h>
RH_ASK rf_driver;
static long count=0;
static long count2=0;
void setup() {
  // put your setup code here, to run once:
rf_driver.init();
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf[21];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
    {
      if(count%4==0){
      Serial.print("Cycle : ");
      Serial.println(count/4);}
      Serial.println(count2);
      count=count+1;
      count2=count2+1;
//      float time1=count2*0.42;
//      float dist=time1*(70/3.4);
//      Serial.print(dist);
//      Serial.print(" cm: ");
      Serial.println((char*)buf);
    }
 }
