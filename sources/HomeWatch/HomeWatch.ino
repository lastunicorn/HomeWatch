#include <GSM.h>
//#include <SPI.h>
//#include <SD.h>
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
  alarm.refresh();

  if (alarm.isTriggered)
    triggerAlarm();

  delay(500);
}

void triggerAlarm()
{
  // led on
  digitalWrite(ledPin, HIGH);

  // make sound
  makeAlarmSound();

  // send sms
  if (alarm.isDoorTriggered)
    smsSender.sendSMS("0723002252", "alarm acasa - door");
  else  if (alarm.isMotionTriggered)
    smsSender.sendSMS("0723002252", "alarm acasa - motion");
  else
    smsSender.sendSMS("0723002252", "alarm acasa");

  // led off
  digitalWrite(ledPin, LOW);
}
