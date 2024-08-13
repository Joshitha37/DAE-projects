#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
const int redLED = 2;
const int blueLED = 3;
const int moistureSensorPin = A0;
const int gasSensorPin = A1;
const int potPin = A2;

// Initialize the LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LED pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  // Initialize the LCD
  lcd.init();  // Initialize the LCD
  lcd.backlight();

  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int moistureValue = analogRead(moistureSensorPin);
  int gasValue = analogRead(gasSensorPin);
  int potValue = analogRead(potPin);

  // Map the potentiometer value to a threshold range (0-1023 to 0-500)
  int moistureThreshold = map(potValue, 0, 1023, 0, 500);
  int gasThreshold = 400; // Fixed threshold, can also be dynamic based on another potentiometer if needed

  // Print sensor values to the serial monitor
  Serial.print("Moisture Value: ");
  Serial.print(moistureValue);
  Serial.print(" | Gas Value: ");
  Serial.print(gasValue);
  Serial.print(" | Moisture Threshold: ");
  Serial.println(moistureThreshold);

  // Display sensor values and thresholds on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moist: ");
  lcd.print(moistureValue);
  lcd.print(" Th:");
  lcd.print(moistureThreshold);
  lcd.setCursor(0, 1);
  lcd.print("Gas: ");
  lcd.print(gasValue);
  lcd.print(" Th:400");

  // Check moisture level
  if (moistureValue < moistureThreshold) {
    digitalWrite(redLED, HIGH); // Turn on red LED
  } else {
    digitalWrite(redLED, LOW); // Turn off red LED
  }

  // Check gas level
  if (gasValue > gasThreshold) {
    digitalWrite(blueLED, HIGH); // Turn on blue LED
  } else {
    digitalWrite(blueLED, LOW); // Turn off blue LED
  }

  // Wait for a second before the next loop
  delay(1000);
}
