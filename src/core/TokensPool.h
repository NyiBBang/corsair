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

#ifndef TOKENSPOOL_H
#define TOKENSPOOL_H

#include "TokensPool_Int.h"

namespace core
{
class TokensPool : public TokensPool_Int
{
public:
    TokensPool( unsigned int size );

    virtual void turnFaceDown( const Combination& combination );
    virtual void reset();
    virtual void accept( TokensPoolDataReceiver_Int& receiver ) const;

private:
    Tokens tokens_;
};

}

#endif // TOKENSPOOL_H
