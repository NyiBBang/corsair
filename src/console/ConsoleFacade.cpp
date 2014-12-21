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

#include "ConsoleFacade.h"
#include <iostream>
#include <stdexcept>

using namespace console;

ConsoleFacade::ConsoleFacade()
    : gameScoreLimit_( 45 )
    , playersManager_( gameScoreLimit_ )
    , tokensPool_( 9 )
    , dicesRoller_( 2 )
    , combinationsComputer_( dicesRoller_, tokensPool_ )
    , gameStateChecker_( playersManager_, gameScoreLimit_ )
    , consoleUserInterface_( combinationsComputer_, dicesRoller_, tokensPool_, playersManager_ )
    , gameSequencer_( playersManager_, dicesRoller_, tokensPool_, combinationsComputer_,
                      consoleUserInterface_, gameStateChecker_, consoleUserInterface_, gameScoreLimit_ )
{
    playersManager_.addPlayer( 1, "Player1" );
    playersManager_.addPlayer( 2, "Player2" );
}

void ConsoleFacade::startNewGame()
{
    try
    {
        gameSequencer_.startNewGame();
    }
    catch( std::exception& ex )
    {
        std::cout << "ERROR: " << ex.what() << std::endl;
    }
}
