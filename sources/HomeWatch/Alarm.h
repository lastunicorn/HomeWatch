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
