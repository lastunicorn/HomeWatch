#include "Arduino.h"
#include "Logger.h"

String formatTimeAsString(unsigned long milliseconds);

void Logger::add(String text)
{
  buffer += text;
}

void Logger::flush()
{
  write(buffer);
  buffer = String();
}

void Logger::write(String text)
{
  String timeFormated = formatTimeAsString(millis());

  char str[timeFormated.length() + 1];
  timeFormated.toCharArray(str, timeFormated.length() + 1);

  Serial.print(str);
  Serial.print(" - ");
  Serial.println(text);

  if (!sdCardAvailable)
    return;

  File myFile;

  // Open the file
  myFile = SD.open("Home.log", FILE_WRITE);

  if (myFile) {

    myFile.print(str);
    myFile.print(" - ");
    myFile.println(text);

    // close the file:
    myFile.close();
  }
  else
  {
    Serial.println("Could not write in log file.");
  }
}
