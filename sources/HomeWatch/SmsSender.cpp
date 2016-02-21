/*
   Home Watch
   Copyright (C) 2016  Dust in the Wind

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    logger->info("GSM - Starting the GSM module...");
  }
  else
  {
    logger->info("GSM - Fakeing the GSM module...");
    sounds->makeFakeSound();
  }

  while (!isConnected)
  {
    changeStateToConnecting();

    int gsmConnectCode = tryToConnectGsm();

    String s = "GSM - Connect code: ";
    s += gsmConnectCode;
    logger->info(s);

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
  logger->info("GSM - Connecting...");
  digitalWrite(pinError, LOW);
  digitalWrite(pinReady, LOW);
}

void SmsSender::changeStateToConnected()
{
  digitalWrite(pinReady, HIGH);
  logger->info("GSM - Connected");
  isConnected = true;
}

void SmsSender::changeStateToNotConnected()
{
  digitalWrite(pinError, HIGH);
  logger->info("GSM - Not connected");
}

int SmsSender::tryToConnectGsm()
{
  if (isReal == false)
    return GSM_READY;

  if (simPin == NULL || strlen(simPin) == 0)
  {
    logger->info("GSM - Try to connect without pin.");
    return gsmAccess.begin();
  }
  else
  {
    logger->append("GSM - Try to connect using pin = ");
    logger->append(simPin);
    logger->info();

    return gsmAccess.begin(simPin);
  }
}

void SmsSender::sendSMS(char remoteNumber[20], char txtMsg[200])
{
  if (isReal == false)
  {
    logger->append("GSM - Fake send sms to number 1: ");
    logger->append(remoteNumber);
    logger->info();

    return;
  }

  logger->append("GSM - Sending message to mobile number: ");
  logger->append(remoteNumber);
  logger->info();

  // sms text
  logger->append("GSM - Message:");
  logger->append(txtMsg);
  logger->info();

  // send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS();

  logger->info("GSM - SMS successfully sent");
}
