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
#include "core/GameSequencer.h"
#include "core-test/MockPlayersManager.h"
#include "core-test/MockDicesRoller.h"
#include "core-test/MockTokensPool.h"
#include "core-test/MockCombinationsComputer.h"
#include "core-test/MockAnnouncer.h"
#include "core-test/MockGameStateChecker.h"
#include "core-test/MockPlayerChoiceManager.h"
#include <boost/foreach.hpp>
#include <boost/assign/list_of.hpp>

namespace
{
    void notifyCombinations( core::CombinationsComputerDataReceiver_Int& receiver, const core::Combinations& combinations )
    {
        receiver.receiveCombinationAvailable( combinations.size() > 0 );
        BOOST_FOREACH( const core::Combination& combination, combinations )
            receiver.receiveCombination( combination );
    }
    void notifyChosenCombination( core::PlayerChoiceManagerDataReceiver_Int& receiver, const core::Combination& combination )
    {
        receiver.receiveChosenCombination( combination );
    }
    void notifyTokens( core::TokensPoolDataReceiver_Int& receiver, const core::Tokens& tokens )
    {
        BOOST_FOREACH( const core::Token& token, tokens )
            receiver.receiveToken( token );
    }
}

BOOST_AUTO_TEST_CASE( game_sequencer_sequences_a_simple_game )
{
    core::MockPlayersManager playersManager;
    core::MockDicesRoller dicesRoller;
    core::MockTokensPool tokensPool;
    core::MockCombinationsComputer combinationsComputer;
    core::MockAnnouncer announcer;
    core::MockGameStateChecker gameStateChecker;
    core::MockPlayerChoiceManager playerChoiceManager;
    const unsigned int gameScoreLimit = 10;
    core::GameSequencer gameSequencer( playersManager, dicesRoller, tokensPool,
                                       combinationsComputer, announcer, gameStateChecker,
                                       playerChoiceManager, gameScoreLimit );
    mock::sequence s;
    MOCK_EXPECT( gameStateChecker, isGameOver ).once().in( s ).returns( false );
    MOCK_EXPECT( playersManager, switchToNextPlayer ).once().in( s );
    MOCK_EXPECT( announcer, announcePlayerTurn ).once().in( s );
    MOCK_EXPECT( tokensPool, reset ).once().in( s );
    MOCK_EXPECT( dicesRoller, rollDices ).once().in( s );
    MOCK_EXPECT( announcer, announceDicesRoll ).once().in( s );
    MOCK_EXPECT( combinationsComputer, compute ).once().in( s );
    MOCK_EXPECT( announcer, announceTokensLeft ).once().in( s );
    MOCK_EXPECT( announcer, announceCombinations ).once().in( s );
    core::Combination combination1 = boost::assign::map_list_of( 1, true )( 3, true )( 4, true );
    core::Combinations combinations = boost::assign::list_of( combination1 );
    MOCK_EXPECT( combinationsComputer, accept ).once().in( s ).calls( boost::bind( &notifyCombinations, boost::ref( gameSequencer ),
                                                                                  boost::cref( combinations ) ) );
    MOCK_EXPECT( playerChoiceManager, askForCombinationChoice ).once().in( s );
    MOCK_EXPECT( playerChoiceManager, accept ).once().in( s ).calls( boost::bind( &notifyChosenCombination, boost::ref( gameSequencer ),
                                                                                 boost::cref( combination1 ) ) );
    MOCK_EXPECT( tokensPool, turnFaceDown ).once().in( s ).with( boost::cref( combination1 ) );
    MOCK_EXPECT( dicesRoller, rollDices ).once().in( s );
    MOCK_EXPECT( announcer, announceDicesRoll ).once().in( s );
    MOCK_EXPECT( combinationsComputer, compute ).once().in( s );
    MOCK_EXPECT( announcer, announceTokensLeft ).once().in( s );
    MOCK_EXPECT( announcer, announceCombinations ).once().in( s );
    MOCK_EXPECT( combinationsComputer, accept ).once().in( s ).calls( boost::bind( &notifyCombinations, boost::ref( gameSequencer ),
                                                                                  core::Combinations() ) );
    core::Tokens tokens = boost::assign::map_list_of( 1, false )( 2, true )( 3, false )( 4, false )( 5, true );
    MOCK_EXPECT( tokensPool, accept ).once().in( s ).calls( boost::bind( &notifyTokens, boost::ref( gameSequencer ),
                                                                        boost::cref( tokens ) ) );
    MOCK_EXPECT( playersManager, addToCurrentPlayerScore ).once().in( s ).with( 7u );
    MOCK_EXPECT( gameStateChecker, isGameOver ).once().in( s ).returns( true );
    MOCK_EXPECT( announcer, announceEndOfGame ).once().in( s );
    MOCK_EXPECT( announcer, announceWinner ).once().in( s );
    gameSequencer.startNewGame();
}
