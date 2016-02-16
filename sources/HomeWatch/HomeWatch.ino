#include <GSM.h>
#include "Alarm.h"
#include "Logger.h"
#include "Sounds.h"
#include "Listener.h"

Logger logger;
Sounds sounds;

Alarm alarm = Alarm(&logger, &sounds);
Listener listener = Listener(&logger, &sounds, &alarm);

void setup() {
  Serial.begin(9600);

  logger.write("=======================================================");
  logger.write("=== Home Watch - Powered by Arduino");
  logger.write("=== Copyright © 2016 Dust in the Wind");
  logger.write("=======================================================");

  alarm.init();

  logger.write("Arduino started");
}

void loop() {
  listener.refresh();
  delay(100);
}
