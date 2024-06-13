#include <Wire.h>  // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for I2C LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27, 16 column and 2 rows

const int gasSensorPin = A0;  // Analog pin for gas sensor
const int redLedPin = 7;     // Pin for red LED
const int greenLedPin = 4;   // Pin for green LED
const int fanPin = 5;         // Pin for fan control

const int pollutionThreshold = 1000;  // Adjust as per your sensor and requirements

void setup() {
  lcd.init();  // Initialize LCD
  lcd.backlight();  // Turn on backlight

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(fanPin, OUTPUT);

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read analog value from gas sensor
  int gasLevel = analogRead(gasSensorPin);

  // Convert analog value to a meaningful range (adjust according to your sensor)
  int gasPPM = map(gasLevel, 0, 1023, 0, 5000);  // Example mapping for MQ series gas sensor

  // Display project title and air quality on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality Monitor");
  lcd.setCursor(0, 1);

  // Check gas level and display air quality
  if (gasPPM > pollutionThreshold) {
    lcd.print("Status: Polluted");
    digitalWrite(redLedPin, HIGH);  // Turn on red LED
    digitalWrite(greenLedPin, LOW); // Turn off green LED
    digitalWrite(fanPin, HIGH);     // Turn on fan
  } else {
    lcd.print("Status: Normal  ");
    digitalWrite(redLedPin, LOW);   // Turn off red LED
    digitalWrite(greenLedPin, HIGH); // Turn on green LED
    digitalWrite(fanPin, LOW);      // Turn off fan
  }

  delay(1000);  // Adjust delay based on your requirement and sensor response time
}
