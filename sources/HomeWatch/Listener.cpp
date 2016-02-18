/*
   Home Watch
   Copyright (C) 2016  Dust in the Wind

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"
#include "Listener.h"
#include "Logger.h"

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

  if (isListening == true && timeFromLastStart <= startDelay)
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
  if (lastNow - lastOnButton1Time <= secondValueDelay)
    return;

  lastOnButton1Time = lastNow;
  turnOn();
}

void Listener::handleOnButton2Pressed()
{
  if (lastNow - lastOnButton2Time <= secondValueDelay)
    return;

  lastOnButton2Time = lastNow;
  turnOn();
}

void Listener::turnOn()
{
  logger->write("Turning sensor listener on.");

  isListening = true;
  lastStartTime = lastNow;

  digitalWrite(pinOn, HIGH);
  digitalWrite(pinOff, LOW);
}

void Listener::handleOffButton1Pressed()
{
  if (lastNow - lastOffButton1Time <= secondValueDelay)
    return;

  lastOffButton1Time = lastNow;

  turnOff();
}

void Listener::handleOffButton2Pressed()
{
  if (lastNow - lastOffButton2Time <= secondValueDelay)
    return;

  lastOffButton2Time = lastNow;

  turnOff();
}

void Listener::turnOff()
{
  logger->write("Turning sensor listener off.");
  isListening = false;

  digitalWrite(pinOn, LOW);
  digitalWrite(pinOff, HIGH);

  sounds->makeOffSound();
}

void Listener::handleDoorSensorTriggered()
{
  if (lastNow - lastDoorSensorTime <= secondValueDelay)
    return;

  lastDoorSensorTime = lastNow;

  if (allowToTriggerSensor() == false)
    return;

  triggerDoorSensor();
}

void Listener::triggerDoorSensor()
{
  alarm->trigger("door");
}

void Listener::handleMotionSensorTriggered()
{
  if (lastNow - lastMotionSensorTime <= secondValueDelay)
    return;

  lastMotionSensorTime = lastNow;

  if (allowToTriggerSensor() == false)
    return;

  triggerMotionSensor();
}

boolean Listener::allowToTriggerSensor()
{
  if (isListening == false)
  {
    logger->write("Not triggered because sensor listener is off.");
    return false;
  }

  unsigned long timeFromLastStart = lastNow - lastStartTime;
  if (timeFromLastStart <= startDelay)
  {
    logger->write("Not triggered because of start delay.");
    return false;
  }

  return true;
}

void Listener::triggerMotionSensor()
{
  alarm->trigger("motion");
}
