#ifndef SmsSender_h
#define SmsSender_h

#include <GSM.h>
#include "Logger.h";
#include "Sounds.h";

class SmsSender
{
  public:
    int pinError = 5;
    int pinReady = 6;
    char* simPin;

  private:
    Logger *logger;
    Sounds *sounds;
    boolean isReal = false;
    boolean isConnected = false;
    GSM gsmAccess = GSM(true); // include a 'true' parameter for debug enabled
    GSM_SMS sms;

  public:
    SmsSender(Logger *logger, Sounds *sounds, boolean isReal);
    SmsSender(Logger *logger, Sounds *sounds) : SmsSender(logger, sounds, true) {};
    void connect();
    void sendSMS(char remoteNumber[20], char txtMsg[200]);

  private:
    void changeStateToConnecting();
    void changeStateToConnected();
    void changeStateToNotConnected();
    int tryToConnectGsm();
};

#endif
