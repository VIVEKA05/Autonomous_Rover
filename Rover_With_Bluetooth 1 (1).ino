#include <Servo.h>
#include <NewPing.h>



// -------- Motor control pins (L298N) --------
const int LeftMotorForward = 2;
const int LeftMotorBackward = 3;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

// -------- Ultrasonic Sensor --------
#define trigPin 6
#define echoPin 7
#define maximum_distance 200

// -------- Servo --------
#define servoPin 8

// -------- Variables --------
boolean goesForward = false;
int distance = 100;
char command;
boolean autoMode = false;   // false = Bluetooth, true = Auto

// -------- Objects --------
NewPing sonar(trigPin, echoPin, maximum_distance);
Servo servo_motor;

// -------------------------------------------------
void setup() {

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(servoPin);
  servo_motor.write(90);

  Serial.begin(9600);
  Serial.println("System Ready");
  Serial.println("Mode: Bluetooth Control");

  moveStop();   // keep idle at start
}

// -------------------------------------------------
void loop() {

  // ---------- Bluetooth Command Reading ----------
  if (Serial.available()) {
    command = Serial.read();
    Serial.print("Command: ");
    Serial.println(command);

    if (command == 'A') {
      autoMode = true;
      Serial.println("Switched to AUTO mode");
      distance = readPing();
      return;
    }

    if (command == 'P') {
      autoMode = false;
      Serial.println("Switched to BLUETOOTH mode");
      moveStop();
      return;
    }
  }

  // ---------- BLUETOOTH MODE ----------
  if (!autoMode) {

    if (command == 'F') moveForward();
    else if (command == 'B') moveBackward();
    else if (command == 'L') turnLeft();
    else if (command == 'R') turnRight();
    else if (command == 'S') moveStop();

    return;   // IMPORTANT: stop auto logic
  }

  // ---------- AUTOMATIC MODE (UNCHANGED LOGIC) ----------
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20) {
    moveStop();
    delay(200);

    moveBackward();
    delay(300);

    moveStop();
    delay(200);

    distanceRight = lookRight();
    delay(150);
    distanceLeft = lookLeft();
    delay(150);

    if (distanceRight >= distanceLeft) {
      turnRight();
    } else {
      turnLeft();
    }
  } else {
    moveForward();
  }

  distance = readPing();
}

// -------------------------------------------------
void moveServoSlow(int fromAngle, int toAngle) {
  if (fromAngle < toAngle) {
    for (int pos = fromAngle; pos <= toAngle; pos++) {
      servo_motor.write(pos);
      delay(20);
    }
  } else {
    for (int pos = fromAngle; pos >= toAngle; pos--) {
      servo_motor.write(pos);
      delay(15);
    }
  }
}

// -------------------------------------------------
int lookRight() {
  moveServoSlow(90, 30);
  delay(200);
  int d = readPing();
  moveServoSlow(30, 90);
  return d;
}

// -------------------------------------------------
int lookLeft() {
  moveServoSlow(90, 150);
  delay(200);
  int d = readPing();
  moveServoSlow(150, 90);
  return d;
}

// -------------------------------------------------
int readPing() {
  delay(50);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 250;
  return cm;
}

// -------------------------------------------------
void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

// -------------------------------------------------
void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}

// -------------------------------------------------
void moveBackward() {
  goesForward = false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

// -------------------------------------------------
void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(600);
  moveStop();
}

// -------------------------------------------------
void turnLeft() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(600);
  moveStop();
}
