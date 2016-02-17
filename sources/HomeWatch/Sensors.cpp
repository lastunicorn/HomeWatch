/**
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

#include "Arduino.h"
#include "Sensors.h"

/*
 * ===============================================================
 * Sensor
 * ===============================================================
 */

boolean Sensor::handle(unsigned long value)
{
  if (value != id)
    return false;

  unsigned long now = millis();

  if (now - lastTime <= inhibitionTime)
    return true;

  lastTime = now;
  return execute();
}

boolean Sensor::beforeExecute()
{
  return true;
}

/*
 * ===============================================================
 * Button On1
 * ===============================================================
 */

ButtonOn1Sensor::ButtonOn1Sensor(Listener *listener)
  : Sensor(***REMOVED***)
{
  this->listener = listener;
}

boolean ButtonOn1Sensor::execute()
{
  listener->turnOn();
}

/*
 * ===============================================================
 * Button On2
 * ===============================================================
 */

ButtonOn2Sensor::ButtonOn2Sensor(Listener *listener)
  : Sensor(***REMOVED***)
{
  this->listener = listener;
}

boolean ButtonOn2Sensor::execute()
{
  listener->turnOn();
}

/*
 * ===============================================================
 * Button Off1
 * ===============================================================
 */

ButtonOff1Sensor::ButtonOff1Sensor(Listener *listener)
  : Sensor(***REMOVED***)
{
  this->listener = listener;
}

boolean ButtonOff1Sensor::execute()
{
  listener->turnOff();
}

/*
 * ===============================================================
 * Button Off2
 * ===============================================================
 */

ButtonOff2Sensor::ButtonOff2Sensor(Listener *listener)
  : Sensor(***REMOVED***)
{
  this->listener = listener;
}

boolean ButtonOff2Sensor::execute()
{
  listener->turnOff();
}

/*
 * ===============================================================
 * Door Sensor
 * ===============================================================
 */

DoorSensor::DoorSensor(Alarm *alarm)
  : Sensor(***REMOVED***)
{
  this->alarm = alarm;
}

boolean DoorSensor::execute()
{
  alarm->trigger("door");
}

/*
 * ===============================================================
 * Motion Sensor
 * ===============================================================
 */

MotionSensor::MotionSensor(Alarm *alarm)
  : Sensor(***REMOVED***)
{
  this->alarm = alarm;
}

boolean MotionSensor::execute()
{
  alarm->trigger("motion");
}

