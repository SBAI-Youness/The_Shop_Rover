#include "../include/car_control.h"

void move_motors(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t direction) {
  motor1->setSpeed(MOTOR_SPEED);
  motor1->run(direction);
  motor2->setSpeed(MOTOR_SPEED);
  motor2->run(direction);
  motor3->setSpeed(MOTOR_SPEED);
  motor3->run(direction);
  motor4->setSpeed(MOTOR_SPEED);
  motor4->run(direction);
}

void car_forward(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  move_motors(motor1, motor2, motor3, motor4, FORWARD);
}

void car_back(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  move_motors(motor1, motor2, motor3, motor4, BACKWARD);
}

void car_forward_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  motor1->setSpeed(MOTOR_SPEED / 2);
  motor1->run(FORWARD);
  motor2->setSpeed(MOTOR_SPEED);
  motor2->run(FORWARD);
  motor3->setSpeed(MOTOR_SPEED / 2);
  motor3->run(FORWARD);
  motor4->setSpeed(MOTOR_SPEED);
  motor4->run(FORWARD);
}

void car_forward_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  motor1->setSpeed(MOTOR_SPEED);
  motor1->run(FORWARD);
  motor2->setSpeed(MOTOR_SPEED / 2);
  motor2->run(FORWARD);
  motor3->setSpeed(MOTOR_SPEED);
  motor3->run(FORWARD);
  motor4->setSpeed(MOTOR_SPEED / 2);
  motor4->run(FORWARD);
}

void car_back_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  motor1->setSpeed(MOTOR_SPEED / 2);
  motor1->run(BACKWARD);
  motor2->setSpeed(MOTOR_SPEED);
  motor2->run(BACKWARD);
  motor3->setSpeed(MOTOR_SPEED / 2);
  motor3->run(BACKWARD);
  motor4->setSpeed(MOTOR_SPEED);
  motor4->run(BACKWARD);
}

void car_back_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  motor1->setSpeed(MOTOR_SPEED);
  motor1->run(BACKWARD);
  motor2->setSpeed(MOTOR_SPEED / 2);
  motor2->run(BACKWARD);
  motor3->setSpeed(MOTOR_SPEED);
  motor3->run(BACKWARD);
  motor4->setSpeed(MOTOR_SPEED / 2);
  motor4->run(BACKWARD);
}

void car_turn_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  motor1->setSpeed(MOTOR_SPEED);
  motor1->run(BACKWARD);
  motor2->setSpeed(MOTOR_SPEED);
  motor2->run(FORWARD);
  motor3->setSpeed(MOTOR_SPEED);
  motor3->run(BACKWARD);
  motor4->setSpeed(MOTOR_SPEED);
  motor4->run(FORWARD);
}

void car_turn_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4) {
  motor1->setSpeed(MOTOR_SPEED);
  motor1->run(FORWARD);
  motor2->setSpeed(MOTOR_SPEED);
  motor2->run(BACKWARD);
  motor3->setSpeed(MOTOR_SPEED);
  motor3->run(FORWARD);
  motor4->setSpeed(MOTOR_SPEED);
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