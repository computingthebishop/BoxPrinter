#include <Servo.h>
#define threshold 150
#define ServoZero 72

#define pinServoL 6
#define pinServoR 9
#define pinFans 4

#define pinCooler 5
#define pinPump 3

#define inputToFan A1
#define inputToCool A3 //P1.22
#define setToPause A2 //P1.23
#define statusLed 13
#define errorLed 2

Servo ServoL;
Servo ServoR;

bool fanOpen = false;

void openFans(void) {
  ServoL.write(20);
  ServoR.write(20);
  delay(850);
  ServoL.write(ServoZero);
  ServoR.write(ServoZero);
  digitalWrite(pinFans, HIGH);
  fanOpen = true;
}

void closeFans(void) {
  digitalWrite(pinFans, LOW);
  ServoL.write(90);
  ServoR.write(90);
  delay(1000);
  ServoL.write(ServoZero);
  ServoR.write(ServoZero);
  fanOpen = false;
}

void setup() {
  ServoL.attach(pinServoL);
  ServoL.write(ServoZero);
  ServoR.attach(pinServoR);
  ServoR.write(ServoZero);
  pinMode(pinFans, OUTPUT);
  digitalWrite(pinFans, LOW);
  pinMode(pinCooler, OUTPUT);
  digitalWrite(pinCooler, LOW);
  pinMode(pinPump, OUTPUT);
  digitalWrite(pinPump, LOW);
  pinMode(inputToFan, INPUT);
  pinMode(inputToCool, INPUT);
  pinMode(setToPause, OUTPUT);
  digitalWrite(setToPause, LOW);
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, LOW);

  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
  if ((analogRead(inputToFan) >= threshold) && !fanOpen) {
    openFans();
  }
  else if ((analogRead(inputToFan) <= threshold) && fanOpen) {
    closeFans();
  }
  if (analogRead(inputToCool) >= threshold) {
    digitalWrite(statusLed, HIGH);
    analogWrite(pinPump, 200);
    analogWrite(pinCooler, 180);
    Serial.println("ON");
  }
  else {
    digitalWrite(statusLed, LOW);
    analogWrite(pinPump, 0);
    analogWrite(pinCooler, 0);
    Serial.println("OFF");
  }
  delay(200);
}
