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

#include "ConsoleUserInterface.h"
#include "core/CombinationsComputer_Int.h"
#include "core/PlayerChoiceManagerDataReceiver_Int.h"
#include "core/DicesRoller_Int.h"
#include "core/TokensPool_Int.h"
#include "core/PlayersManager_Int.h"
#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>

using namespace console;

ConsoleUserInterface::ConsoleUserInterface( const core::CombinationsComputer_Int& computer, const core::DicesRoller_Int& dicesRoller,
                                            const core::TokensPool_Int& tokensPool, const core::PlayersManager_Int& playersManager )
    : computer_( computer )
    , dicesRoller_( dicesRoller )
    , tokensPool_( tokensPool )
    , playersManager_( playersManager )
    , currentPlayer_( CORE_UNKNOWN_PLAYER )
    , winner_( CORE_UNKNOWN_PLAYER )
{
}

ConsoleUserInterface::~ConsoleUserInterface()
{
}

void ConsoleUserInterface::announceDicesRoll()
{
    dicesRolls_.clear();
    dicesRoller_.accept( *this );
    std::cout << "Dices roll: ";
    BOOST_FOREACH( core::DiceRoll diceRoll, dicesRolls_ )
        std::cout << diceRoll << " ";
    std::cout << std::endl;
}

void ConsoleUserInterface::announceTokensLeft()
{
    tokens_.clear();
    tokensPool_.accept( *this );
    std::cout << "Tokens left: ";
    BOOST_FOREACH( const core::Token& token, tokens_ )
        if( token.second )
            std::cout << token.first << " ";
    std::cout << std::endl;
}

void ConsoleUserInterface::announceCombinations()
{
    combinations_.clear();
    computer_.accept( *this );

    if( !combinationAvailable_ )
    {
        std::cout << "No combination available ... Sorry !" << std::endl;
        return;
    }

    std::cout << "Combinations available are:" << std::endl;
    for( unsigned int i = 1; i <= combinations_.size(); ++i )
    {
        std::cout << i << ": .";
        const core::Combination& combination = combinations_[ i - 1 ];
        BOOST_FOREACH( const core::Token& token, combination )
            std::cout << token.first << ".";
        std::cout << std::endl;
    }
}

void ConsoleUserInterface::announcePlayerTurn()
{
    players_.clear();
    playersManager_.accept( *this );
    std::cout << "============================================================" << std::endl
              << "This is now " << players_.find( currentPlayer_ )->second.name << "'s turn !" << std::endl
              << "His score is " << players_.find( currentPlayer_ )->second.score << "." << std::endl;
}

void ConsoleUserInterface::announceEndOfGame()
{
    std::cout << "============================================================" << std::endl
              << "Game is over !" << std::endl;
}

void ConsoleUserInterface::announceWinner()
{
    players_.clear();
    playersManager_.accept( *this );
    std::cout << "And the winner is " << players_[ winner_ ].name << " !" << std::endl;
}

void ConsoleUserInterface::accept( core::PlayerChoiceManagerDataReceiver_Int& receiver ) const
{
    receiver.receiveChosenCombination( chosenCombination_ );
}

void ConsoleUserInterface::askForCombinationChoice()
{
    std::string input;
    unsigned int choice;
    do
    {
        std::cout << "Please choose a combination: ";
        getline( std::cin, input );
        std::stringstream ss( input );
        ss >> choice;
    } while( choice <= 0 || choice > combinations_.size() );
    chosenCombination_ = combinations_[ choice - 1 ];
}

void ConsoleUserInterface::receiveCombinationAvailable( bool combinationAvailable )
{
    combinationAvailable_ = combinationAvailable;
}

void ConsoleUserInterface::receiveCombination( const core::Combination& combination )
{
    combinations_.push_back( combination );
}

void ConsoleUserInterface::receiveDiceRoll( core::DiceRoll diceRoll )
{
    dicesRolls_.push_back( diceRoll );
}

void ConsoleUserInterface::receiveToken( const core::Token& token )
{
    tokens_.insert( token );
}

void ConsoleUserInterface::receivePlayer( unsigned int identifier, const std::string& name, unsigned int score )
{
    players_.insert( core::Players::value_type( identifier, core::Player( name, score ) ) );
}

void ConsoleUserInterface::receiveCurrentPlayer( unsigned int identifier )
{
    currentPlayer_ = identifier;
}

void ConsoleUserInterface::receiveWinner( unsigned int identifier )
{
    winner_ = identifier;
}
