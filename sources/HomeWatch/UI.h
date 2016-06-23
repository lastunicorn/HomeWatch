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

#ifndef UI_h
#define UI_h

#include <Ethernet2.h>
#include "Logger.h"

class UI
{
  private:
    Logger *logger;
    EthernetServer server = EthernetServer(80);

  public:
    UI(Logger *logger);
    void initializeEthernet();
    void checkEthernetRequest();
};

#endif
