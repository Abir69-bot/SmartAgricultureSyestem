#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "config.h"

// External references to object instances initialized in main file
extern LiquidCrystal_I2C lcd;
extern DHT dht;
extern Servo myservo;

// Tracks active servo position to prevent rewrite wear and jitter
static int currentServoPos = -1; 


inline int readSoilMoisture() {
  long totalAnalog = 0;
  for (int i = 0; i < 5; i++) {
    totalAnalog += analogRead(SOIL_PIN); // Take 5 successive reads
    delay(10); 
  }
  int avgAnalog = totalAnalog / 5;
  
  // Convert 12-bit ADC value (0-4095) to 0-100%
  int soilPercent = map(avgAnalog, 4095, 0, 0, 100); 
  return constrain(soilPercent, 0, 100);
}


inline int readUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); // 10µs High pulse to trigger pin
  digitalWrite(TRIG_PIN, LOW);

  // Measure response duration with an integrated hardware timeout
  long duration = pulseIn(ECHO_PIN, HIGH, US_TIMEOUT); 
  
  if (duration <= 0) {
    return -1; // Flag indicating "No Obj"
  }
  return duration * 0.034 / 2; // Calculate distance in cm
}


inline void updateServoControl(float currentTemp) {
  // Rotate to 180° if temperature exceeds 25°C, otherwise return to 90°
  int targetPos = (currentTemp > TEMP_THRESHOLD) ? 180 : 90;
  
  if (targetPos != currentServoPos) { 
    myservo.write(targetPos); // Only write if a true threshold change happens
    currentServoPos = targetPos;
  }
}


inline void updateLedIndicator(int soilPercent, bool &shouldBlink) {
  if (soilPercent >= SOIL_THRESHOLD) {
    shouldBlink = true; // Flag for loop asynchronous blinking
  } else {
    shouldBlink = false;
    digitalWrite(LED_PIN, HIGH); // Turn off the active-LOW onboard LED
  }
}

#endif