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

#ifndef SmsSender_h
#define SmsSender_h

//#include <GSM.h>
#include "Logger.h";
#include "Sounds.h";
#include "CustomGsm.h";

class SmsSender
{
  public:
    int pinReady = 22;
    int pinError = 23;
    char* simPin;

  private:
    Logger *logger;
    Sounds *sounds;
    boolean isReal = false;
    boolean isConnected = false;
    //GSM gsmAccess = GSM(true); // include a 'true' parameter for debug enabled
    //GSM_SMS sms;
    CustomGsm *gsm;

  public:
    SmsSender(Logger *logger, Sounds *sounds, CustomGsm *gsm, boolean isReal);
    SmsSender(Logger *logger, Sounds *sounds, CustomGsm *gsm) : SmsSender(logger, sounds, gsm, true) {};
    void connect();
    void sendSMS(char remoteNumber[20], char txtMsg[200]);

  private:
    void changeStateToConnecting();
    void changeStateToConnected();
    void changeStateToNotConnected();
    int tryToConnectGsm();
};

#endif
