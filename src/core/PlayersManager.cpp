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

#include "PlayersManager.h"
#include "PlayersManagerDataReceiver_Int.h"
#include <boost/foreach.hpp>

using namespace core;

PlayersManager::PlayersManager( unsigned int gameScoreLimit )
    : gameScoreLimit_( gameScoreLimit )
    , currentPlayer_( players_.end() )
{
}

void PlayersManager::addPlayer( unsigned int identifier, const std::string& name )
{
    if( players_.find( identifier ) != players_.end() )
        return;
    players_.insert( Players::value_type( identifier, Player( name, 0 ) ) );
}

void PlayersManager::removePlayer( unsigned int identifier )
{
    Players::iterator it = players_.find( identifier );
    if( it != players_.end() && it == currentPlayer_ )
        switchToNextPlayer();
    players_.erase( identifier );
}

void PlayersManager::switchToNextPlayer()
{
    const unsigned int remainingCount = remainingPlayersCount();
    if( remainingCount == 0 )
    {
        currentPlayer_ = players_.end();
        return;
    }
    do
    {
        if( currentPlayer_ == players_.end() )
            currentPlayer_ = players_.begin();
        else
        {
            ++currentPlayer_;
            if( currentPlayer_ == players_.end() )
                currentPlayer_ = players_.begin();
        }
    } while( currentPlayer_->second.score >= gameScoreLimit_ );
}

void PlayersManager::addToCurrentPlayerScore( unsigned int score )
{
    if( currentPlayer_ == players_.end() )
        return;
    currentPlayer_->second.score += score;
}

void PlayersManager::accept( PlayersManagerDataReceiver_Int& receiver ) const
{
    BOOST_FOREACH( const Players::value_type& player, players_ )
        receiver.receivePlayer( player.first, player.second.name, player.second.score );
    if( currentPlayer_ != players_.end() )
        receiver.receiveCurrentPlayer( currentPlayer_->first );
    else
        receiver.receiveCurrentPlayer( CORE_UNKNOWN_PLAYER );
    if( remainingPlayersCount() == 1u )
    {
        Players::const_iterator player = players_.begin();
        while( player->second.score >= gameScoreLimit_ )
            ++player;
        receiver.receiveWinner( player->first );
    }
}

unsigned int PlayersManager::remainingPlayersCount() const
{
    unsigned int count = 0;
    BOOST_FOREACH( const Players::value_type& player, players_ )
        if( player.second.score < gameScoreLimit_ )
            ++count;
    return count;
}
