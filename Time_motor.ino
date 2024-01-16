#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

// Motor control pins
int motorPin = 9; // Connect to relay module

void setup() {
  Serial.begin(9600);
  DateTime buildTime(F(__DATE__), F(__TIME__));
  rtc.begin();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    rtc.begin();

  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(motorPin, OUTPUT);
  DateTime now = rtc.now();
  Serial.println(now.minute());
}

void loop() {
  String timestring = F(__TIME__);
  String timestringSub = timestring.substring(0, 2);
  int time = atoi(timestringSub.c_str());
  Serial.println(time);

  if (time == 20 || time == 10) {
    // Turn on the motor
    turnOnMotor();
    turnOffMotor(); // Turn off the motor
    if(time == 20){
      delay(50400000);
    }
    else if(time == 10){
      delay(36000000);
    }
    
  }

  // Other tasks can be performed here
}

void turnOnMotor() {
  // Activate the relay to turn on the motor
  digitalWrite(motorPin, HIGH);
  delay(1000);
}

void turnOffMotor() {
  // Deactivate the relay to turn off the motor
  digitalWrite(motorPin, LOW);
}