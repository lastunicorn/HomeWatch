#ifndef SmsSender_h
#define SmsSender_h

#include <GSM.h>

class SmsSender
{
  public:
    int pinError = 5;
    int pinReady = 6;
    char* pin;

  private:
    boolean isConnected = false;
    GSM gsmAccess; // include a 'true' parameter for debug enabled
    GSM_SMS sms;

  public:
    SmsSender();
    void connect();
    void sendSMS(char remoteNumber[20], char txtMsg[200]);
};

#endif
