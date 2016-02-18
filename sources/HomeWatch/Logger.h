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

#ifndef Logger_h
#define Logger_h

#include "Arduino.h"

/**
   This class is logging both to Serial and to a SD card.
   It uses the SD.h library and neede the Serial to be already started.
*/
class Logger
{
  private:
    String buffer;
    bool sdCardAvailable = false;

  public:
    Logger();
    void add(String text);
    void flush();
    void write(String message);
    void write(unsigned long value);

  private:
    void initializeSdCard();
    void logToSerial(String text);
    void logToSdCard(String text);
};

#endif
