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
#include "LogReader.h"

#define LOG_DEBUG 0
#define LOG_TRACE 1
#define LOG_INFO 2
#define LOG_WARNING 3
#define LOG_ERROR 4

/**
   This class is logging both to Serial and to a SD card.
   It uses the SD.h library and expects the Serial to be already initialized.
*/
class Logger
{
  private:
    String buffer;
    bool sdCardAvailable = false;
    unsigned short logLevel = LOG_INFO;
    File logFile;

  public:
    Logger() : Logger(LOG_INFO) {};
    Logger(unsigned short logLevel);
    Logger* append(String text);
    Logger* append(unsigned long value);
    void debug();
    void trace();
    void info();
    void warning();
    void error();

    void debug(String message);
    void debug(unsigned long value);
    void trace(String message);
    void trace(unsigned long value);
    void info(String message);
    void info(unsigned long value);
    void warning(String message);
    void warning(unsigned long value);
    void error(String message);
    void error(unsigned long value);

    LogReader getLogReader();

  private:
    void initializeSdCard();
    void write(String message, unsigned short logLevel);
    String formatTime(unsigned long milliseconds);
    String formatLogLevel(unsigned short logLevel);
    void writeToSerial(String text);
    void writeToSdCard(String text);
};

#endif
