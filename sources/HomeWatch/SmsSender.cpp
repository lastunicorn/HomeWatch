#include "Arduino.h"
#include "SmsSender.h"
#include "Logger.h"
#include "Sounds.h"

SmsSender::SmsSender(Logger *logger, Sounds *sounds, boolean isReal)
{
  this->logger = logger;
  this->sounds = sounds;
  this->isReal = isReal;

  pinMode(pinError, OUTPUT);
  pinMode(pinReady, OUTPUT);

  digitalWrite(pinError, LOW);
  digitalWrite(pinReady, LOW);
}

void SmsSender::connect()
{
  if (isReal)
  {
    logger->write("GSM - Starting the GSM module...");
  }
  else
  {
    logger->write("GSM - Fakeing the GSM module...");
    sounds->makeFakeSound();
  }

  while (!isConnected)
  {
    changeStateToConnecting();

    int gsmConnectCode = tryToConnectGsm();

    String s = "GSM - Connect code: ";
    s += gsmConnectCode;
    logger->write(s);

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
}

void SmsSender::changeStateToConnecting()
{
  logger->write("GSM - Connecting...");
  digitalWrite(pinError, LOW);
  digitalWrite(pinReady, LOW);
}

void SmsSender::changeStateToConnected()
{
  digitalWrite(pinReady, HIGH);
  logger->write("GSM - Connected");
  isConnected = true;
}

void SmsSender::changeStateToNotConnected()
{
  digitalWrite(pinError, HIGH);
  logger->write("GSM - Not connected");
}

int SmsSender::tryToConnectGsm()
{
  if (isReal == false)
    return GSM_READY;

  if (simPin == NULL || strlen(simPin) == 0)
  {
    logger->write("GSM - Try to connect without pin.");
    return gsmAccess.begin();
  }
  else
  {
    String s = "GSM - Try to connect using pin = ";
    s += simPin;
    logger->write(s);

    return gsmAccess.begin(simPin);
  }
}

void SmsSender::sendSMS(char remoteNumber[20], char txtMsg[200])
{
  if (isReal == false)
  {
    String s = "GSM - Fake send sms to number: ";
    s += remoteNumber;
    logger->write(s);
    
    return;
  }

  String s = "GSM - Sending message to mobile number: ";
  s += remoteNumber;
  logger->write(s);

  // sms text
  logger->write("GSM - Message:");
  logger->write(txtMsg);

  // send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS();

  logger->write("GSM - SMS successfully sent");
}
