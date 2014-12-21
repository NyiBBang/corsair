/**********************************************************************************
 * Copyright (C) 2011 NYI.BBang (Vincent PALANCHER)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *********************************************************************************/

#ifndef PLAYERSMANAGER_INT_H
#define PLAYERSMANAGER_INT_H

#include <string>

namespace core
{
    class PlayersManagerDataReceiver_Int;

class PlayersManager_Int
{
public:
    PlayersManager_Int() {}
    virtual ~PlayersManager_Int() {}

    virtual void addPlayer( unsigned int identifier, const std::string& name ) = 0;
    virtual void removePlayer( unsigned int identifier ) = 0;
    virtual void switchToNextPlayer() = 0;
    virtual void addToCurrentPlayerScore( unsigned int score ) = 0;
    virtual void accept( PlayersManagerDataReceiver_Int& receiver ) const = 0;
};
}

#endif // PLAYERSMANAGER_INT_H
