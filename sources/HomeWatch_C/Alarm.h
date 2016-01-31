#ifndef Alarm_h
#define Alarm_h

class Alarm
{
  public:
    int sensorPin = A0;
    unsigned long alarmInterval = 30000;
    unsigned long alarmDelay = 60000;
    int sensorValue;

  private:
    unsigned long lastAlarmTime = 0;
    unsigned long elapsedTime = 0;

  public:
    Alarm();
    boolean isTriggered();
};

#endif
