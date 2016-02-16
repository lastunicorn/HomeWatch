#include "Arduino.h"
#include "Listener.h"
#include "Logger.h"
#include "Sounds.h"

String formatTimeAsString(unsigned long milliseconds);

Listener::Listener(Logger *logger, Sounds *sounds, Alarm *alarm)
{
  this->logger = logger;
  this->sounds = sounds;
  this->alarm = alarm;

  mySwitch.enableReceive(0);

  pinMode(pinOn, OUTPUT);
  pinMode(pinOff, OUTPUT);

  digitalWrite(pinOn, LOW);
  digitalWrite(pinOff, HIGH);
}

void Listener::refresh()
{
  lastNow = millis();
  unsigned long timeFromLastStart = lastNow - lastStartTime;

  if (on == true && timeFromLastStart <= startDelay)
    sounds->makeStartingSound();

  if (mySwitch.available())
  {
    sensorValue = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();

    logSensorValue();

    if (sensorValue == onId1)
    {
      handleOnButton1Pressed();
    }
    else if (sensorValue == onId2)
    {
      handleOnButton2Pressed();
    }
    else if (sensorValue == offId1)
    {
      handleOffButton1Pressed();
    }
    else if (sensorValue == offId2)
    {
      handleOffButton2Pressed();
    }
    else if (sensorValue == doorSensorId)
    {
      handleDoorSensorTriggered();
    }
    else if (sensorValue == motionSensorId)
    {
      handleMotionSensorTriggered();
    }
  }
}

void Listener::logSensorValue()
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

  logger->write(s);
}

void Listener::handleOnButton1Pressed()
{
  if (lastNow - lastOnButton1Time <= 2000)
    return;

  lastOnButton1Time = lastNow;
  turnOn();
}

void Listener::handleOnButton2Pressed()
{
  if (lastNow - lastOnButton2Time <= 2000)
    return;

  lastOnButton2Time = lastNow;
  turnOn();
}

void Listener::turnOn()
{
  logger->write("Turning sensor listener on.");
  on = true;
  lastStartTime = lastNow;

  digitalWrite(pinOn, HIGH);
  digitalWrite(pinOff, LOW);
}

void Listener::handleOffButton1Pressed()
{
  if (lastNow - lastOffButton1Time <= 2000)
    return;

  lastOffButton1Time = lastNow;

  turnOff();
}

void Listener::handleOffButton2Pressed()
{
  if (lastNow - lastOffButton2Time <= 2000)
    return;

  lastOffButton2Time = lastNow;

  turnOff();
}

void Listener::turnOff()
{
  logger->write("Turning sensor listener off.");
  on = false;

  digitalWrite(pinOn, LOW);
  digitalWrite(pinOff, HIGH);

  sounds->makeOffSound();
}

void Listener::handleDoorSensorTriggered()
{
  if (lastNow - lastDoorSensorTime <= 2000)
    return;

  lastDoorSensorTime = lastNow;

  if (on == false)
  {
    logger->write("Not triggered because sensor listener is off.");
    return;
  }

  unsigned long timeFromLastStart = lastNow - lastStartTime;
  if (timeFromLastStart <= startDelay)
  {
    logger->write("Not triggered because of start delay.");
    return;
  }

  alarm->trigger("door");
}

void Listener::handleMotionSensorTriggered()
{
  if (lastNow - lastMotionSensorTime <= 2000)
    return;

  lastMotionSensorTime = lastNow;

  if (on == false)
  {
    logger->write("Not triggered because sensor listener is off.");
    return;
  }

  unsigned long timeFromLastStart = lastNow - lastStartTime;
  if (timeFromLastStart <= startDelay)
  {
    logger->write("Not triggered because of start delay.");
    return;
  }

  alarm->trigger("motion");
}
