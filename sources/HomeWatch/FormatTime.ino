String formatTimeAsString(unsigned long milliseconds)
{
  unsigned long value = milliseconds;

  unsigned long hours = value / 3600000;
  value = value % 3600000;

  unsigned long minutes = value / 60000;
  value = value % 60000;

  unsigned long seconds = value / 1000;
  value = value % 1000;

  String s;

  if (hours < 10)
    s += "0";
  s += hours;
  s += ":";

  if (minutes < 10)
    s += "0";
  s += minutes;
  s += ":";

  if (seconds < 10)
    s += "0";
  s += seconds;
  s += ".";

  if (value < 10)
    s += "00";
  else if (value < 100)
    s += "0";
  s += value;

  s += " (";  
  s += milliseconds;
  s += ")";

  return s;
}

// Is not working corectly, but I don't know why.
char* formatTimeAsCharArray(unsigned long milliseconds)
{  
  String timeFormated;
  timeFormated += formatTimeAsString(milliseconds);

  char str[timeFormated.length() + 1];
  timeFormated.toCharArray(str, timeFormated.length() + 1);

  return str;
}

