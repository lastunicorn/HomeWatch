#ifndef Alarm_h
#define Alarm_h

#include <RCSwitch.h>

class Alarm
{
  public:
    unsigned long repeatInterval = 30000;
    unsigned long startDelay = 60000;

    int pinOn = 12;
    int pinOff = 11;
    
    boolean isTriggered = false;
    boolean isDoorTriggered = false;
    boolean isMotionTriggered = false;

  private:
    boolean on = false;
    RCSwitch mySwitch;    
    
    unsigned long lastNow = 0;
    unsigned long lastStartTime = 0;
    unsigned long lastStopTime = 0;
    unsigned long lastAlarmTime = 0;
    unsigned long lastDoorSensorTime = 0;
    unsigned long lastMotionSensorTime = 0;

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
    
    boolean isDoorSensor();
    void handleDoorSensorTriggered();
    
    boolean isMotionSensor();
    void handleMotionSensorTriggered();
};

#endif
