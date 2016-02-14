#ifndef Sounds_h
#define Sounds_h

struct MusicalNote
{
  unsigned int frequency;
  unsigned long duration;
};

class Sounds
{
  public:
    int piezoPin = 9;

  public:
    Sounds();
    void makeAlarmSound();
    void makeStartingSound();
    void makeFakeSound();
    void makeOffSound();
};

#endif
