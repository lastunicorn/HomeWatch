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
#include "Logger.h"
#include "LogReader.h"
#include <SD.h>

String formatTimeAsString(unsigned long milliseconds);

Logger::Logger(unsigned short logLevel)
{
  this->logLevel = logLevel;
  initializeSdCard();
}

void Logger::initializeSdCard()
{
  Serial.println("Initializing SD card...");

  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    sdCardAvailable = false;
  }
  else
  {
    Serial.println("SD card successfully initialized.");
    sdCardAvailable = true;
  }
}

Logger* Logger::append(String text)
{
  buffer += text;
  return this;
}

Logger* Logger::append(unsigned long value)
{
  String message(value);
  buffer += message;
  return this;
}

void Logger::debug()
{
  write(buffer, LOG_DEBUG);
  buffer = String();
}

void Logger::trace()
{
  write(buffer, LOG_TRACE);
  buffer = String();
}

void Logger::info()
{
  write(buffer, LOG_INFO);
  buffer = String();
}

void Logger::warning()
{
  write(buffer, LOG_WARNING);
  buffer = String();
}

void Logger::error()
{
  write(buffer, LOG_ERROR);
  buffer = String();
}

void Logger::debug(String message)
{
  write(message, LOG_DEBUG);
}

void Logger::debug(unsigned long value)
{
  String message(value);
  write(message, LOG_DEBUG);
}

void Logger::trace(String message)
{
  write(message, LOG_TRACE);
}

void Logger::trace(unsigned long value)
{
  String message(value);
  write(message, LOG_TRACE);
}

void Logger::info(String message)
{
  write(message, LOG_INFO);
}

void Logger::info(unsigned long value)
{
  String message(value);
  write(message, LOG_INFO);
}

void Logger::warning(String message)
{
  write(message, LOG_WARNING);
}

void Logger::warning(unsigned long value)
{
  String message(value);
  write(message, LOG_WARNING);
}

void Logger::error(String message)
{
  write(message, LOG_ERROR);
}

void Logger::error(unsigned long value)
{
  String message(value);
  write(message, LOG_ERROR);
}

void Logger::write(String message, unsigned short logLevel)
{
  if (logLevel < this->logLevel)
    return;

  String timeStampAsString = formatTime(millis());
  String logLevelAsString = formatLogLevel(logLevel);
  String text = timeStampAsString + " [" + logLevelAsString + "]" + " - " + message;

  writeToSerial(text);
  writeToSdCard(text);
}

void Logger::writeToSerial(String text)
{
  Serial.println(text);
}

void Logger::writeToSdCard(String text)
{
  if (!sdCardAvailable)
    return;

  File myFile;

  // Open the file
  myFile = SD.open("Home.log", FILE_WRITE);

  if (myFile)
  {
    myFile.println(text);
    myFile.close();
  }
  else
  {
    Serial.println("Could not write in log file.");
  }
}

String Logger::formatTime(unsigned long milliseconds)
{
  unsigned long value = milliseconds;

  unsigned long hours = value / 3600000;
  value = value % 3600000;

  unsigned long minutes = value / 60000;
  value = value % 60000;

  unsigned long seconds = value / 1000;
  value = value % 1000;

  String s;

  if (hours < 10)
    s += "0";
  s += hours;
  s += ":";

  if (minutes < 10)
    s += "0";
  s += minutes;
  s += ":";

  if (seconds < 10)
    s += "0";
  s += seconds;
  s += ".";

  if (value < 10)
    s += "00";
  else if (value < 100)
    s += "0";
  s += value;

  s += " (";
  s += milliseconds;
  s += ")";

  return s;
}

//// Is not working corectly, but I don't know why.
//char* formatTimeAsCharArray(unsigned long milliseconds)
//{
//  String timeFormated;
//  timeFormated += formatTimeAsString(milliseconds);
//
//  char str[timeFormated.length() + 1];
//  timeFormated.toCharArray(str, timeFormated.length() + 1);
//
//  return str;
//}

String Logger::formatLogLevel(unsigned short logLevel)
{
  switch (logLevel)
  {
    case LOG_DEBUG:
      return "DBG";
    case LOG_TRACE:
      return "TRC";
    case LOG_INFO:
      return "INF";
    case LOG_WARNING:
      return "WRN";
    case LOG_ERROR:
      return "ERR";
    default:
      return String(logLevel);
  }
}

LogReader Logger::getLogReader()
{
  // Open the file
  logFile = SD.open("Home.log");

  if (logFile)
  {
    return LogReader(&logFile);
  }
  else
  {
    Serial.println("Could not write in log file.");
    return NULL;
  }
}

