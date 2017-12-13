/*
 * Created by Shruti Iyer, William Lu
 * This code integrates two DC motors
 * and two IR reflectance sensors using
 * bang bang control.
 */


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <PID_v1.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);

int rightIR; //Value from infrared sensor 1
int leftIR;  //Value from infrared sensor 2
int diffIR;  //Difference in IR sensor values

int rightMotorSpeed = 30; //set motor speeds
int leftMotorSpeed = 30;
int newSpeed;

double Setpoint;
double Kp = 1;
double Ki = 1;
double Kd = 1;

PID myPID(&diffIR, &newSpeed, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  AFMS.begin();
  rightMotor->setSpeed(rightMotorSpeed);
  leftMotor->setSpeed(leftMotorSpeed);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  myPID.SetMode(AUTOMATIC);
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available() > 0){
    // checks if there is data in the Serial buffer
    // if there is data in the buffer, parses it
    // for an integer and sets the motor speeds to
    // that integer
    newSpeed = Serial.parseInt();
    rightMotorSpeed = newSpeed;
    leftMotorSpeed = newSpeed;
    rightMotor->setSpeed(rightMotorSpeed);
    leftMotor->setSpeed(leftMotorSpeed);
  }
  
  leftIR = analogRead(A1);
  rightIR = analogRead(A0);
  
  if (rightIR > leftIR && rightIR - leftIR >= 100) {
    // if the robot is to the right of the track, turn left
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
    Serial.print(leftIR); Serial.print(" "); Serial.print(rightIR); Serial.print(" "); 
    Serial.print(leftMotorSpeed); Serial.print(" "); Serial.println(-rightMotorSpeed);
  }

  else if (leftIR > rightIR && leftIR - rightIR >= 100) {
    // if the robot is to the left of the track, turn rightM
    rightMotor->run(BACKWARD);
    leftMotor->run(FORWARD);
    Serial.print(leftIR); Serial.print(" "); Serial.print(rightIR); Serial.print(" "); 
    Serial.print(-leftMotorSpeed); Serial.print(" "); Serial.println(rightMotorSpeed);
  }
  
  else if (leftIR - rightIR <= 100 || rightIR - leftIR <= 100) {
    // if the robot is centered on the track, continue moving straight
    rightMotor->run(FORWARD);
    leftMotor->run(FORWARD);
    Serial.print(leftIR); Serial.print(" "); Serial.print(rightIR); Serial.print(" "); 
    Serial.print(leftMotorSpeed); Serial.print(" "); Serial.println(rightMotorSpeed);
  }
//  
//  else if (leftIR >= 600 && rightIR >= 600){
//    // if the robot crosses the starting line, tell MATLAB to stop recording data
//    Serial.println("AWS");
//  }
}
