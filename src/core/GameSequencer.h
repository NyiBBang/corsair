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

#ifndef GAMESEQUENCER_H
#define GAMESEQUENCER_H

#include "CombinationsComputerDataReceiver_Int.h"
#include "TokensPoolDataReceiver_Int.h"
#include "PlayerChoiceManagerDataReceiver_Int.h"
#include <boost/noncopyable.hpp>
#include <list>
#include <set>

namespace core
{
    class PlayersManager_Int;
    class DicesRoller_Int;
    class TokensPool_Int;
    class CombinationsComputer_Int;
    class Announcer_Int;
    class GameStateChecker_Int;
    class PlayerChoiceManager_Int;

class GameSequencer : public CombinationsComputerDataReceiver_Int
                    , public TokensPoolDataReceiver_Int
                    , public PlayerChoiceManagerDataReceiver_Int
                    , private boost::noncopyable
{
public:
    GameSequencer( PlayersManager_Int& playersManager, DicesRoller_Int& dicesRoller,
                   TokensPool_Int& tokensPool, CombinationsComputer_Int& combinationsComputer,
                   Announcer_Int& announcer, GameStateChecker_Int& gameStateChecker,
                   PlayerChoiceManager_Int& playerChoiceManager, const unsigned int gameScoreLimit );

    void startNewGame();
    virtual void receiveCombinationAvailable( bool combinationAvailable );
    virtual void receiveCombination( const Combination& combination );
    virtual void receiveChosenCombination( const Combination& chosenCombination );
    virtual void receiveToken( const Token& token );

private:
    PlayersManager_Int& playersManager_;
    DicesRoller_Int& dicesRoller_;
    TokensPool_Int& tokensPool_;
    CombinationsComputer_Int& combinationsComputer_;
    Announcer_Int& announcer_;
    GameStateChecker_Int& gameStateChecker_;
    PlayerChoiceManager_Int& playerChoiceManager_;
    const unsigned int gameScoreLimit_;
    bool combinationAvailable_;
    Combination chosenCombination_;
    Tokens tokens_;
};
}

#endif // GAMESEQUENCER_H
