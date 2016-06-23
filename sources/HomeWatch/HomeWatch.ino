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

#include "Alarm.h"
#include "Logger.h"
#include "SmsSender.h"
#include "Sounds.h"
#include "Listener.h"
#include "CustomGsm.h"
#include "UI.h"

Logger logger = Logger(LOG_DEBUG);
Sounds sounds;
CustomGsm gsm = CustomGsm(&logger);
SmsSender smsSender = SmsSender(&logger, &sounds, &gsm, false);

Alarm alarm = Alarm(&logger, &sounds, &smsSender);
Listener listener = Listener(&logger, &sounds, &alarm);
UI ui = UI(&logger);

void setup()
{
  Serial.begin(9600);

  logger.info("=======================================================");
  logger.info("=== Home Watch - Powered by Arduino");
  logger.info("=== Copyright © 2016 Dust in the Wind");
  logger.info("=======================================================");

  alarm.init();
  ui.initializeEthernet();

  logger.info("Arduino started");
}

void loop()
{
  listener.refresh();
  ui.checkEthernetRequest();
  delay(100);
}

