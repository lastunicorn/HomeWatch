#include "Arduino.h"
#include "SmsSender.h"
#include "Logger.h"

extern Logger logger;

SmsSender::SmsSender()
{
  pinMode(pinError, OUTPUT);
  pinMode(pinReady, OUTPUT);
}

void SmsSender::connect()
{
  while (!isConnected)
  {
    logger.write("--> Connecting...");
    digitalWrite(pinError, LOW);
    digitalWrite(pinReady, LOW);

    int gsmConnectCode ;

    if (pin == NULL || strlen(pin) == 0)
    {
      logger.write("Try to connect without pin.");
      gsmConnectCode = gsmAccess.begin();
    }
    else
    {
      String s = "Try to connect using pin = ";
      s += pin;
      logger.write(s);

      gsmConnectCode = gsmAccess.begin(pin);
    }

    String s = "Connect code: ";
    s += gsmConnectCode;
    logger.write(s);

    if (gsmConnectCode == GSM_READY)
    {
      digitalWrite(pinReady, HIGH);
      logger.write("Connected");
      isConnected = true;
    }
    else
    {
      digitalWrite(pinError, HIGH);
      logger.write("Not connected");
      delay(10000);
    }
  }

  logger.write("<--");
}

void SmsSender::sendSMS(char remoteNumber[20], char txtMsg[200]) {

  Serial.print("Sending message to mobile number: ");
  Serial.println(remoteNumber);

  // sms text
  Serial.println("Message:");
  Serial.println(txtMsg);

  // send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS();

  Serial.println("SMS successfully sent");
}
