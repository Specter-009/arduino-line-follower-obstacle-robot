#include <AFMotor.h>

// -------- IR SENSOR PINS --------
#define irLeft A2
#define irCenter A4
#define irRight A3

// -------- ULTRASONIC + SERVO --------
#define trigger A0
#define echo A1
#define servo 10

int Set = 20;
int distance_L, distance_F, distance_R;

// -------- MOTOR OBJECTS --------
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int speed = 175;

void setup() {

  Serial.begin(9600);

  pinMode(irLeft, INPUT);
  pinMode(irCenter, INPUT);
  pinMode(irRight, INPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(servo, OUTPUT);

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  // Initialize servo sweep
  for (int angle = 70; angle <= 140; angle += 5) {
    servoPulse(servo, angle);
  }
  for (int angle = 140; angle >= 0; angle -= 5) {
    servoPulse(servo, angle);
  }
  for (int angle = 0; angle <= 70; angle += 5) {
    servoPulse(servo, angle);
  }

  distance_F = Ultrasonic_read();
  delay(500);
}

void loop() {

  distance_F = Ultrasonic_read();
  Serial.print("D F=");
  Serial.println(distance_F);

  // =========================
  // OBSTACLE CHECK (SECONDARY)
  // =========================
  if(distance_F < Set){
    Check_side();
    return;
  }

  // =========================
  // LINE FOLLOWING (PRIMARY)
  // =========================

  int left = digitalRead(irLeft);
  int center = digitalRead(irCenter);
  int right = digitalRead(irRight);

  if(center == 1) {

    if(left == 0 && right == 0) {
      Serial.println("Move Forward");
      moveForward();
    }

    else if(left == 0 && right == 1) {
      Serial.println("Sharp Left");
      sharpLeft();
    }

    else if(center == 1 && right == 1) {
      Serial.println("Sharp Left");
      sharpLeft();
    }

    else if(left == 1 && right == 0) {
      Serial.println("Sharp Right");
      sharpRight();
    }

    else if(center == 1 && left == 1) {
      Serial.println("Sharp Right");
      sharpRight();
    }

    else if(left == 1 && right == 1) {
      Serial.println("Stop");
      Stop();
    }
  }

  else {

    if(left == 0 && right == 1) {
      Serial.println("Left");
      turnLeft();
    }

    else if(left == 1 && right == 0) {
      Serial.println("Right");
      turnRight();
    }

    else if(left == 0 && right == 0) {
      Serial.println("Line Lost! Stop");
      Stop();
    }
  }

  delay(5);
}


// =========================
// MOTOR FUNCTIONS
// =========================

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void sharpLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void sharpRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}


// =========================
// SERVO CONTROL
// =========================

void servoPulse(int pin, int angle){

  int pwm = (angle * 11) + 500;

  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);

  digitalWrite(pin, LOW);
  delay(30);
}


// =========================
// ULTRASONIC SENSOR
// =========================

long Ultrasonic_read(){

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);

  long time = pulseIn(echo, HIGH);

  return time / 29 / 2;
}


// =========================
// OBSTACLE AVOIDANCE
// =========================

void Check_side(){

  Stop();
  delay(100);

  for (int angle = 70; angle <= 140; angle += 5){
    servoPulse(servo, angle);
  }

  delay(300);

  distance_R = Ultrasonic_read();
  Serial.print("D R=");
  Serial.println(distance_R);

  delay(100);

  for (int angle = 140; angle >= 0; angle -= 5){
    servoPulse(servo, angle);
  }

  delay(500);

  distance_L = Ultrasonic_read();
  Serial.print("D L=");
  Serial.println(distance_L);

  delay(100);

  for (int angle = 0; angle <= 70; angle += 5){
    servoPulse(servo, angle);
  }

  delay(300);

  compareDistance();
}


void compareDistance(){

  if(distance_L > distance_R){

    turnLeft();
    delay(500);

    moveForward();
    delay(400);

    turnRight();
    delay(500);

    moveForward();
    delay(500);

    turnRight();
    delay(400);

    moveForward();
    delay(420);
  }

  else{

    turnRight();
    delay(500);

    moveForward();
    delay(400);

    turnLeft();
    delay(500);

    moveForward();
    delay(500);

    turnLeft();
    delay(400);

    moveForward();
    delay(420);
  }
}  