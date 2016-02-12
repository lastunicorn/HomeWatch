#include "Arduino.h"
#include "SmsSender.h"
#include "Logger.h"
#include "Sounds.h"

void makeFakeSound();
extern Logger logger;
extern Sounds sounds;

SmsSender::SmsSender(boolean isReal)
{
  this->isReal = isReal;
  
  pinMode(pinError, OUTPUT);
  pinMode(pinReady, OUTPUT);
}

void SmsSender::connect()
{
  if (isReal == false)
    sounds.makeFakeSound();

  while (!isConnected)
  {
    changeStateToConnecting();

    int gsmConnectCode = tryToConnectGsm();

    String s = "Connect code: ";
    s += gsmConnectCode;
    logger.write(s);

    if (gsmConnectCode == GSM_READY)
    {
      changeStateToConnected();
    }
    else
    {
      changeStateToNotConnected();
      delay(10000);
    }
  }

  logger.write("<--");
}

void SmsSender::changeStateToConnecting()
{
  logger.write("--> Connecting...");
  digitalWrite(pinError, LOW);
  digitalWrite(pinReady, LOW);
}

void SmsSender::changeStateToConnected()
{
  digitalWrite(pinReady, HIGH);
  logger.write("Connected");
  isConnected = true;
}

void SmsSender::changeStateToNotConnected()
{
  digitalWrite(pinError, HIGH);
  logger.write("Not connected");
}

int SmsSender::tryToConnectGsm()
{
  if (isReal == false)
    return GSM_READY;

  if (simPin == NULL || strlen(simPin) == 0)
  {
    logger.write("Try to connect without pin.");
    return gsmAccess.begin();
  }
  else
  {
    String s = "Try to connect using pin = ";
    s += simPin;
    logger.write(s);

    return gsmAccess.begin(simPin);
  }
}

void SmsSender::sendSMS(char remoteNumber[20], char txtMsg[200]) {

  String s = "Sending message to mobile number: ";
  s += remoteNumber;
  logger.write(s);

  if (isReal == false)
    return;

  // sms text
  logger.write("Message:");
  logger.write(txtMsg);

  // send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS();

  logger.write("SMS successfully sent");
}
