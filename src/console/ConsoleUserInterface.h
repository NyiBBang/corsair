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

#ifndef CONSOLEUSERINTERFACE_H
#define CONSOLEUSERINTERFACE_H

#include "core/Announcer_Int.h"
#include "core/PlayerChoiceManager_Int.h"
#include "core/CombinationsComputerDataReceiver_Int.h"
#include "core/DicesRollerDataReceiver_Int.h"
#include "core/TokensPoolDataReceiver_Int.h"
#include "core/PlayersManagerDataReceiver_Int.h"

namespace core
{
    class CombinationsComputer_Int;
    class DicesRoller_Int;
    class TokensPool_Int;
    class PlayersManager_Int;
}

namespace console
{
class ConsoleUserInterface : public core::Announcer_Int
                           , public core::PlayerChoiceManager_Int
                           , private core::CombinationsComputerDataReceiver_Int
                           , private core::DicesRollerDataReceiver_Int
                           , private core::TokensPoolDataReceiver_Int
                           , private core::PlayersManagerDataReceiver_Int
{
public:
    ConsoleUserInterface( const core::CombinationsComputer_Int& computer, const core::DicesRoller_Int& dicesRoller,
                          const core::TokensPool_Int& tokensPool, const core::PlayersManager_Int& playersManager );
    virtual ~ConsoleUserInterface();

    virtual void announceDicesRoll();
    virtual void announceTokensLeft();
    virtual void announceCombinations();
    virtual void announcePlayerTurn();
    virtual void announceEndOfGame();
    virtual void announceWinner();
    virtual void accept( core::PlayerChoiceManagerDataReceiver_Int& receiver ) const;
    virtual void askForCombinationChoice();

private:
    virtual void receiveCombinationAvailable( bool combinationAvailable );
    virtual void receiveCombination( const core::Combination& combination );
    virtual void receiveDiceRoll( core::DiceRoll diceRoll );
    virtual void receiveToken( const core::Token& token );
    virtual void receivePlayer( unsigned int identifier, const std::string& name, unsigned int score );
    virtual void receiveCurrentPlayer( unsigned int identifier );
    virtual void receiveWinner( unsigned int identifier );

private:
    const core::CombinationsComputer_Int& computer_;
    const core::DicesRoller_Int& dicesRoller_;
    const core::TokensPool_Int& tokensPool_;
    const core::PlayersManager_Int& playersManager_;
    bool combinationAvailable_;
    core::Combinations combinations_;
    core::Combination chosenCombination_;
    core::DicesRolls dicesRolls_;
    core::Tokens tokens_;
    core::Players players_;
    unsigned int currentPlayer_;
    unsigned int winner_;
};
}

#endif // CONSOLEUSERINTERFACE_H
