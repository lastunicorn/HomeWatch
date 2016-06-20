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

#include "Alarm.h"

Alarm::Alarm(Logger *logger, Sounds *sounds, SmsSender *smsSender)
{
  this->logger = logger;
  this->sounds = sounds;
  this->smsSender = smsSender;

  pinMode(pinOn, OUTPUT);
  pinMode(pinOff, OUTPUT);
  pinMode(pinAlarm, OUTPUT);

  digitalWrite(pinOn, LOW);
  digitalWrite(pinOff, HIGH);
  digitalWrite(pinAlarm, LOW);
}

void Alarm::init()
{
  smsSender->connect();
}

void Alarm::trigger(String sensorName)
{
  unsigned long now = millis();

  if (lastAlarmTime != 0 && now - lastAlarmTime <= repeatDelay)
  {
    logger->info("Alarm - Not triggered because of alarm repeat delay.");
    return;
  }

  lastAlarmTime = now;

  logger->info("Alarm - !!! alarm, alarm, alarm !!! - Alarm triggered by " + sensorName + " sensor.");

  // led on
  digitalWrite(pinAlarm, HIGH);

  sounds->makeAlarmSound();
  sensSms(sensorName);

  // led off
  digitalWrite(pinAlarm, LOW);
}

void Alarm::sensSms(String sensorName)
{
  String message = "alarm acasa - ";
  message += sensorName;

  char str[message.length() + 1];
  message.toCharArray(str, message.length() + 1);

  for(int i = 0; i < PHONE_COUNT; i++)
    smsSender->sendSMS(phones[i], str);
}
