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
    void write(String text);
    void write(unsigned long value);
};

#endif
