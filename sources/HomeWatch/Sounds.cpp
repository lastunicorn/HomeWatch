#include "Arduino.h"
#include "Sounds.h"

Sounds::Sounds()
{
  pinMode(piezoPin, OUTPUT);
}

void Sounds::makeAlarmSound()
{
  tone(piezoPin, 200, 500);
  delay(500);
  tone(piezoPin, 100, 500);
  delay(500);
  tone(piezoPin, 200, 500);
  delay(500);
  tone(piezoPin, 100, 500);
  delay(500);
}

void Sounds::makeStartingSound()
{
  tone(piezoPin, 200, 150);
  delay(150);
  tone(piezoPin, 150, 100);
  delay(500);
}

void Sounds::makeFakeSound()
{
  tone(piezoPin, 50, 1000);
  delay(1000);
}

void Sounds::makeOffSound()
{
  tone(piezoPin, 300, 100);
  delay(100);
  tone(piezoPin, 100, 200);
  delay(200);
}
