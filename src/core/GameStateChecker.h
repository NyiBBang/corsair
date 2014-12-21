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

#ifndef GAMESTATECHECKER_H
#define GAMESTATECHECKER_H

#include "GameStateChecker_Int.h"
#include "PlayersManagerDataReceiver_Int.h"
#include "Types.h"
#include <map>

namespace core
{
    class PlayersManager_Int;

class GameStateChecker : public GameStateChecker_Int
                       , public PlayersManagerDataReceiver_Int
{
public:
    GameStateChecker( const PlayersManager_Int& playersManager, const unsigned int gameScoreLimit );

    virtual bool isGameOver();
    virtual void receivePlayer( unsigned int identifier, const std::string& name, unsigned int score );
    virtual void receiveCurrentPlayer( unsigned int identifier );
    virtual void receiveWinner( unsigned int identifier );

private:
    typedef std::map< unsigned int, unsigned int > T_PlayersScores;

private:
    const PlayersManager_Int& playersManager_;
    const unsigned int gameScoreLimit_;
    Players players_;
};
}

#endif // GAMESTATECHECKER_H
