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

  pinMode(pinOn, OUTPUT);
  pinMode(pinOff, OUTPUT);

  digitalWrite(pinOn, LOW);
  digitalWrite(pinOff, HIGH);
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

    if (isDoorSensor())
    {
      handleDoorSensorTriggered();
      return;
    }

    if (isMotionSensor())
    {
      handleMotionSensorTriggered();
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
  
  digitalWrite(pinOn, HIGH);
  digitalWrite(pinOff, LOW);
}

boolean Alarm::isOffButtonPressed()
{
  return sensorValue == offId1 || sensorValue == offId2;
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

  digitalWrite(pinOn, LOW);
  digitalWrite(pinOff, HIGH);

  sounds.makeOffSound();
}

boolean Alarm::isDoorSensor()
{
  return sensorValue == doorSensorId;
}

void Alarm::handleDoorSensorTriggered()
{
  if (lastNow - lastDoorSensorTime <= 2000)
  {
    logger.write("Ignored");
    return;
  }

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

  lastAlarmTime = lastNow;
  lastDoorSensorTime = lastNow;
  isTriggered = true;
  isDoorTriggered = true;

  logger.write("!!! alarm, alarm, alarm !!! - Alarm triggered by door.");
}

boolean Alarm::isMotionSensor()
{
  return sensorValue == motionSensorId;
}

void Alarm::handleMotionSensorTriggered()
{
  if (lastNow - lastMotionSensorTime <= 2000)
  {
    logger.write("Ignored");
    return;
  }

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

  lastAlarmTime = lastNow;
  lastMotionSensorTime = lastNow;
  isTriggered = true;
  isMotionTriggered = true;

  logger.write("!!! alarm, alarm, alarm !!! - Alarm triggered by motion.");
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
