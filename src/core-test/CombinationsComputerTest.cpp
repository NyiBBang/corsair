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
#include "core/CombinationsComputer.h"
#include "core/CombinationsComputerDataReceiver_Int.h"
#include "MockDicesRoller.h"
#include "MockTokensPool.h"
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <list>
#include <set>
#include <algorithm>
#include <map>
#include <numeric>
#include <stdlib.h>
#include <time.h>

namespace
{
    class Visitor : public core::CombinationsComputerDataReceiver_Int
    {
    public:
        Visitor( core::Combinations& combinations )
            : combinations_( combinations )
        {
        }
        virtual void receiveCombinationAvailable( bool /*combinationAvailable*/ )
        {
        }
        virtual void receiveCombination( const core::Combination& combination )
        {
            combinations_.push_back( combination );
        }
    private:
        core::Combinations& combinations_;
    };

    class DataComputer
    {
    public:
        DataComputer( core::CombinationsComputer& combinationsComputer )
            : combinationsComputer_( combinationsComputer )
        {}
        void compute()
        {
            dicesRolls_.clear();
            tokens_.clear();
            for( unsigned int i = 0; i < 2; ++i )
                dicesRolls_.push_back( rand() % 6 + 1 );
            for( unsigned int i = 1; i <= 9; ++i )
                tokens_[ i ] = rand() % 2 == 0;
        }
        void notifyDicesRolls()
        {
            BOOST_FOREACH( core::DiceRoll diceRoll, dicesRolls_ )
                combinationsComputer_.receiveDiceRoll( diceRoll );
        }
        void notifyTokens()
        {
            BOOST_FOREACH( core::Token token, tokens_ )
                combinationsComputer_.receiveToken( token );
        }
        const core::DicesRolls& GetDicesRolls() const
        {
            return dicesRolls_;
        }
        core::Tokens GetTokens() const
        {
            return tokens_;
        }
    private:
        core::DicesRolls dicesRolls_;
        core::Tokens tokens_;
        core::CombinationsComputer& combinationsComputer_;
    };

    void CheckCombination( const core::Combination& combination, const core::DicesRolls& dicesRolls, const core::Tokens& tokens )
    {
        BOOST_CHECK( combination.size() <= 4 );
        BOOST_CHECK_EQUAL( std::accumulate( combination.begin(), combination.end(), 0, &core::accumulateTokens ),
                           std::accumulate( dicesRolls.begin(), dicesRolls.end(), 0 ) );
        BOOST_FOREACH( core::Token tokenInCombination, combination )
        {
            core::Tokens::const_iterator it = tokens.find( tokenInCombination.first );
            BOOST_CHECK( it != tokens.end() && it->second );
        }
    }
}

BOOST_AUTO_TEST_CASE( combinations_are_computed )
{
    srand( static_cast< unsigned int>( time( 0 ) ) );
    core::MockDicesRoller dicesRoller;
    core::MockTokensPool tokensPool;
    core::CombinationsComputer combinationsComputer( dicesRoller, tokensPool );
    DataComputer dataComputer( combinationsComputer );
    for( unsigned int i = 0; i < 100; ++i ) // Try a hundred different cases
    {
        dataComputer.compute();
        MOCK_EXPECT( dicesRoller, accept ).once().calls( boost::bind( &DataComputer::notifyDicesRolls, &dataComputer ) );
        MOCK_EXPECT( tokensPool, accept ).once().calls( boost::bind( &DataComputer::notifyTokens, &dataComputer ));
        combinationsComputer.compute();
        const core::DicesRolls& dicesRolls = dataComputer.GetDicesRolls();
        const core::Tokens tokens = dataComputer.GetTokens();
        core::Combinations combinations;
        Visitor receiver( combinations );
        combinationsComputer.accept( receiver );
        BOOST_FOREACH( const core::Combination& combination, combinations )
            CheckCombination( combination, dicesRolls, tokens );
    }
}
