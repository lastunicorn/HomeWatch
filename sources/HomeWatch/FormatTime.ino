/*
 * Home Watch
 * Copyright (C) 2016  Dust in the Wind
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

