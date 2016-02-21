/*
   Home Watch
   Copyright (C) 2016  Dust in the Wind

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

void Sounds::makeListenerStartingSound()
{
  tone(piezoPin, 200, 150);
  delay(150);
  tone(piezoPin, 150, 100);
  delay(500);
}

void Sounds::makeSmsSenderFakeSound()
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
