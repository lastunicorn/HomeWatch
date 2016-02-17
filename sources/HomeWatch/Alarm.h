/*
 * Home Watch
 * Copyright (C) 2016  Dust in the Wind
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Alarm_h
#define Alarm_h

#include "Logger.h"
#include "Sounds.h"
#include "SmsSender.h"

/*
 * This class is implementing the logic run when the alarm is triggered.
 */
class Alarm
{
  private:
    Logger *logger;
    Sounds *sounds;
    SmsSender smsSender = SmsSender(true);

    unsigned long repeatInterval = 30000;
    unsigned long lastAlarmTime = 0;

  public:
    int pinOn = 12;
    int pinOff = 11;
    int pinAlarm = 8;

  public:
    Alarm(Logger *logger, Sounds *sounds);
    void init();
    void trigger(String sensorName);
};

#endif
