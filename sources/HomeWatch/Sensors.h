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

#ifndef Sensors_h
#define Sensors_h

#include "Listener.h"
#include "Alarm.h"

/*
 * ===============================================================
 * Sensor
 * ===============================================================
 */

class Sensor
{
  protected:
    unsigned long id = 0;
    unsigned long lastTime = 0;
    unsigned long inhibitionTime = 2000;

  public:
    Sensor(int id);
    boolean handle(unsigned long value);

  protected:
    boolean beforeExecute();
    boolean execute();
};

/*
 * ===============================================================
 * Button On1
 * ===============================================================
 */

class ButtonOn1Sensor : public Sensor
{
  private:
    Listener *listener;

  public:
    ButtonOn1Sensor(Listener *listener);

  protected:
    boolean execute();
};

/*
 * ===============================================================
 * Button On2
 * ===============================================================
 */

class ButtonOn2Sensor : public Sensor
{
  private:
    Listener *listener;

  public:
    ButtonOn2Sensor(Listener *listener);

  protected:
    boolean execute();
};

/*
 * ===============================================================
 * Button Off1
 * ===============================================================
 */

class ButtonOff1Sensor : public Sensor
{
  private:
    Listener *listener;

  public:
    ButtonOff1Sensor(Listener *listener);

  protected:
    boolean execute();
};

/*
 * ===============================================================
 * Button Off2
 * ===============================================================
 */

class ButtonOff2Sensor : public Sensor
{
  private:
    Listener *listener;

  public:
    ButtonOff2Sensor(Listener *listener);

  protected:
    boolean execute();
};

/*
 * ===============================================================
 * Door Sensor
 * ===============================================================
 */

class DoorSensor : public Sensor
{
  private:
    Alarm *alarm;

  public:
    DoorSensor(Alarm *alarm);

  protected:
    boolean execute();
};

/*
 * ===============================================================
 * Motion Sensor
 * ===============================================================
 */

class MotionSensor : public Sensor
{
  private:
    Alarm *alarm;

  public:
    MotionSensor(Alarm *alarm);

  protected:
    boolean execute();
};

#endif
