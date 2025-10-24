/*
  Project: Tilt + Sound + LCD + Buzzer
  Based on: LiquidCrystal "Hello World" example and Tilt Sensor reading
  This sketch displays tilt and sound sensor readings on a 16x2 LCD.
  When both are triggered, the buzzer sounds.
*/

#include <LiquidCrystal.h>

// LCD pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Components
int tiltSensor = 7;     // Tilt sensor pin
int soundPin = A0;      // Simulated sound sensor (potentiometer)
int buzzer = 9;       // buzzer pin
const int quiet = 10; //value
const int loud = 30;   //value
int pitch = 1000; //pitch value

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("System Starting...");
  delay(1500);
  lcd.clear();

  // Pin setup
  pinMode(tiltSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
}


void loop() {
  int tiltValue = digitalRead(tiltSensor);// value return by tilt sensor
  int soundValue = analogRead(soundPin); //value return by sound sensor

  // Debug values
  Serial.print("Tilt: ");
  Serial.print(tiltValue);
  Serial.print(" | Sound: ");
  Serial.println(soundValue);

  // Display tilt status


  // Display sound status
  lcd.setCursor(0, 1);

  if (tiltValue == HIGH) {
    if (soundValue <= quiet) { // when soundvalue is quiet
      lcd.print("QUIET        "); //print to lcd
      Serial.println("Quiet"); //serial print
      pitch = 250; //adjust pitch
    } else if ((soundValue > quiet) && ( soundValue <= loud)) { //if soundvalue is moderate)
      lcd.print("MODERATE        ");
      Serial.println("Moderate.");
      pitch = 500;
      
    } else if (soundValue > loud){
      lcd.print("LOUD        ");
      Serial.println("LOUD");
      pitch = 1000;
    }
    lcd.setCursor(0, 0);
    lcd.print("Tilt detected  ");
    tone(buzzer, pitch);  // Make sound
  } else {
    lcd.setCursor(0, 0);
    lcd.print("No tilt        ");
    noTone(buzzer);      // Silence
  }

  delay(200);
}