#include "Arduino.h"
#include "Alarm.h"
#include "Logger.h"

void makeStartingSound();
String formatTimeAsString(unsigned long milliseconds);
extern Logger logger;

Alarm::Alarm()
{
  pinMode(sensorPin, INPUT);
  mySwitch.enableReceive(0);
}

void Alarm::refresh()
{
  resetTriggerFlags();

  lastNow = millis();
  unsigned long timeFromLastStart = lastNow - startTime;

  if (on == true && timeFromLastStart <= startDelay)
    makeStartingSound();

  if (mySwitch.available())
  {
    sensorValue = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();

    unsigned long timeFromLastAlarm = lastNow - lastAlarmTime;

    String s;

    s += "sensor triggered: ";
    s += sensorValue;
    s += " - time from last alarm: ";
    s += formatTimeAsString(timeFromLastAlarm);

    logger.write(s);

    // Remote On button was pressed.
    if (sensorValue == onId1 || sensorValue == onId2)
    {
      logger.write("Turning alarm on.");
      on = true;
      startTime = lastNow;
      return;
    }

    // Remote Off button was pressed.
    if (sensorValue == offId1 || sensorValue == offId2)
    {
      logger.write("Turning alarm off.");
      on = false;
      return;
    }

    if (on == false)
    {
      logger.write("Not triggered because alarm is off.");
      return;
    }

    if (sensorValue == doorSensorId || sensorValue == motionSensorId)
    {
      if (timeFromLastStart <= startDelay)
      {
        logger.write("Not triggered because of start delay.");
        return;
      }

      if (timeFromLastAlarm <= alarmRepeatInterval)
      {
        logger.write("Not triggered because of alarm repeat interval.");
        return;
      }

      triggerAlarm();

      return;
    }

    logger.write("Not triggered because unknown signal.");
  }
}

void Alarm::resetTriggerFlags()
{
  isTriggered = false;
  isDoorTriggered = false;
  isMotionTriggered = false;
}

void Alarm::triggerAlarm()
{
  logger.write("!!! alarm, alarm, alarm !!!");
  lastAlarmTime = lastNow;

  isTriggered = true;

  if (sensorValue == doorSensorId)
  {
    logger.write("Alarm triggered by door.");
    isDoorTriggered = true;
  }

  if (sensorValue == motionSensorId)
  {
    logger.write("Alarm triggered by motion.");
    isMotionTriggered = true;
  }
}

//boolean Alarm::isTriggered()
//{
//  sensorValue = analogRead(sensorPin);
//
//  if (sensorValue < 100)
//  {
//    unsigned long now = millis();
//    elapsedTime = now - lastAlarmTime;
//
//    String s;
//
//    s += "sensor triggered: ";
//    s += sensorValue;
//    s += " - time from last alarm: ";
//    s += formatTimeAsString(elapsedTime);
//
//    logger.write(s);
//
//    if (now > alarmDelay)
//    {
//      if (elapsedTime > alarmInterval)
//      {
//        logger.write("!!! alarm, alarm, alarm !!!");
//        logger.write(1);
//        lastAlarmTime = now;
//
//        return true;
//      }
//    }
//  }
//
//  return false;
//}
