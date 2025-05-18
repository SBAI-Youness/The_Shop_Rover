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

void setup() {
  bluetoothSerial.begin(9600);
}

void loop() {
  if (bluetoothSerial.available() > 0) {
    command = bluetoothSerial.read();
    car_stop(&motor1, &motor2, &motor3, &motor4);

    // Speed control commands (0-9)
    if (command >= '0' && command <= '9') {
      // Convert ASCII to number and map to speed range
      currentSpeed = map(command - '0', 0, 9, MIN_SPEED, MAX_SPEED);
      return;
    }

    switch (command) {
      case 'F':
        car_forward(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'B':
        car_back(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'G':
        car_forward_left(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'I':
        car_forward_right(&motor1, &motor2, &motor3, &motor4, currentSpeed);
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
    }
  }
}