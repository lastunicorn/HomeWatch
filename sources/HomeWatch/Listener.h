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

#ifndef Listener_h
#define Listener_h

#include <RCSwitch.h>
#include "Alarm.h"

class Listener
{
  public:
    unsigned long startDelay = 10000;

    int pinOn = 12;
    int pinOff = 11;

  private:
    Logger *logger;
    Sounds *sounds;
    Alarm *alarm;

    boolean isListening = false;
    int secondValueDelay = 4000;
    RCSwitch mySwitch;

    unsigned long lastNow = 0;
    unsigned long lastStartTime = 0;

    unsigned long lastOnButton1Time = 0;
    unsigned long lastOnButton2Time = 0;
    unsigned long lastOffButton1Time = 0;
    unsigned long lastOffButton2Time = 0;
    unsigned long lastDoorSensorTime = 0;
    unsigned long lastMotionSensorTime = 0;

    unsigned long onId1 = ***REMOVED***;
    unsigned long offId1 = ***REMOVED***;
    unsigned long onId2 = ***REMOVED***;
    unsigned long offId2 = ***REMOVED***;
    unsigned long doorSensorId = ***REMOVED***;
    unsigned long motionSensorId = ***REMOVED***;

    unsigned long sensorValue;

  public:
    Listener(Logger *logger, Sounds *sounds, Alarm *alarm);
    void refresh();
    void turnOn();
    void turnOff();

  private:
    void logSensorValue();

    void handleOnButton1Pressed();
    void handleOnButton2Pressed();
    void handleOffButton1Pressed();
    void handleOffButton2Pressed();
    void handleDoorSensorTriggered();
    void handleMotionSensorTriggered();

    boolean allowToTriggerSensor();

    void triggerDoorSensor();
    void triggerMotionSensor();
};

#endif
