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

#include "config.h"
#include "core/PlayersManager.h"
#include "core/PlayersManagerDataReceiver_Int.h"
#include <boost/foreach.hpp>
#include <boost/assign/list_of.hpp>

namespace
{
    class Visitor : public core::PlayersManagerDataReceiver_Int
    {
    public:
        Visitor( const core::PlayersManager& manager )
            : manager_( manager )
            , currentPlayer_( CORE_UNKNOWN_PLAYER )
            , winner_( CORE_UNKNOWN_PLAYER )
        {}
        virtual void receivePlayer( unsigned int identifier, const std::string& name, unsigned int score )
        {
            players_.insert( core::Players::value_type( identifier, core::Player( name, score ) ) );
        }
        virtual void receiveCurrentPlayer( unsigned int identifier )
        {
            currentPlayer_ = identifier;
        }
        virtual void receiveWinner( unsigned int identifier )
        {
            winner_ = identifier;
        }
        void checkPlayers( const core::Players& expected )
        {
            players_.clear();
            manager_.accept( *this );
            BOOST_CHECK_EQUAL( expected.size(), players_.size() );
            BOOST_FOREACH( core::Players::value_type expectedPlayer, expected )
            {
                core::Players::iterator playerFound = players_.find( expectedPlayer.first );
                BOOST_CHECK( playerFound != players_.end() );
                BOOST_CHECK_EQUAL( playerFound->second.name , expectedPlayer.second.name );
                BOOST_CHECK_EQUAL( playerFound->second.score , expectedPlayer.second.score );
            }
        }
        void checkCurrentPlayer( unsigned int identifier )
        {
            manager_.accept( *this );
            BOOST_CHECK_EQUAL( currentPlayer_, identifier );
        }
        void checkWinner( unsigned int identifier )
        {
            manager_.accept( *this );
            BOOST_CHECK_EQUAL( winner_, identifier );
        }
    private:
        const core::PlayersManager& manager_;
        core::Players players_;
        unsigned int currentPlayer_;
        unsigned int winner_;
    };
}

BOOST_AUTO_TEST_CASE( players_manager_can_add_and_remove_players )
{
    core::PlayersManager manager( 10 );
    Visitor receiver( manager );
    manager.addPlayer( 0, "Player1" );
    manager.addPlayer( 1, "Player2" );
    manager.addPlayer( 2, "Player3" );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 0 ) )
                                                    ( 1, core::Player( "Player2", 0 ) )
                                                    ( 2, core::Player( "Player3", 0 ) ) );
    manager.removePlayer( 1 );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 0 ) )
                                                    ( 2, core::Player( "Player3", 0 ) ) );
}

BOOST_AUTO_TEST_CASE( players_manager_can_switch_to_next_player )
{
    core::PlayersManager manager( 10 );
    Visitor receiver( manager );
    manager.addPlayer( 0, "Player1" );
    manager.addPlayer( 1, "Player2" );
    manager.addPlayer( 2, "Player3" );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 0 ) )
                                                    ( 1, core::Player( "Player2", 0 ) )
                                                    ( 2, core::Player( "Player3", 0 ) ) );
    manager.switchToNextPlayer();
    manager.addToCurrentPlayerScore( 6 );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 6 ) )
                                                    ( 1, core::Player( "Player2", 0 ) )
                                                    ( 2, core::Player( "Player3", 0 ) ) );
    manager.switchToNextPlayer();
    manager.addToCurrentPlayerScore( 13 );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 6 ) )
                                                    ( 1, core::Player( "Player2", 13 ) )
                                                    ( 2, core::Player( "Player3", 0 ) ) );
    manager.switchToNextPlayer();
    manager.addToCurrentPlayerScore( 3 );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 6 ) )
                                                    ( 1, core::Player( "Player2", 13 ) )
                                                    ( 2, core::Player( "Player3", 3 ) ) );
    manager.switchToNextPlayer();
    manager.addToCurrentPlayerScore( 3 );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 9 ) )
                                                    ( 1, core::Player( "Player2", 13 ) )
                                                    ( 2, core::Player( "Player3", 3 ) ) );
    manager.switchToNextPlayer();
    manager.addToCurrentPlayerScore( 3 );
    receiver.checkPlayers( boost::assign::map_list_of( 0, core::Player( "Player1", 9 ) )
                                                    ( 1, core::Player( "Player2", 13 ) )
                                                    ( 2, core::Player( "Player3", 6 ) ) );
}

BOOST_AUTO_TEST_CASE( players_manager_notifies_current_player_to_receiver )
{
    core::PlayersManager manager( 10 );
    Visitor receiver( manager );
    manager.addPlayer( 0, "Player1" );
    manager.addPlayer( 1, "Player2" );
    manager.switchToNextPlayer();
    receiver.checkCurrentPlayer( 0 );
    manager.switchToNextPlayer();
    receiver.checkCurrentPlayer( 1 );
    manager.addToCurrentPlayerScore( 13 );
    manager.switchToNextPlayer();
    receiver.checkCurrentPlayer( 0 );
    manager.switchToNextPlayer();
    receiver.checkCurrentPlayer( 0 );
}

BOOST_AUTO_TEST_CASE( players_manager_notifies_winner )
{
    core::PlayersManager manager( 10 );
    Visitor receiver( manager );
    manager.addPlayer( 0, "Player1" );
    manager.addPlayer( 1, "Player2" );
    receiver.checkWinner( CORE_UNKNOWN_PLAYER );
    manager.switchToNextPlayer();
    manager.addToCurrentPlayerScore( 13 );
    receiver.checkWinner( 1 );
}
