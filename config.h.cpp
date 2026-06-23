#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>


#define SOIL_PIN        PA0   // Analog input for Soil Moisture sensor
#define SERVO_PIN       PA1   // PWM output pin for Servo Motor
#define TRIG_PIN        PB8   // Ultrasonic Trigger Pin
#define ECHO_PIN        PB9   // Ultrasonic Echo Pin
#define DHT_PIN         PB10  // DHT11 Digital Data Pin
#define LED_PIN         PC13  // Onboard LED (Active LOW on Blue Pill)

#define DHTTYPE         DHT11 // Sensor module type
const float TEMP_THRESHOLD = 25.0; // Rotation threshold temperature in Celsius
const int SOIL_THRESHOLD   = 70;   // Over-watering alert percentage value
const uint32_t US_TIMEOUT  = 30000; // Ultrasonic echo response timeout in microseconds

#endif