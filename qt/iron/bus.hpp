#ifndef BUS_HPP
#define BUS_HPP

// Copyright (C) 2015 Engine Development
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

//------------------------------------------------------------------------------
//

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEFINE_BUS_PROTOCOL( NAME, S_ID, S_CONN, S_DCONN ) \
    struct NAME; \
    \
    template<> \
    struct TBus< NAME > \
    { \
        enum Signal \
        { \
            ID         = S_ID, \
            Connect    = S_CONN, \
            Disconnect = S_DCONN \
        }; \
    }; \

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P, int A >
struct BDevice
{
};

//------------------------------------------------------------------------------
//

template< class P, int A >
struct Device : BDevice< P, A >
{
};

//------------------------------------------------------------------------------
//

template< class P >
struct TBus
{
    enum Signal
    {
        ID         = 0x0,
        Connect    = 0x0,
        Disconnect = 0x0
    };
};

} // engine

//------------------------------------------------------------------------------
//

#include "bus.ipp"

#endif // BUS_HPP
