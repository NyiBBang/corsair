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

#ifndef DICESROLLER_H
#define DICESROLLER_H

#include "DicesRoller_Int.h"
#include "Types.h"
#include <list>

namespace core
{
class DicesRoller : public DicesRoller_Int
{
public:
    explicit DicesRoller( unsigned int numberOfDices );

    virtual void rollDices();
    virtual void accept( DicesRollerDataReceiver_Int& receiver ) const;

private:
    unsigned int numberOfDices_;
    DicesRolls lastRolls_;
};
}

#endif // DICESROLLER_H
