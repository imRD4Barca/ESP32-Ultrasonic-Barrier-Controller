#include <ESP32Servo.h>

// Pin Configurations
const int trigPin = 19;
const int echoPin = 18;
const int servoPin = 27;
const int openLedPin = 22;
const int closeLedPin = 23;


const float soundSpeed = 0.0343;
const int openAngle = 0;
const int closeAngle = 90;
unsigned long openAt = 0;
bool gateOpen = false;

Servo servo;

// Functions Initialize
void barricadeOpen();
void barricadeClose();
void ultrasonicSensorInitialize();

void barricadeOpen(){
  servo.write(openAngle);
  digitalWrite(openLedPin, HIGH);
  digitalWrite(closeLedPin, LOW);
  openAt = millis();
}
void barricadeClose(){
  servo.write(closeAngle);
  digitalWrite(openLedPin, LOW);
  digitalWrite(closeLedPin, HIGH);
  openAt = 0;
}

void ultrasonicSensorInitialize(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(openLedPin, OUTPUT);
  pinMode(closeLedPin, OUTPUT);
  servo.attach(servoPin);
  barricadeClose();
}


void loop() {
  // put your main code here, to run repeatedl:
  ultrasonicSensorInitialize();

  unsigned long duration = pulseIn(echoPin, HIGH, 50000);
  float distance;
  if (duration==0){
    distance = 999;
  }
  else{
    distance = soundSpeed * duration / 2;
  }

  if(distance <= 20){
    if(!gateOpen){
      barricadeOpen();
      gateOpen = true;
    }
  }
  if(gateOpen && (millis()-openAt)>2000){
    barricadeClose();
    gateOpen = false;
  }
  delay(20);
}
