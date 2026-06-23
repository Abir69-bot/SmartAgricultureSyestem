#include "config.h"
#include "functions.h"


LiquidCrystal_I2C lcd(0x27, 16, 2); // Address 0x27 for 16x2 text matrix
DHT dht(DHT_PIN, DHTTYPE);
Servo myservo;

unsigned long lastDHTRead   = 0;
const unsigned long dhtInterval = 2000; // Refresh temperature every 2 seconds

unsigned long lastScrollTime = 0;
const unsigned long scrollInterval = 300; // Advance scrolling status text every 300ms

unsigned long lastLEDBlink  = 0;
const unsigned long blinkInterval = 250; // Alert blinking pulse speed


float currentTemperature = 24.5; 
bool blinkAlertActive = false;
bool ledState = HIGH; // HIGH represents an OFF state for the active-LOW PC13 pin

String scrollMessage = "";
int scrollIndex = 0;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Maintain default off state on startup
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Wake up peripheral sensors and motor controllers
  dht.begin();
  myservo.attach(SERVO_PIN);
  myservo.write(90); // Initialize at default 90-degree angle
  
  // Power up and establish communication with I2C LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // 1. Gather Soil Moisture metrics through the noise reduction filter
  int soilPercent = readSoilMoisture();
  updateLedIndicator(soilPercent, blinkAlertActive);

  // Fetch environmental tracking metrics from DHT11 periodically
  if (millis() - lastDHTRead >= dhtInterval) {
    lastDHTRead = millis();
    float newTemp = dht.readTemperature();
    if (!isnan(newTemp)) {
      currentTemperature = newTemp; // Update with validated numeric value
    }
  }

  // Measure proximity tracking data via the ultrasonic sensor
  int distance = readUltrasonicDistance();


  updateServoControl(currentTemperature);

  
  if (blinkAlertActive) {
    if (millis() - lastLEDBlink >= blinkInterval) {
      lastLEDBlink = millis();
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState); // Flash onboard active-LOW LED indicator
    }
    scrollMessage = "Soil Wet " + String(soilPercent) + "%   "; // Alert notification text
  } else {
    scrollMessage = "Soil OK " + String(soilPercent) + "%   ";  // Normal tracking text
  }

  // Refresh static telemetry data onto Top Row of LCD screen
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(currentTemperature, 1);
  lcd.print("C ");

  lcd.setCursor(9, 0);
  if (distance == -1) {
    lcd.print("No Obj "); // Timeout target check notification string
  } else {
    lcd.print("D:");
    lcd.print(distance);
    lcd.print("cm   "); // Active item distance metric output
  }

  // Manage background ticker rendering of Bottom Row scrolling messaging banner
  if (millis() - lastScrollTime >= scrollInterval) {
    lastScrollTime = millis();
    
    lcd.setCursor(0, 1);
    String displayStr = "";
    for (int i = 0; i < 16; i++) {
      int charIndex = (scrollIndex + i) % scrollMessage.length();
      displayStr += scrollMessage[charIndex];
    }
    lcd.print(displayStr); // Render specific 16-character string slice to LCD
    
    scrollIndex++;
    if (scrollIndex >= scrollMessage.length()) {
      scrollIndex = 0; // Reset scroll index when text bounds are crossed
    }
  }
}