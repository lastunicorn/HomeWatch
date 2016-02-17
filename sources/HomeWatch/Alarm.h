#ifndef Alarm_h
#define Alarm_h

#include "Logger.h"
#include "Sounds.h"
#include "SmsSender.h"

/*
 * This class is implementing the logic to be executed when the alarm is triggered.
 */
class Alarm
{
  public:
    int pinOn = 12;
    int pinOff = 11;
    int pinAlarm = 8;

  private:
    Logger *logger;
    Sounds *sounds;
    SmsSender *smsSender;

    unsigned long repeatDelay = 30000;
    unsigned long lastAlarmTime = 0;

  public:
    Alarm(Logger *logger, Sounds *sounds, SmsSender *smsSender);
    void init();
    void trigger(String sensorName);
};

#endif
