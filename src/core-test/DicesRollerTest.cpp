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
#include "core/DicesRoller.h"
#include "core/DicesRollerDataReceiver_Int.h"
#include <boost/foreach.hpp>

namespace
{
    class Visitor : public core::DicesRollerDataReceiver_Int
    {
    public:
        Visitor( unsigned int numberOfDices )
            : numberOfDices_( numberOfDices )
        {}
        virtual void receiveDiceRoll( core::DiceRoll diceRoll )
        {
            lastRolls_.push_back( diceRoll );
        }
        void clearLastRolls()
        {
            lastRolls_.clear();
        }
        void checkLastRolls() const
        {
            BOOST_CHECK_EQUAL( lastRolls_.size(), numberOfDices_ );
            BOOST_FOREACH( core::DiceRoll diceRoll, lastRolls_ )
                BOOST_CHECK( diceRoll >= 1 && diceRoll <= 6 );
        }
    private:
        const unsigned int numberOfDices_;
        core::DicesRolls lastRolls_;
    };

}

BOOST_AUTO_TEST_CASE( dices_roller_rolls_dices )
{
    const unsigned int numberOfDices = 2;
    core::DicesRoller roller( numberOfDices );
    Visitor receiver( numberOfDices );
    for( unsigned int i = 0; i < 100; ++i ) // Try a hundred different cases
    {
        roller.rollDices();
        receiver.clearLastRolls();
        roller.accept( receiver );
        receiver.checkLastRolls();
    }
}
