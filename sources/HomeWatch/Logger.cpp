/*
 * Home Watch
 * Copyright (C) 2016  Dust in the Wind
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Arduino.h"
#include "Logger.h"
#include <SD.h>

String formatTimeAsString(unsigned long milliseconds);

Logger::Logger()
{
  //initializeSdCard();
}

void Logger::add(String text)
{
  buffer += text;
}

void Logger::flush()
{
  write(buffer);
  buffer = String();
}

void Logger::write(String message)
{
  String timeFormated = formatTimeAsString(millis());

  String text = timeFormated + " - " + message;

  logToSerial(text);
  logToSdCard(text);

}

void Logger::write(unsigned long value)
{
  String str(value);
  write(str);
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

void Logger::logToSerial(String text)
{
  Serial.println(text);
}

void Logger::logToSdCard(String text)
{
  if (!sdCardAvailable)
    return;

  File myFile;

  // Open the file
  myFile = SD.open("Home.log", FILE_WRITE);

  if (myFile) {
    myFile.println(text);
    myFile.close();
  }
  else
  {
    Serial.println("Could not write in log file.");
  }
}
