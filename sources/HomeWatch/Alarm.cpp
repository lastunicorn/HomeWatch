#include "Alarm.h"

Alarm::Alarm(Logger *logger, Sounds *sounds)
{
  this->logger = logger;
  this->sounds = sounds;

  pinMode(pinOn, OUTPUT);
  pinMode(pinOff, OUTPUT);
  pinMode(pinAlarm, OUTPUT);

  digitalWrite(pinOn, LOW);
  digitalWrite(pinOff, HIGH);
  digitalWrite(pinAlarm, LOW);
}

void Alarm::init()
{
  smsSender.connect();
}

void Alarm::trigger(String sensorName)
{
  unsigned long now = millis();

  if (lastAlarmTime != 0 && now - lastAlarmTime <= repeatInterval)
  {
    logger->write("Not triggered because of alarm repeat interval.");
    return;
  }

  lastAlarmTime = now;

  logger->write("!!! alarm, alarm, alarm !!! - Alarm triggered by " + sensorName + " sensor.");

  // led on
  digitalWrite(pinAlarm, HIGH);

  // make sound
  sounds->makeAlarmSound();

  // send sms
  String message;
  message += "alarm acasa - ";
  message += sensorName;

  char str[message.length() + 1];
  message.toCharArray(str, message.length() + 1);

  smsSender.sendSMS("0723002252", str);

  // led off
  digitalWrite(pinAlarm, LOW);
}
