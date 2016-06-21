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
#include "CustomGsm.h"

CustomGsm::CustomGsm(Logger *logger)
{
  this->logger = logger;
  Serial3.begin(9600);
}

int CustomGsm::connect()
{
  ping();

  if (atResponse.indexOf("OK") < 0)
    return ERROR;

  setSmsModeText();

  if (atResponse.indexOf("OK") < 0)
    return ERROR;

  return GSM_READY;
}

int CustomGsm::connect(String simPin)
{
  return ERROR;
}

void CustomGsm::sendSms(char remoteNumber[20], char txtMsg[200])
{
  logger->debug("Sending: AT+CMGS=\"" + String(remoteNumber) + "\"");
  transmit("AT+CMGS=\"" + String(remoteNumber) + "\"");

  receive();
  logger->debug("Received: " + atResponse);

  logger->debug("Sending: " + String(txtMsg));
  transmit(txtMsg);

  logger->debug("Sending: Ctrl+Z (0x1A)");
  Serial3.write(26); // 0x1A - Ctrl+Z

  while (true)
  {
    delay(1000);
    receive();
    logger->debug("Received: " + atResponse);

    if (atResponse.indexOf("+CMGS") >= 0)
    {
      // Success
      logger->debug("Success");
      break;
    }
    else if (atResponse.indexOf("ERROR") >= 0)
    {
      // Error
      logger->debug("Error");
      break;
    }
    else
    {
      logger->debug("Waiting...");
    }
  }
}

void CustomGsm::ping()
{
  request("AT");
}

void CustomGsm::setSmsModeText()
{
  request("AT+CMGF=1");
}

void CustomGsm::request(char command[])
{
  logger->debug("Sending: " + String(command));
  transmit(command);

  receive();
  logger->debug("Received: " + atResponse);
}

void CustomGsm::transmit(String command) {
  Serial3.println(command);
  delay(1000);
}

void CustomGsm::receive() {
  atResponse = "";

  while (Serial3.available())
    atResponse += (char)Serial3.read();
}
