#ifndef SIGNAL_HPP
#define SIGNAL_HPP

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

#define EN_DEFINE_SIGNAL( NAME, ID_0, ID_1, ID_2, ID_3 ) \
    struct NAME; \
    \
    template<> \
    struct TSignal< NAME > \
    { \
        static const bool valid = true; \
        static EN_INLINE const char* name(); \
        static const uint8_t id[ 4 ]; \
    }; \
    \
    EN_INLINE const char* TSignal< NAME >::name() { return EN_STRINGIZE( NAME ); } \
    \
    const uint8_t TSignal< NAME >::id[] = { ID_0, ID_1, ID_2, ID_3 }; \

namespace engine
{

//------------------------------------------------------------------------------
//

template< class S >
struct TSignal
{
    static const bool valid = false;
    static EN_INLINE const char* name();
    static const uint8_t id[ 4 ];
};

template< class S >
EN_INLINE const char* TSignal< S >::name() { return ""; }

template< class S >
const uint8_t TSignal< S >::id[ 4 ] = { 0x0, 0x0, 0x0, 0x0 };

//------------------------------------------------------------------------------
// Define standard signals
//

EN_DEFINE_SIGNAL( Signal_ID,       0x2B, 0x43, 0x6,  0xD  )
EN_DEFINE_SIGNAL( Signal_Select,   0x3,  0x16, 0x93, 0x63 )
EN_DEFINE_SIGNAL( Signal_Deselect, 0x5B, 0x4C, 0x1F, 0x19 )
EN_DEFINE_SIGNAL( Signal_Write,    0x3E, 0x3A, 0x59, 0x11 )
EN_DEFINE_SIGNAL( Signal_Read,     0x21, 0x31, 0x56, 0x8E )

} // engine

#endif // SIGNAL_HPP
