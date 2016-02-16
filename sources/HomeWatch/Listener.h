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
    boolean on = false;
    RCSwitch mySwitch;
    Logger *logger;
    Sounds *sounds;
    Alarm *alarm;

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

  private:
    void logSensorValue();

    void handleOnButton1Pressed();
    void handleOnButton2Pressed();
    void handleOffButton1Pressed();
    void handleOffButton2Pressed();
    void handleDoorSensorTriggered();
    void handleMotionSensorTriggered();

    void turnOn();
    void turnOff();
};

#endif
