boolean isAlarmTriggered()
{
  sensorValue = analogRead(sensorPin);

  if (sensorValue < 100)
  {
    unsigned long now = millis();
    elapsedTime = now - lastAlarmTime;

    String s;

    s += "sensor triggered: ";
    s += sensorValue;
    s += " - time from last alarm: ";
    s += formatTimeAsString(elapsedTime);

    loggerWrite(s);

    if (now > alarmDelay)
    {
      if (elapsedTime > alarmInterval)
      {
        loggerWrite("!!! alarm, alarm, alarm !!!");
        loggerWrite(1);
        lastAlarmTime = now;

        return true;
      }
    }
  }

  return false;
}
