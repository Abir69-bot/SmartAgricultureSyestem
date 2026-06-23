# 🌱 Smart Agriculture System

A smart farming solution built using the STM32 Blue Pill Microcontroller that monitors environmental conditions in real time and automates agricultural responses. The system integrates multiple sensors to measure temperature, soil moisture, and distance, while providing automated control through a servo motor and visual alerts.


## 📌 Project Overview

Traditional farming often lacks continuous monitoring of environmental conditions, which can lead to inefficient water usage and poor crop management. This project addresses these challenges by developing an automated monitoring system capable of:

Measuring soil moisture levels
Monitoring ambient temperature
Detecting distance/water levels using ultrasonic sensing
Controlling a servo motor automatically based on temperature thresholds
Providing real-time feedback through an LCD display and LED indicators
The system is designed to be affordable, energy-efficient, and suitable for small to medium-scale agricultural applications.

## 🚀 Features

### 🌡 Temperature Monitoring
- Uses a DHT11 sensor to measure ambient temperature.
- Displays temperature readings in real time.
- Automatically controls servo position based on temperature thresholds.

### 🌱 Soil Moisture Monitoring
- Measures soil moisture percentage using an analog soil moisture sensor.
- Applies averaging techniques to reduce sensor noise.
- Triggers visual alerts when soil moisture exceeds predefined thresholds.

### 📏 Distance Measurement
- Uses an HC-SR04 Ultrasonic Sensor.
- Measures distance for water-level monitoring or object detection.
- Handles timeout conditions gracefully.

### 🔄 Automated Servo Control
- Rotates to 180° when temperature exceeds 25°C.
- Returns to 90° when temperature falls below the threshold.
- Optimized to avoid unnecessary servo movements and jitter.

### 💡 LED Alert System
- Blinks when soil moisture reaches or exceeds 70%.
- Provides immediate visual indication of over-watered conditions.

### 📟 LCD Display
- Displays temperature and distance measurements.
- Shows scrolling soil status information.
- Updates data in real time.

## 📊 System Workflow
- Read temperature from the DHT11 sensor.
- Read soil moisture data from the analog sensor.
- Measure distance using the HC-SR04 sensor.
- Display all sensor data on the LCD.
- Compare temperature against the threshold.
- Control servo motor accordingly.
- Trigger LED alerts based on soil moisture level.
- Continuously repeat the monitoring cycle.

## ⚙️ Technologies Used
Embedded C/C++
STM32 Blue Pill
Arduino Framework
I2C Communication
Sensor Interfacing
Servo Motor Control
ADC (Analog-to-Digital Conversion)


## 📂 Project Structure

```text
Smart-Agriculture-System/
├── SmartAgricultureSystem.ino
├── functions.h
├── config.h
├── README.md
├── Documentation/
│   └── Project_Report.pdf
└── Images/
    └── system_diagram.png
```
    

## Future Enhancements

1. Wi-Fi/Bluetooth-based remote monitoring
2. Mobile application dashboard for real-time monitoring
3. Automated irrigation control system
4. GSM-based SMS notifications and alerts
5. Cloud data storage and analytics
6. Solar-powered deployment for energy efficiency
7. Multi-zone soil moisture monitoring
