#define IN1 5
#define IN2 6
#define IN3 3
#define IN4 9
#define Prox1 A0
#define Prox2 A1
#define hallpin A2
int threshold = 1;
void moveForward(){
analogWrite(IN1,speed1);
analogWrite(IN2,0);
analogWrite(IN3,0);
analogWrite(IN4,speed2);
}
void stopRobot(){
analogWrite(IN1,0);
analogWrite(IN2,0);
analogWrite(IN3,0);
analogWrite(IN4,0);
}
void moveLeft(){
analogWrite(IN1,speed1);
analogWrite(IN2,0);
analogWrite(IN3,0);
analogWrite(IN4,0); 
}
void moveRight(){
analogWrite(IN1,0);
analogWrite(IN2,0);
analogWrite(IN3,0);
analogWrite(IN4,speed2);
}  

//Sensor Functions Start

float readProx1(){
float r=((float)analogRead(Prox1)  + 0.5 ) / 1024.0 * 5.0;
return r;
}
float readProx2(){
float r=((float)analogRead(Prox2)  + 0.5 ) / 1024.0 * 5.0;
return r;
}

//Sensor Functions End

void setup() {
pinMode(IN3,OUTPUT);
pinMode(hallpin,INPUT);
pinMode(IN4,OUTPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(Prox1,INPUT);
pinMode(Prox2,INPUT);
Serial.begin(9600);
}
//////////////////////////////////////////////////////////////////////////////////////
void loop(){  
//**Testing Code**
//Serial.print(analogRead(IN1));
//Serial.print(", ");
//Serial.print(analogRead(IN2));
//Serial.print(", ");
//Serial.print(analogRead(IN3));
//Serial.print(", ");
//Serial.print(analogRead(IN4));
//Serial.print(", ");
//Serial.print(readProx1());
//Serial.print(", ");
//Serial.println(readProx2());
if(((readProx1())>=threshold) && (readProx2()>=threshold)){
moveForward();
  }
if(((readProx1())<=threshold) && (readProx2()>=threshold)){
moveLeft();
  }
if(((readProx1())>=threshold) && (readProx2()<=threshold)){
moveRight();  
}
if(((readProx1())<=threshold) && (readProx2()<=threshold)){
moveLeft();
}
delay(60);
}
