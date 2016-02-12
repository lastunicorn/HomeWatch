#include "Arduino.h"
#include "Sounds.h"

Sounds::Sounds()
{
  pinMode(alarmPiezoPin, OUTPUT);
}

void Sounds::makeAlarmSound()
{
  tone(alarmPiezoPin, 200, 500);
  delay(500);
  tone(alarmPiezoPin, 100, 500);
  delay(500);
  tone(alarmPiezoPin, 200, 500);
  delay(500);
  tone(alarmPiezoPin, 100, 500);
  delay(500);
}

void Sounds::makeStartingSound()
{
  tone(alarmPiezoPin, 200, 150);
  delay(150);
  tone(alarmPiezoPin, 150, 100);
  delay(500);
}

void Sounds::makeFakeSound()
{
  tone(alarmPiezoPin, 50, 1000);
  delay(1000);
}
