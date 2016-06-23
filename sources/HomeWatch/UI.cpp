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

#include <Ethernet2.h>
#include <SD.h>
#include "UI.h"
#include "LogReader.h"

UI::UI(Logger *logger)
{
  this->logger = logger;
}

void UI::initializeEthernet()
{
  byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x50, 0x5E };
  IPAddress ip(192, 168, 0, 77);

  Ethernet.begin(mac, ip);
  server.begin();

  Serial.print("Web server is listening at ");
  Serial.println(Ethernet.localIP());
}

void UI::checkEthernetRequest()
{
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client)
  {
    Serial.println("new client");

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();

          client.println("<!DOCTYPE HTML>");
          client.println("<html><head><title></title></head><body><pre>");

          LogReader logReader = logger->getLogReader();
          byte buffer[1024];

          while (true)
          {
            int i;

            for (i = 0; i < 1024; i++)
            {
              if (logReader.available())
                buffer[i] = logReader.read();
              else
                break;
            }

            if (i == 0)
              break;

            client.write(buffer, i);
          }

          logReader.close();

          client.println("</pre></body></html>");
          break;
        }

        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
