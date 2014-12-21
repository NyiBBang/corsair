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

#include "DicesRoller.h"
#include "DicesRollerDataReceiver_Int.h"
#include <boost/foreach.hpp>
#include <cstdlib>
#include <ctime>

using namespace core;

DicesRoller::DicesRoller( unsigned int numberOfDices )
    : numberOfDices_( numberOfDices )
{
    srand( static_cast< unsigned int >( time( 0 ) ) );
}

void DicesRoller::rollDices()
{
    lastRolls_.clear();
    for( unsigned int i = 0; i < numberOfDices_; ++i )
        lastRolls_.push_back( rand() % 6 + 1 );
}

void DicesRoller::accept( DicesRollerDataReceiver_Int& receiver ) const
{
    BOOST_FOREACH( DiceRoll diceRoll, lastRolls_ )
        receiver.receiveDiceRoll( diceRoll );
}
