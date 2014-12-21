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

#ifndef COMBINATIONSCOMPUTERDATARECEIVER_INT_H
#define COMBINATIONSCOMPUTERDATARECEIVER_INT_H

#include "Types.h"
#include <set>

namespace core
{
class CombinationsComputerDataReceiver_Int
{
public:
    CombinationsComputerDataReceiver_Int() {}
    virtual ~CombinationsComputerDataReceiver_Int() {}

    virtual void receiveCombinationAvailable( bool combinationAvailable ) = 0;
    virtual void receiveCombination( const Combination& combination ) = 0;
};
}

#endif // COMBINATIONSCOMPUTERDATARECEIVER_INT_H
