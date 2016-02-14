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

    logSensorValue();

    if (isOnButtonPressed())
    {
      handleOnButtonPressed();
      return;
    }

    if (isOffButtonPressed())
    {
      handleOffButtonPressed();
      return;
    }

    if (isKnownSensor())
    {
      handleSensorTriggered();
      return;
    }
  }
}

void Alarm::resetTriggerFlags()
{
  isTriggered = false;
  isDoorTriggered = false;
  isMotionTriggered = false;
}

void Alarm::logSensorValue()
{
  String s;

  s += "Value received: ";
  s += sensorValue;

  if (sensorValue == doorSensorId)
    s += " - door sensor";
  else if (sensorValue == motionSensorId)
    s += " - motion sensor";
  else if (sensorValue == onId1)
    s += " - remote 1 on";
  else if (sensorValue == offId1)
    s += " - remote 1 off";
  else if (sensorValue == onId2)
    s += " - remote 2 on";
  else if (sensorValue == offId2)
    s += " - remote 2 off";
  else
    s += " - unknown";

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

void Alarm::handleOnButtonPressed()
{
  if (lastNow - lastStartTime <= 2000)
  {
    logger.write("Ignored");
    return;
  }

  logger.write("Turning alarm on.");
  on = true;
  lastStartTime = lastNow;
}

void Alarm::handleOffButtonPressed()
{
  if (lastNow - lastStopTime <= 2000)
  {
    logger.write("Ignored");
    return;
  }

  logger.write("Turning alarm off.");
  on = false;
  lastStopTime = lastNow;
  sounds.makeOffSound();
}

boolean Alarm::isKnownSensor()
{
  return sensorValue == doorSensorId || sensorValue == motionSensorId;
}

void Alarm::handleSensorTriggered()
{
  if (on == false)
  {
    logger.write("Not triggered because alarm is off.");
    return;
  }

  unsigned long timeFromLastStart = lastNow - lastStartTime;
  if (timeFromLastStart <= startDelay)
  {
    logger.write("Not triggered because of start delay.");
    return;
  }

  unsigned long timeFromLastAlarm = lastNow - lastAlarmTime;
  if (timeFromLastAlarm <= repeatInterval)
  {
    logger.write("Not triggered because of alarm repeat interval.");
    return;
  }

  if (sensorValue == doorSensorId)
  {
    lastAlarmTime = lastNow;
    isTriggered = true;
    isDoorTriggered = true;

    logger.write("!!! alarm, alarm, alarm !!! - Alarm triggered by door.");
  }

  if (sensorValue == motionSensorId)
  {
    lastAlarmTime = lastNow;
    isTriggered = true;
    isMotionTriggered = true;

    logger.write("!!! alarm, alarm, alarm !!! - Alarm triggered by motion.");
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
