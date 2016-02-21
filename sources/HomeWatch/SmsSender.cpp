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
    logger->info("GSM - Fake: Starting the GSM module...");
    sounds->makeSmsSenderFakeSound();
  }

  while (!isConnected)
  {
    changeStateToConnecting();

    int gsmConnectCode = tryToConnectGsm();

    logger->append("GSM - Connect code: ");
    logger->append(gsmConnectCode);
    logger->trace();

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
    logger->trace("GSM - Try to connect without pin.");
    return gsmAccess.begin();
  }
  else
  {
    logger->append("GSM - Try to connect using pin = ");
    logger->append(simPin);
    logger->trace();

    return gsmAccess.begin(simPin);
  }
}

void SmsSender::sendSMS(char remoteNumber[20], char txtMsg[200])
{
  logger->append("GSM - Sending sms message to mobile number: ");
  logger->append(remoteNumber);
  logger->info();

  // sms text
  logger->append("GSM - Message:");
  logger->append(txtMsg);
  logger->trace();

  if (isReal)
  {
    // send the message
    sms.beginSMS(remoteNumber);
    sms.print(txtMsg);
    sms.endSMS();

    logger->info("GSM - SMS successfully sent");
  }
  else
  {
    logger->info("GSM - Fake: SMS successfully sent");
  }
}
