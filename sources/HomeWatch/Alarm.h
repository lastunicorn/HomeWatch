#ifndef Alarm_h
#define Alarm_h

#include <RCSwitch.h>

class Alarm
{
  public:
    boolean on = false;
    int sensorPin = A0;
    unsigned long alarmRepeatInterval = 30000;
    unsigned long startDelay = 60000;
    unsigned long sensorValue;
    RCSwitch mySwitch;
    boolean isTriggered = false;
    boolean isDoorTriggered = false;
    boolean isMotionTriggered = false;

  private:
    unsigned long startTime = 0;
    unsigned long lastAlarmTime = 0;
    unsigned long lastNow = 0;

    unsigned long doorSensorId = ***REMOVED***;
    unsigned long motionSensorId = ***REMOVED***;
    unsigned long onId1 = ***REMOVED***;
    unsigned long offId1 = ***REMOVED***;
    unsigned long onId2 = ***REMOVED***;
    unsigned long offId2 = ***REMOVED***;

  public:
    Alarm();
    void refresh();

  private:
    void resetTriggerFlags();
    void triggerAlarm();
};

#endif
