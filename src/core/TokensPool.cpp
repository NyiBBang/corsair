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

#include "TokensPool.h"
#include "TokensPoolDataReceiver_Int.h"
#include <boost/foreach.hpp>

using namespace core;

TokensPool::TokensPool( unsigned int size )
{
    for( unsigned int tokenValue = 1; tokenValue <= size; ++tokenValue )
        tokens_.insert( Token( tokenValue, true ) );
}

void TokensPool::turnFaceDown( const Combination& combination )
{
    BOOST_FOREACH( const Token& token, combination )
    {
        Tokens::iterator it = tokens_.find( token.first );
        if( it != tokens_.end() )
            it->second = false;
    }
}

void TokensPool::reset()
{
    for( Tokens::iterator it = tokens_.begin(); it != tokens_.end(); ++it )
        it->second = true;
}

void TokensPool::accept( TokensPoolDataReceiver_Int& receiver ) const
{
    BOOST_FOREACH( const Token& token, tokens_ )
        receiver.receiveToken( token );
}
