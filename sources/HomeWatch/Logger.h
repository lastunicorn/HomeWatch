#ifndef Logger_h
#define Logger_h

class Logger
{
  private:
    String buffer;

  public:
    void add(String text);
    void flush();
    void write(String text);
};

#endif
