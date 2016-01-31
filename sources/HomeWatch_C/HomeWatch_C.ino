#include <GSM.h>
#include <SPI.h>
#include <SD.h>
#include "SmsSender.h"
#include "Alarm.h"
#include "Logger.h"

const int ledPin = 8;
const int piezoPin = 9;

Alarm alarm;
SmsSender smsSender;

Logger logger;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  smsSender.connect();

  logger.write("=======================================================");
  logger.write("Arduino started");
  logger.write("=======================================================");
}

void loop() {
  boolean isTriggered = alarm.isTriggered();

  if (isTriggered)
    triggerAlarm();

  delay(500);
}

void triggerAlarm()
{
  // led on
  digitalWrite(ledPin, HIGH);

  // make sound
  tone(piezoPin, 200, 500);
  delay(500);
  tone(piezoPin, 100, 500);
  delay(500);
  tone(piezoPin, 200, 500);
  delay(500);
  tone(piezoPin, 100, 500);
  delay(500);

  // send sms
  smsSender.sendSMS("0723002252", "alarm acasa");

  // led off
  digitalWrite(ledPin, LOW);
}
