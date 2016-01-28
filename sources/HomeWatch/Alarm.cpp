#include "Arduino.h"
#include "Alarm.h"
#include "Logger.h"

String formatTimeAsString(unsigned long milliseconds);
extern Logger logger;

Alarm::Alarm()
{
  pinMode(sensorPin, INPUT);
}

boolean Alarm::isTriggered()
{
  sensorValue = analogRead(sensorPin);

  if (sensorValue < 100)
  {
    unsigned long now = millis();
    elapsedTime = now - lastAlarmTime;

    String s;

    s += "sensor triggered: ";
    s += sensorValue;
    s += " - time from last alarm: ";
    s += formatTimeAsString(elapsedTime);

    logger.write(s);

    if (now > alarmDelay)
    {
      if (elapsedTime > alarmInterval)
      {
        logger.write("!!! alarm, alarm, alarm !!!");
        logger.write(1);
        lastAlarmTime = now;

        return true;
      }
    }
  }

  return false;
}
