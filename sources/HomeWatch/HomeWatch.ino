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

#include <GSM.h>
#include "Alarm.h"
#include "Logger.h"
#include "SmsSender.h"
#include "Sounds.h"
#include "Listener.h"

Logger logger = Logger(LOG_INFO);
Sounds sounds;
SmsSender smsSender = SmsSender(&logger, &sounds, false);

Alarm alarm = Alarm(&logger, &sounds, &smsSender);
Listener listener = Listener(&logger, &sounds, &alarm);

void setup() {
  Serial.begin(9600);

  logger.info("=======================================================");
  logger.info("=== Home Watch - Powered by Arduino");
  logger.info("=== Copyright © 2016 Dust in the Wind");
  logger.info("=======================================================");

  alarm.init();

  logger.info("Arduino started");
}

void loop() {
  listener.refresh();
  delay(100);
}

