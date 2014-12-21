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

#ifndef COMBINATIONSCOMPUTER_H
#define COMBINATIONSCOMPUTER_H

#include "CombinationsComputer_Int.h"
#include "DicesRollerDataReceiver_Int.h"
#include "TokensPoolDataReceiver_Int.h"
#include "Types.h"
#include <list>
#include <set>

namespace core
{
    class DicesRoller_Int;
    class TokensPool_Int;

class CombinationsComputer : public CombinationsComputer_Int
                           , public DicesRollerDataReceiver_Int
                           , public TokensPoolDataReceiver_Int
{
public:
    CombinationsComputer( const DicesRoller_Int& dicesRoller, const TokensPool_Int& tokensPool );

    virtual void accept( CombinationsComputerDataReceiver_Int& receiver ) const;
    virtual void receiveDiceRoll( DiceRoll diceRoll );
    virtual void receiveToken( const Token& token );
    virtual void compute();

private:
    const DicesRoller_Int& dicesRoller_;
    const TokensPool_Int& tokensPool_;
    DicesRolls lastDicesRolls_;
    Tokens tokens_;
    Combinations computedCombinations_;
};
}

#endif // COMBINATIONSCOMPUTER_H
