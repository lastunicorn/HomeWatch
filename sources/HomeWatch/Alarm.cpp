#include "Arduino.h"
#include "Alarm.h"
#include "Logger.h"
#include "Sounds.h"

void makeStartingSound();
String formatTimeAsString(unsigned long milliseconds);
extern Logger logger;
extern Sounds sounds;

Alarm::Alarm()
{
  mySwitch.enableReceive(0);
}

void Alarm::refresh()
{
  resetTriggerFlags();

  lastNow = millis();
  unsigned long timeFromLastStart = lastNow - lastStartTime;

  if (on == true && timeFromLastStart <= startDelay)
    sounds.makeStartingSound();

  if (mySwitch.available())
  {
    sensorValue = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();

    unsigned long timeFromLastAlarm = lastNow - lastAlarmTime;

    logSensorValue(timeFromLastAlarm);

    if (isOnButtonPressed())
    {
      start();
      return;
    }

    if (isOffButtonPressed())
    {
      if (lastNow - lastStopTime >= 2000)
        stop();

      return;
    }

    if (on == false)
    {
      logger.write("Not triggered because alarm is off.");
      return;
    }

    if (sensorValue != doorSensorId && sensorValue != motionSensorId)
    {
      logger.write("Not triggered because unknown signal.");
    }

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
  }
}

void Alarm::resetTriggerFlags()
{
  isTriggered = false;
  isDoorTriggered = false;
  isMotionTriggered = false;
}

void Alarm::logSensorValue(unsigned long timeFromLastAlarm)
{
  String s;

  s += "sensor triggered: ";
  s += sensorValue;
  s += " - time from last alarm: ";
  s += formatTimeAsString(timeFromLastAlarm);

  logger.write(s);
}

boolean Alarm::isOnButtonPressed()
{
  return sensorValue == onId1 || sensorValue == onId2;
}

boolean Alarm::isOffButtonPressed()
{
  return sensorValue == offId1 || sensorValue == offId2;
}

void Alarm::start()
{
  logger.write("Turning alarm on.");
  on = true;
  lastStartTime = lastNow;
}

void Alarm::stop()
{
  logger.write("Turning alarm off.");
  on = false;
  lastStopTime = lastNow;
  sounds.makeOffSound();
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
