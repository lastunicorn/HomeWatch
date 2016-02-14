#ifndef Alarm_h
#define Alarm_h

#include <RCSwitch.h>

class Alarm
{
  public:
    boolean on = false;
    unsigned long repeatInterval = 30000;
    unsigned long startDelay = 60000;
    RCSwitch mySwitch;
    boolean isTriggered = false;
    boolean isDoorTriggered = false;
    boolean isMotionTriggered = false;

  private:
    unsigned long lastNow = 0;
    unsigned long lastStartTime = 0;
    unsigned long lastStopTime = 0;
    unsigned long lastAlarmTime = 0;

    unsigned long doorSensorId = ***REMOVED***;
    unsigned long motionSensorId = ***REMOVED***;
    unsigned long onId1 = ***REMOVED***;
    unsigned long offId1 = ***REMOVED***;
    unsigned long onId2 = ***REMOVED***;
    unsigned long offId2 = ***REMOVED***;
    
    unsigned long sensorValue;

  public:
    Alarm();
    void refresh();

  private:
    void resetTriggerFlags();
    void logSensorValue();
    
    boolean isOnButtonPressed();
    void handleOnButtonPressed();
    
    boolean isOffButtonPressed();
    void handleOffButtonPressed();
    
    boolean isKnownSensor();
    void handleSensorTriggered();
};

#endif
