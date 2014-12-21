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
#include "core/TokensPool.h"
#include "core/TokensPoolDataReceiver_Int.h"
#include <boost/foreach.hpp>
#include <boost/assign/list_of.hpp>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

namespace
{
    class Visitor : public core::TokensPoolDataReceiver_Int
    {
    public:
        Visitor( unsigned int poolSize )
            : poolSize_( poolSize )
        {}
        void clear()
        {
            tokensFaceUp_.clear();
        }
        virtual void receiveToken( const core::Token& token )
        {
            if( token.second )
                tokensFaceUp_.insert( token );
        }
        void checkTokensFaceUp( const core::Combination& combination )
        {
            std::vector< core::Token > intersection;
            intersection.resize( std::set_intersection( tokensFaceUp_.begin(), tokensFaceUp_.end(),
                                                        combination.begin(), combination.end(),
                                                        intersection.begin() ) - intersection.begin() );
            BOOST_CHECK_EQUAL( intersection.size(), 0u );
            BOOST_CHECK_EQUAL( tokensFaceUp_.size(), poolSize_ - combination.size() );
        }
    private:
        const unsigned int poolSize_;
        core::Tokens tokensFaceUp_;
    };

    class CombinationGenerator
    {
    public:
        CombinationGenerator( unsigned int poolSize )
            : poolSize_( poolSize )
        {
            srand( static_cast< unsigned int>( time( 0 ) ) );
        }
        core::Combination generateCombination()
        {
            core::Combination combination;
            const unsigned int numberOfTokens = rand() % 4 + 1;
            for( unsigned int i = 0; i < numberOfTokens; ++i )
            {
                core::Token token;
                token.second = true;
                do
                {
                    token.first = rand() % poolSize_ + 1;
                } while( combination.find( token.first ) != combination.end() );
                combination.insert( token );
            }
            return combination;
        }
    private:
        const unsigned int poolSize_;
    };
}

BOOST_AUTO_TEST_CASE( tokens_can_be_turned_face_down_and_reset )
{
    const unsigned int poolSize = 5;
    core::TokensPool pool( poolSize );
    CombinationGenerator generator( poolSize );
    Visitor receiver( poolSize );
    for( unsigned int i = 0; i < 100; ++i ) // Try a hundred different cases
    {
        core::Combination combination = generator.generateCombination();
        pool.reset();
        pool.turnFaceDown( combination );
        receiver.clear();
        pool.accept( receiver );
        receiver.checkTokensFaceUp( combination );
    }
}
