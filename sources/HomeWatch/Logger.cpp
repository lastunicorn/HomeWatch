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

