#include <GSM.h>
//#include <SPI.h>
//#include <SD.h>
#include "SmsSender.h"
#include "Alarm.h"
#include "Logger.h"
#include "Sounds.h"

const int alarmLedPin = 8;

Alarm alarm;
SmsSender smsSender;
Sounds sounds;

Logger logger;

void setup() {
  Serial.begin(9600);

  pinMode(alarmLedPin, OUTPUT);
  digitalWrite(alarmLedPin, LOW);

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
  digitalWrite(alarmLedPin, HIGH);

  // make sound
  sounds.makeAlarmSound();

  // send sms
  if (alarm.isDoorTriggered)
    smsSender.sendSMS("0723002252", "alarm acasa - door");
  else  if (alarm.isMotionTriggered)
    smsSender.sendSMS("0723002252", "alarm acasa - motion");
  else
    smsSender.sendSMS("0723002252", "alarm acasa");

  // led off
  digitalWrite(alarmLedPin, LOW);
}
