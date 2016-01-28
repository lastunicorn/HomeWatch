#include <SPI.h>
#include <SD.h>

String formatTimeAsString(unsigned long milliseconds);
char* formatTimeAsCharArray(unsigned long milliseconds);

void writeLog(String text)
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

void writeLog(unsigned long value)
{
  String str(value);
  writeLog(str);
}
