/*
  The Shop Rover: an Arduino Bluetooth Controlled Car
  Install Adafruit Motor Shield Library before uploading this code.
  AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install

  -> If you need helping guide on how to install library for the motor shield or how to use motor shield then
      send me a message on email: youness.sbai.work@gmail.com

      Caution: Remove the jumper or switch off the battery switch before connecting the Arduino board to computer.

      For more support contact me on LinkedIn: https://www.linkedin.com/in/y-sbai/
*/

#include <SoftwareSerial.h>
#include "../include/car_control.h"

#define BLUETOOTH_RX 9
#define BLUETOOTH_TX 10

AF_DCMotor motor1(MOTOR1_ID, MOTOR12_1KHZ);
AF_DCMotor motor2(MOTOR2_ID, MOTOR12_1KHZ);
AF_DCMotor motor3(MOTOR3_ID, MOTOR34_1KHZ);
AF_DCMotor motor4(MOTOR4_ID, MOTOR34_1KHZ);

SoftwareSerial bluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX);

char command;
uint8_t currentSpeed = MAX_SPEED;
unsigned long lastDistanceCheck = 0;
const unsigned long DISTANCE_CHECK_INTERVAL = 100;
float lastDistance = 0;

void setup() {
  bluetoothSerial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastDistanceCheck >= DISTANCE_CHECK_INTERVAL) {
    lastDistance = measureDistance();
    lastDistanceCheck = currentMillis;
  }

  if (bluetoothSerial.available() > 0) {
    command = bluetoothSerial.read();
    
    if (command >= '0' && command <= '9') {
      currentSpeed = map(command - '0', 0, 9, MIN_SPEED, MAX_SPEED);
      return;
    }

    bool obstacleDetected = lastDistance < MIN_DISTANCE;
    
    switch (command) {
      case 'F':
        if (!obstacleDetected) {
          car_forward(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        } else {
          car_stop(&motor1, &motor2, &motor3, &motor4);
        }
        break;
      case 'B':
        car_back(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'G':
        if (!obstacleDetected) {
          car_forward_left(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        } else {
          car_stop(&motor1, &motor2, &motor3, &motor4);
        }
        break;
      case 'I':
        if (!obstacleDetected) {
          car_forward_right(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        } else {
          car_stop(&motor1, &motor2, &motor3, &motor4);
        }
        break;
      case 'H':
        car_back_left(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'J':
        car_back_right(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'L':
        car_turn_left(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'R':
        car_turn_right(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'S':
        car_stop(&motor1, &motor2, &motor3, &motor4);
        break;
    }
  }
}