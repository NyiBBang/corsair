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

#include "CombinationsComputer.h"
#include "CombinationsComputerDataReceiver_Int.h"
#include "DicesRoller_Int.h"
#include "TokensPool_Int.h"
#include <boost/foreach.hpp>
#include <set>
#include <numeric>

using namespace core;

CombinationsComputer::CombinationsComputer( const DicesRoller_Int& dicesRoller, const TokensPool_Int& tokensPool )
    : dicesRoller_( dicesRoller )
    , tokensPool_( tokensPool )
{
}

void CombinationsComputer::accept( CombinationsComputerDataReceiver_Int& receiver ) const
{
    receiver.receiveCombinationAvailable( !computedCombinations_.empty() );
    BOOST_FOREACH( const Combination& combination, computedCombinations_ )
        receiver.receiveCombination( combination );
}

void CombinationsComputer::receiveDiceRoll( DiceRoll diceRoll )
{
    lastDicesRolls_.push_back( diceRoll );
}

void CombinationsComputer::receiveToken( const Token& token )
{
    tokens_.insert( token );
}

namespace
{
    Combinations GetCombinations( Tokens tokens, unsigned int result )
    {
        Combinations combinations;
        Tokens tokensLeftToTry = tokens;
        BOOST_FOREACH( Token token, tokens )
        {
            if( token.second )
            {
                if( token.first >= result )
                {
                    if( token.first == result )
                    {
                        Combination singleTokenCombination;
                        singleTokenCombination.insert( token );
                        combinations.push_back( singleTokenCombination );
                    }
                    break;
                }
                tokensLeftToTry.erase( token.first );
                Combinations subCombinations = GetCombinations( tokensLeftToTry, result - token.first );
                BOOST_FOREACH( Combination& subCombination, subCombinations )
                {
                    subCombination.insert( token );
                    combinations.push_back( subCombination );
                }
            }
        }
        return combinations;
    }
}

void CombinationsComputer::compute()
{
    lastDicesRolls_.clear();
    dicesRoller_.accept( *this );
    tokens_.clear();
    tokensPool_.accept( *this );
    computedCombinations_ = GetCombinations( tokens_, std::accumulate( lastDicesRolls_.begin(), lastDicesRolls_.end(), 0 ) );
}
