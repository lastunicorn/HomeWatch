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

#ifndef CustomGsm_h
#define CustomGsm_h

#include "Arduino.h"
#include "Logger.h";

#define ERROR 0
#define IDLE 1
#define CONNECTING 2
#define GSM_READY 3
#define GPRS_READY 4
#define TRANSPARENT_CONNECTED 5

class CustomGsm
{
  private:
    String atResponse;
    Logger *logger;

  public:
    CustomGsm(Logger *logger);
    int connect();
    int connect(String simPin);
    void sendSms(char remoteNumber[20], char txtMsg[200]);

  private:
    void request(char command[]);
    void transmit(String command);
    void receive();
    void ping();
    void setSmsModeText();
};

#endif
