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

#ifndef MODEL_H
#define MODEL_H

#include <set>
#include <vector>
#include <string>
#include <map>

#define CORE_UNKNOWN_PLAYER 4294967295

namespace core
{
    typedef unsigned int DiceRoll;
    typedef std::vector< DiceRoll > DicesRolls;
    typedef std::pair< unsigned int, bool > Token;
    typedef std::map< unsigned int, bool > Tokens;
    typedef std::map< unsigned int, bool > Combination;
    typedef std::vector< Combination > Combinations;
    struct Player
    {
        Player()
            : name( "Unknown Player" )
            , score( 0 )
        {}
        Player( const std::string& playerName, unsigned int playerScore )
            : name( playerName )
            , score( playerScore )
        {}
        std::string name;
        unsigned int score;
    };
    typedef std::map< unsigned int, Player > Players;
    inline unsigned int accumulateTokens( unsigned int value, const core::Token& token )
    {
        return value + token.first;
    }
    inline unsigned int accumulateFacedUpTokens( unsigned int value, const core::Token& token )
    {
        if( token.second )
            return value + token.first;
        return value;
    }
}

#endif // MODEL_H
