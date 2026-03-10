
# Line Follower Robot with Obstacle Avoidance

## Overview

This project implements a line follower robot with obstacle avoidance using an Arduino and a motor driver shield. The robot follows a black line using three infrared sensors while continuously monitoring the distance ahead with an ultrasonic sensor. When an obstacle is detected within a predefined distance, the robot scans the surroundings using a servo-mounted ultrasonic sensor and chooses the direction with more space to navigate around the obstacle.

## Features

* Line following using three IR sensors (left, center, right)
* Obstacle detection using an ultrasonic sensor
* Servo-based scanning to check left and right paths
* Automatic decision making to avoid obstacles
* Motor control using the Adafruit Motor Shield library

## Hardware Components

* Arduino Uno or compatible board
* Adafruit Motor Shield (L293D based)
* 4 DC motors
* 3 IR line tracking sensors
* HC-SR04 ultrasonic sensor
* Servo motor for ultrasonic scanning
* Robot chassis and wheels
* Battery power supply

## Pin Configuration

### IR Sensors

* Left IR Sensor: A2
* Center IR Sensor: A4
* Right IR Sensor: A3

### Ultrasonic Sensor

* Trigger Pin: A0
* Echo Pin: A1

### Servo

* Servo Control Pin: 10

### Motors (Motor Shield)

* Motor1 and Motor2: Left side motors
* Motor3 and Motor4: Right side motors

## How It Works

### Line Following

The robot uses three IR sensors to detect the line.

* If the center sensor detects the line, the robot moves forward.
* If the right sensor detects the line, the robot turns right.
* If the left sensor detects the line, the robot turns left.
* If the line is lost, the robot stops.

### Obstacle Detection

The ultrasonic sensor continuously measures the distance in front of the robot.

A threshold distance is defined in the code:

int Set = 20;

If an obstacle is detected closer than this value (in centimeters), the robot temporarily stops following the line and begins the obstacle avoidance routine.

### Obstacle Avoidance

1. The robot stops.
2. The servo rotates the ultrasonic sensor to scan the right side.
3. The distance to the right is measured.
4. The servo rotates to scan the left side.
5. The distance to the left is measured.
6. The robot compares the two distances.
7. The robot chooses the direction with more space.
8. The robot performs a sequence of movements to bypass the obstacle and return to its path.

## Adjustable Parameters

### Obstacle Detection Distance

You can change the detection distance by modifying:

int Set = 20;

Increasing this value makes the robot react earlier to obstacles.

### Motor Speed

Motor speed can be adjusted using:

int speed = 175;

Higher values make the robot move faster.

### Servo Speed

Servo movement speed can be adjusted inside the `servoPulse` function by modifying the delay value.

## Compilation and Upload

1. Install the Arduino IDE.
2. Install the Adafruit Motor Shield Library.
3. Connect the Arduino board to your computer.
4. Upload the code to the board.
5. Power the robot and place it on a line track.

## Notes

* The obstacle avoidance movement uses delay-based timing, so distances may need adjustment depending on the robot speed and wheel size.
* Proper sensor alignment and calibration are important for reliable line tracking.

## License

This project is intended for educational and academic use.
