#include "../include/car_control.h"

float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 10000);
  if (duration == 0) return 999;

  float distance = duration * 0.034 / 2;
  return distance;
}

void move_motors(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t direction, uint8_t speed) {
  motor1->setSpeed(speed);
  motor1->run(direction);
  motor2->setSpeed(speed);
  motor2->run(direction);
  motor3->setSpeed(speed);
  motor3->run(direction);
  motor4->setSpeed(speed);
  motor4->run(direction);
}

void car_forward(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  move_motors(motor1, motor2, motor3, motor4, FORWARD, speed);
}

void car_back(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  move_motors(motor1, motor2, motor3, motor4, BACKWARD, speed);
}

void car_forward_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  motor1->setSpeed(speed / 2);
  motor1->run(FORWARD);
  motor2->setSpeed(speed);
  motor2->run(FORWARD);
  motor3->setSpeed(speed / 2);
  motor3->run(FORWARD);
  motor4->setSpeed(speed);
  motor4->run(FORWARD);
}

void car_forward_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  motor1->setSpeed(speed);
  motor1->run(FORWARD);
  motor2->setSpeed(speed / 2);
  motor2->run(FORWARD);
  motor3->setSpeed(speed);
  motor3->run(FORWARD);
  motor4->setSpeed(speed / 2);
  motor4->run(FORWARD);
}

void car_back_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  motor1->setSpeed(speed / 2);
  motor1->run(BACKWARD);
  motor2->setSpeed(speed);
  motor2->run(BACKWARD);
  motor3->setSpeed(speed / 2);
  motor3->run(BACKWARD);
  motor4->setSpeed(speed);
  motor4->run(BACKWARD);
}

void car_back_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  motor1->setSpeed(speed);
  motor1->run(BACKWARD);
  motor2->setSpeed(speed / 2);
  motor2->run(BACKWARD);
  motor3->setSpeed(speed);
  motor3->run(BACKWARD);
  motor4->setSpeed(speed / 2);
  motor4->run(BACKWARD);
}

void car_turn_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  motor1->setSpeed(speed);
  motor1->run(BACKWARD);
  motor2->setSpeed(speed);
  motor2->run(FORWARD);
  motor3->setSpeed(speed);
  motor3->run(BACKWARD);
  motor4->setSpeed(speed);
  motor4->run(FORWARD);
}

void car_turn_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  motor1->setSpeed(speed);
  motor1->run(FORWARD);
  motor2->setSpeed(speed);
  motor2->run(BACKWARD);
  motor3->setSpeed(speed);
  motor3->run(FORWARD);
  motor4->setSpeed(speed);
  motor4->run(BACKWARD);
}

void car_stop(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  motor1->setSpeed(0);
  motor1->run(RELEASE);
  motor2->setSpeed(0);
  motor2->run(RELEASE);
  motor3->setSpeed(0);
  motor3->run(RELEASE);
  motor4->setSpeed(0);
  motor4->run(RELEASE);
}