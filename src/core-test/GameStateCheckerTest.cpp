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
#include "MockPlayersManager.h"
#include "core/GameStateChecker.h"
#include "core/Types.h"
#include <boost/foreach.hpp>
#include <boost/assign/list_of.hpp>

namespace
{
    void notifyPlayers( core::PlayersManagerDataReceiver_Int& receiver, const core::Players& players )
    {
        BOOST_FOREACH( core::Players::value_type player, players )
            receiver.receivePlayer( player.first, player.second.name, player.second.score );
    }
}

BOOST_AUTO_TEST_CASE( game_state_checker_tells_that_game_is_over_when_only_one_player_left )
{
    core::MockPlayersManager playersManager;
    core::GameStateChecker checker( playersManager, 10 );
    core::Players players = boost::assign::map_list_of( 0, core::Player( "Player1", 5 ) )
                                                      ( 1, core::Player( "Player2", 15 ) );
    MOCK_EXPECT( playersManager, accept ).once().calls( boost::bind( &notifyPlayers, checker, players ) );
    BOOST_CHECK( checker.isGameOver() );
}

BOOST_AUTO_TEST_CASE( game_state_checker_tells_that_game_is_over_when_no_player_left )
{
    core::MockPlayersManager playersManager;
    core::GameStateChecker checker( playersManager, 10 );
    core::Players players = boost::assign::map_list_of( 0, core::Player( "Player1", 42 ) )
                                                      ( 1, core::Player( "Player2", 15 ) )
                                                      ( 2, core::Player( "Player3", 25 ) );
    MOCK_EXPECT( playersManager, accept ).once().calls( boost::bind( &notifyPlayers, checker, players ) );
    BOOST_CHECK( checker.isGameOver() );
}

BOOST_AUTO_TEST_CASE( game_state_checker_tells_that_game_is_not_over_when_several_players_are_left )
{
    core::MockPlayersManager playersManager;
    core::GameStateChecker checker( playersManager, 10 );
    core::Players players = boost::assign::map_list_of( 0, core::Player( "Player1", 2 ) )
                                                      ( 1, core::Player( "Player2", 9 ) )
                                                      ( 2, core::Player( "Player3", 25 ) );
    MOCK_EXPECT( playersManager, accept ).once().calls( boost::bind( &notifyPlayers, boost::ref( checker ), boost::cref( players ) ) );
    BOOST_CHECK( !checker.isGameOver() );
}
