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

#include "GameSequencer.h"
#include "PlayersManager_Int.h"
#include "DicesRoller_Int.h"
#include "TokensPool_Int.h"
#include "CombinationsComputer_Int.h"
#include "Announcer_Int.h"
#include "GameStateChecker_Int.h"
#include "PlayerChoiceManager_Int.h"
#include <boost/foreach.hpp>
#include <numeric>

using namespace core;

GameSequencer::GameSequencer( PlayersManager_Int& playersManager, DicesRoller_Int& dicesRoller,
                              TokensPool_Int& tokensPool, CombinationsComputer_Int& combinationsComputer,
                              Announcer_Int& announcer, GameStateChecker_Int& gameStateChecker,
                              PlayerChoiceManager_Int& playerChoiceManager, const unsigned int gameScoreLimit )
    : playersManager_( playersManager )
    , dicesRoller_( dicesRoller )
    , tokensPool_( tokensPool )
    , combinationsComputer_( combinationsComputer )
    , announcer_( announcer )
    , gameStateChecker_( gameStateChecker )
    , playerChoiceManager_( playerChoiceManager )
    , gameScoreLimit_( gameScoreLimit )
{
}

void GameSequencer::startNewGame()
{
    while( !gameStateChecker_.isGameOver() )
    {
        playersManager_.switchToNextPlayer();
        announcer_.announcePlayerTurn();
        tokensPool_.reset();
        do
        {
            dicesRoller_.rollDices();
            announcer_.announceDicesRoll();
            combinationsComputer_.compute();
            announcer_.announceTokensLeft();
            announcer_.announceCombinations();
            combinationsComputer_.accept( *this );
            if( combinationAvailable_ )
            {
                playerChoiceManager_.askForCombinationChoice();
                playerChoiceManager_.accept( *this );
                tokensPool_.turnFaceDown( chosenCombination_ );
            }
        } while( combinationAvailable_ );
        tokens_.clear();
        tokensPool_.accept( *this );
        const unsigned int tokensSum = std::accumulate( tokens_.begin(), tokens_.end(), 0u, &accumulateFacedUpTokens );
        playersManager_.addToCurrentPlayerScore( tokensSum );
    }
    announcer_.announceEndOfGame();
    announcer_.announceWinner();
}

void GameSequencer::receiveCombinationAvailable( bool combinationAvailable )
{
    combinationAvailable_ = combinationAvailable;
}

void GameSequencer::receiveCombination( const Combination& /*combination*/ )
{}

void GameSequencer::receiveChosenCombination( const Combination& chosenCombination )
{
    chosenCombination_ = chosenCombination;
}

void GameSequencer::receiveToken( const Token& token )
{
    tokens_.insert( token );
}
