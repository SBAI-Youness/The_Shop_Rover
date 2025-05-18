#pragma once

#include <AFMotor.h>

#define MOTOR1_ID 1
#define MOTOR2_ID 2
#define MOTOR3_ID 3
#define MOTOR4_ID 4

// Speed range: 0-255
#define MIN_SPEED 0
#define MAX_SPEED 255

extern void move_motors(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t direction, uint8_t speed);
extern void car_forward(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_back(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_forward_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_forward_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_back_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_back_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_turn_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_turn_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
extern void car_stop(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4);