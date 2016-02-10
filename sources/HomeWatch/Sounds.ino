void makeAlarmSound()
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

void makeStartingSound()
{
  tone(piezoPin, 150, 100);
  delay(100);
  tone(piezoPin, 150, 100);
  delay(500);
}

void makeFakeSound()
{
  tone(piezoPin, 50, 1000);
  delay(1000);
}
