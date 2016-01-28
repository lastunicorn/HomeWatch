#include "Arduino.h"
#include "Alarm.h"

String formatTimeAsString(unsigned long milliseconds);
void writeLog(String text);
void writeLog(unsigned long value);

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
    s += ::formatTimeAsString(elapsedTime);

    writeLog(s);

    if (now > alarmDelay)
    {
      if (elapsedTime > alarmInterval)
      {
        writeLog("!!! alarm, alarm, alarm !!!");
        writeLog(1);
        lastAlarmTime = now;

        return true;
      }
    }
  }

  return false;
}
