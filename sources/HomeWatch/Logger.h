#ifndef Logger_h
#define Logger_h

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
