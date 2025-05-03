# The Shop Rover 🚗

The Shop Rover is a four-wheel drive robot car designed for simple shopping tasks, controlled via a smartphone.

## 📋 Table of Contents
- [Project Description](#project-description)
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Control Application](#control-application)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Project Description
The Shop Rover is a mobile robot project designed to facilitate shopping tasks. It is equipped with a Bluetooth control system allowing intuitive interaction via smartphone. The robot is built on a four-wheel drive robot car base and integrates various sensors and actuators for a complete experience.

## Features
- Remote control via Bluetooth
- Movement in four directions (forward, backward, left, right)
- Lighting system with white and red LEDs
- Ambient light detection via photoresistor
- Sound signal for interaction
- Rechargeable lithium-ion battery power supply

## Hardware Components
The project uses the following components:
- Four-wheel drive robot car chassis
- Arduino Uno R3 board
- HC-05 Bluetooth module
- L293D motor driver
- INR18650 – 2000mAh Lithium battery
- White and red LEDs
- Photoresistor (LDR)
- Buzzer

For more details about the components, check the [Hardware README](hardware/README.md).

## Project Structure
```
The_Shop_Rover/
├── hardware/           # Hardware documentation and schematics
│   ├── layout/        # Assembly plans
│   ├── architecture/  # Hardware architecture
│   ├── schematics/    # Electronic schematics
│   └── components/    # Component documentation
├── source/            # Arduino source code
│   ├── the_shop_rover.ino
│   └── car_control.c
├── include/           # Header files
│   └── car_control.h
└── docs/             # Additional documentation
```

## Installation
1. Download and install the Arduino IDE
2. Install the Adafruit Motor Shield library
3. Clone this repository
4. Open `source/the_shop_rover.ino` in the Arduino IDE
5. Upload the code to your Arduino Uno

## Control Application
To control The Shop Rover, you'll need to install the Bluetooth RC Controller application:

1. Download the application from [here](https://drive.usercontent.google.com/download?id=1Wrmlk7zawrU3TbYtjh0lwUrek8ABfNiz&export=download&authuser=0)
2. Install the APK file on your Android smartphone
3. Open the application and pair it with the HC-05 Bluetooth module
4. Use the on-screen controls to:
   - Move the car forward/backward
   - Turn left/right
   - Control the lights and buzzer

Note: The application is only available for Android devices.

## Usage
1. Ensure all components are properly connected
2. Power the robot with the lithium-ion battery
3. Enable Bluetooth on your smartphone
4. Connect to the HC-05 module
5. Use the control application to direct the robot

## Contributing
Contributions are welcome! To contribute:
1. Fork the project
2. Create a branch for your feature
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact
For questions or support, contact:
- Email: youness.sbai.work@gmail.com
- LinkedIn: [Youness SBAI](https://www.linkedin.com/in/y-sbai/)