#ifndef Logger_h
#define Logger_h

#include "Arduino.h"

/**
 * This class is logging both to Serial and to a SD card.
 * It uses the SD.h library and neede the Serial to be already started.
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
