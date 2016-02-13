#ifndef Sounds_h
#define Sounds_h

class Sounds
{
  public:
    int alarmPiezoPin = 9;

  public:
    Sounds();
    void makeAlarmSound();
    void makeStartingSound();
    void makeFakeSound();
    void makeOffSound();
};

#endif
