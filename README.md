# 🚗 Bluetooth & Autonomous Rover

## 📌 Project Overview
This project implements a dual-mode smart rover using the Arduino Uno. 
The rover operates in both Bluetooth manual control mode and autonomous obstacle avoidance mode. 
It uses real-time distance sensing and intelligent decision-making to navigate obstacles.

---

## 🛠 Hardware Used
- Arduino Uno
- L298N Motor Driver
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- Bluetooth Module (HC-05 / HC-06)
- DC Motors
- Chassis & Wheels

---

## 💻 Software & Libraries Used
- Arduino IDE
- Servo.h Library
- NewPing.h Library
- Embedded C (Arduino Framework)

---

## ⚙ Features
- Dual Mode Operation (Manual + Auto)
- Bluetooth Wireless Control
- Obstacle Detection and Avoidance
- Servo-Based Direction Scanning
- Real-Time Motor Control

---

## 📡 Operating Modes

### 🔹 Bluetooth Mode
Control the rover using commands:
- F – Forward  
- B – Backward  
- L – Left  
- R – Right  
- S – Stop  
- A – Switch to Auto Mode  
- P – Switch to Bluetooth Mode  

### 🔹 Autonomous Mode
- Detects obstacles within 20 cm  
- Stops and reverses  
- Scans left and right  
- Chooses the clearer path automatically  

---

## 🎯 Applications
- Robotics Learning
- Embedded Systems Projects
- Autonomous Vehicle Prototype
- Educational Demonstration Platform
