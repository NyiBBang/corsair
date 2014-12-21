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

#ifndef PLAYERSMANAGER_H
#define PLAYERSMANAGER_H

#include "Types.h"
#include "PlayersManager_Int.h"

namespace core
{
class PlayersManager : public PlayersManager_Int
{
public:
    PlayersManager( unsigned int gameScoreLimit );

    virtual void addPlayer( unsigned int identifier, const std::string& name );
    virtual void removePlayer( unsigned int identifier );
    virtual void switchToNextPlayer();
    virtual void addToCurrentPlayerScore( unsigned int score );
    virtual void accept( PlayersManagerDataReceiver_Int& receiver ) const;

private:
    unsigned int remainingPlayersCount() const;

private:
    unsigned int gameScoreLimit_;
    Players players_;
    Players::iterator currentPlayer_;
};
}

#endif // PLAYERSMANAGER_H
