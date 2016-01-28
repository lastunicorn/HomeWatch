#include "Arduino.h"
#include "SmsSender.h"

void writeLog(String text);

SmsSender::SmsSender()
{
  pinMode(pinError, OUTPUT);
  pinMode(pinReady, OUTPUT);
}

void SmsSender::connect()
{
  while (!isConnected)
  {
    writeLog("--> Connecting...");
    digitalWrite(pinError, LOW);
    digitalWrite(pinReady, LOW);

    int gsmConnectCode ;

    if (pin == NULL || pin == "")
    {
      writeLog("Try to connect without pin.");
      gsmConnectCode = gsmAccess.begin();
    }
    else
    {
      String s = "Try to connect using pin = ";
      s += pin;
      writeLog(s);

      gsmConnectCode = gsmAccess.begin(pin);
    }

    String s = "Connect code: ";
    s += gsmConnectCode;
    writeLog(s);

    if (gsmConnectCode == GSM_READY)
    {
      digitalWrite(pinReady, HIGH);
      writeLog("Connected");
      isConnected = true;
    }
    else
    {
      digitalWrite(pinError, HIGH);
      writeLog("Not connected");
      delay(10000);
    }
  }

  writeLog("<--");
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
