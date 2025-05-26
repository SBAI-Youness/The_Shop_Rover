/*
  The Shop Rover: an Arduino Bluetooth Controlled Car
  Install Adafruit Motor Shield Library before uploading this code.
  AFMotor Library: https://learn.adafruit.com/adafruit-motor-shield/library-install

  -> If you need help installing the library or using the motor shield,
     send an email to: youness.sbai.work@gmail.com

     Caution: Remove the jumper or switch off the battery switch before connecting the Arduino board to a computer.

     For more support, contact on LinkedIn: https://www.linkedin.com/in/y-sbai/
*/

#include <SoftwareSerial.h>  // Enables serial communication on other digital pins
#include <AFMotor.h>         // Library for Adafruit Motor Shield

// Bluetooth module RX and TX pins
#define BLUETOOTH_RX 9
#define BLUETOOTH_TX 10

// Motor port numbers
#define MOTOR1_ID 1
#define MOTOR2_ID 2
#define MOTOR3_ID 3
#define MOTOR4_ID 4

// Speed boundaries
#define MIN_SPEED 0
#define MAX_SPEED 255

// Ultrasonic sensor pins and threshold
#define TRIG_PIN A1
#define ECHO_PIN A0
#define MIN_DISTANCE 20 // Minimum safe distance in cm

// Buzzer configuration
#define BUZZER_PIN 12
#define BUZZER_FREQ 1000 // Frequency in Hz

// Initialize motors with respective IDs and PWM frequencies
AF_DCMotor motor1(MOTOR1_ID, MOTOR12_1KHZ);
AF_DCMotor motor2(MOTOR2_ID, MOTOR12_1KHZ);
AF_DCMotor motor3(MOTOR3_ID, MOTOR34_1KHZ);
AF_DCMotor motor4(MOTOR4_ID, MOTOR34_1KHZ);

// Initialize software serial for Bluetooth communication
SoftwareSerial bluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX);

// Function declarations
void move_motors(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t direction, uint8_t speed);
void car_forward(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_back(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_forward_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_forward_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_back_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_back_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_turn_left(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_turn_right(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed);
void car_stop(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4);
float measureDistance();
void buzzer_on();
void buzzer_off();

// Global variables
char command;
uint8_t currentSpeed = MAX_SPEED;
unsigned long lastDistanceCheck = 0;
const unsigned long DISTANCE_CHECK_INTERVAL = 100; // ms
float lastDistance = 0;

void setup() {
  bluetoothSerial.begin(9600); // Initialize Bluetooth at 9600 baud rate

  // Set ultrasonic sensor pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  buzzer_off(); // Turn buzzer off initially

  // Initialize all motors to speed 0
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void loop() {
  unsigned long currentMillis = millis();

  // Periodically check distance to obstacles
  if (currentMillis - lastDistanceCheck >= DISTANCE_CHECK_INTERVAL) {
    lastDistance = measureDistance();
    lastDistanceCheck = currentMillis;
  }

  // If a Bluetooth command is available, process it
  if (bluetoothSerial.available() > 0) {
    command = bluetoothSerial.read();

    // Change speed based on numeric input
    if (command >= '0' && command <= '9') {
      currentSpeed = map(command - '0', 0, 9, MIN_SPEED, MAX_SPEED);
      return;
    }

    // Detect if obstacle is too close
    bool obstacleDetected = lastDistance < MIN_DISTANCE;

    // Command execution
    switch (command) {
      case 'F': // Forward
        if (!obstacleDetected) {
          car_forward(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        } else {
          car_stop(&motor1, &motor2, &motor3, &motor4);
        }
        break;
      case 'B': // Backward
        car_back(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'G': // Forward left
        if (!obstacleDetected) {
          car_forward_left(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        } else {
          car_stop(&motor1, &motor2, &motor3, &motor4);
        }
        break;
      case 'I': // Forward right
        if (!obstacleDetected) {
          car_forward_right(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        } else {
          car_stop(&motor1, &motor2, &motor3, &motor4);
        }
        break;
      case 'H': // Backward left
        car_back_left(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'J': // Backward right
        car_back_right(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'L': // Turn left (in place)
        car_turn_left(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'R': // Turn right (in place)
        car_turn_right(&motor1, &motor2, &motor3, &motor4, currentSpeed);
        break;
      case 'S': // Stop
        car_stop(&motor1, &motor2, &motor3, &motor4);
        break;
      case 'V': // Buzzer on
        buzzer_on();
        break;
      case 'v': // Buzzer off
        buzzer_off();
        break;
    }
  }
}

// Measure distance using ultrasonic sensor
float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 10000); // Timeout after 10ms
  if (duration == 0) return 999; // If no pulse received

  float distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Turn on the buzzer
void buzzer_on() {
  tone(BUZZER_PIN, BUZZER_FREQ);
}

// Turn off the buzzer
void buzzer_off() {
  noTone(BUZZER_PIN);
}

// Helper function to move all motors in a specific direction at a given speed
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

// Basic movement functions
void car_forward(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  move_motors(motor1, motor2, motor3, motor4, FORWARD, speed);
}

void car_back(AF_DCMotor *motor1, AF_DCMotor *motor2, AF_DCMotor *motor3, AF_DCMotor *motor4, uint8_t speed) {
  move_motors(motor1, motor2, motor3, motor4, BACKWARD, speed);
}

// Diagonal and turning movement
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

// Stop all motors
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
