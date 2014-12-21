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

#include "GameStateChecker.h"
#include "PlayersManager.h"
#include <boost/foreach.hpp>

using namespace core;

GameStateChecker::GameStateChecker( const PlayersManager_Int& playersManager, const unsigned int gameScoreLimit )
    : playersManager_( playersManager )
    , gameScoreLimit_( gameScoreLimit )
{
}

bool GameStateChecker::isGameOver()
{
    players_.clear();
    playersManager_.accept( *this );
    unsigned int nbOfPlayersStillInGame = 0;
    BOOST_FOREACH( Players::value_type player , players_)
        if( player.second.score < gameScoreLimit_ )
            ++nbOfPlayersStillInGame;
    return nbOfPlayersStillInGame < 2;
}

void GameStateChecker::receivePlayer( unsigned int identifier, const std::string& name, unsigned int score )
{
    players_.insert( Players::value_type( identifier , Player( name, score ) ) );
}

void GameStateChecker::receiveCurrentPlayer( unsigned int /*identifier*/ )
{
}

void GameStateChecker::receiveWinner( unsigned int /*identifier*/ )
{
}
