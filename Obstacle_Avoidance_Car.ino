#include <Servo.h>
#include <LiquidCrystal.h>
#include <dht.h>//servo library
Servo myservo;      // create servo object to control servo
 
LiquidCrystal lcd(9, 10, 5, 7, 6, 8);
int Echo = A4;  
int Trig = A5; 
int REDLED = 2;
int GREENLED = 3;
int BUZZER = 11;
int greenPin = A5;
dht sensor;
 
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 150
int rightDistance = 0, leftDistance = 0, middleDistance = 0;
 
void forward(){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, HIGH);
  digitalWrite(BUZZER, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}
 
void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(GREENLED, LOW);
  digitalWrite(REDLED, HIGH);
  digitalWrite(BUZZER, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}
 
void left() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(GREENLED, HIGH);
  digitalWrite(REDLED, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}
 
void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}
 
void stop() {
  digitalWrite(REDLED, HIGH);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BUZZER, HIGH);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} 
 
//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  
 
void setup() 
{ 
  lcd.begin(16,2);
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
} 
 
void loop() { 
    delay(1000); //wait a sec (recommended for DHT11)
    sensor.read11(greenPin);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity = ");
    lcd.print(sensor.humidity);
    lcd.setCursor(0,1);
    lcd.print("Temp = ");
    lcd.print(sensor.temperature);
    myservo.write(90);  //setservo position according to scaled value
    delay(500); 
    middleDistance = Distance_test();
 
    if(middleDistance <= 20) {     
      stop();
      delay(500);                         
      myservo.write(10);          
      delay(1000);      
      rightDistance = Distance_test();
      
      delay(500);
      myservo.write(90);              
      delay(1000);                                                  
      myservo.write(180);              
      delay(1000); 
      leftDistance = Distance_test();
      
      delay(500);
      myservo.write(90);              
      delay(1000);
      if(rightDistance > leftDistance) {
        right();
        delay(360);
      }
      else if(rightDistance < leftDistance) {
        left();
        delay(360);
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        back();
        delay(180);
      }
      else {
        forward();
      }
    }  
    else {
        forward();
    }                     
}
