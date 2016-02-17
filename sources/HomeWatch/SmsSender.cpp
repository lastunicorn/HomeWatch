/*
 * Home Watch
 * Copyright (C) 2016  Dust in the Wind
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

  digitalWrite(pinError, LOW);
  digitalWrite(pinReady, LOW);
}

void SmsSender::connect()
{
  if (isReal)
  {
    logger.write("GSM - Starting the GSM module...");
  }
  else
  {
    logger.write("GSM - Fakeing the GSM module...");
    sounds.makeFakeSound();
  }

  while (!isConnected)
  {
    changeStateToConnecting();

    int gsmConnectCode = tryToConnectGsm();

    String s = "GSM - Connect code: ";
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
}

void SmsSender::changeStateToConnecting()
{
  logger.write("GSM - Connecting...");
  digitalWrite(pinError, LOW);
  digitalWrite(pinReady, LOW);
}

void SmsSender::changeStateToConnected()
{
  digitalWrite(pinReady, HIGH);
  logger.write("GSM - Connected");
  isConnected = true;
}

void SmsSender::changeStateToNotConnected()
{
  digitalWrite(pinError, HIGH);
  logger.write("GSM - Not connected");
}

int SmsSender::tryToConnectGsm()
{
  if (isReal == false)
    return GSM_READY;

  if (simPin == NULL || strlen(simPin) == 0)
  {
    logger.write("GSM - Try to connect without pin.");
    return gsmAccess.begin();
  }
  else
  {
    String s = "GSM - Try to connect using pin = ";
    s += simPin;
    logger.write(s);

    return gsmAccess.begin(simPin);
  }
}

void SmsSender::sendSMS(char remoteNumber[20], char txtMsg[200])
{
  if (isReal == false)
  {
    String s = "GSM - Fake send sms to number: ";
    s += remoteNumber;
    logger.write(s);
    
    return;
  }

  String s = "GSM - Sending message to mobile number: ";
  s += remoteNumber;
  logger.write(s);

  // sms text
  logger.write("GSM - Message:");
  logger.write(txtMsg);

  // send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS();

  logger.write("GSM - SMS successfully sent");
}
