#ifndef IR_SIGNAL_HPP
#define IR_SIGNAL_HPP

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
        static EN_INLINE const uint8_t* id(); \
    }; \
    \
    EN_INLINE const char* TSignal< NAME >::name() { return EN_STRINGIZE( NAME ); } \
    \
    EN_INLINE const uint8_t* TSignal< NAME >::id() \
    { \
        static uint8_t s_id[ signal_size ] = { ID_0, ID_1, ID_2, ID_3 }; \
        \
        return s_id; \
    } \

namespace engine
{

//------------------------------------------------------------------------------
//

static const uint8_t signal_size = 4;

//------------------------------------------------------------------------------
//

template< class S >
struct TSignal
{
    static const bool valid = false;
    static EN_INLINE const char* name();
    static EN_INLINE const uint8_t* id();
};

template< class S >
EN_INLINE const char* TSignal< S >::name() { return ""; }

template< class S >
EN_INLINE const uint8_t* TSignal< S >::id()
{
    static uint8_t s_id[ signal_size ] = { 0x0, 0x0, 0x0, 0x0 };

    return s_id;
}

//------------------------------------------------------------------------------
// Define standard signals
//

EN_DEFINE_SIGNAL( Signal_ID,     0x2B, 0x43, 0x06, 0x0D )
EN_DEFINE_SIGNAL( Signal_Select, 0x03, 0x16, 0x93, 0x63 )
EN_DEFINE_SIGNAL( Signal_Write,  0x3E, 0x3A, 0x59, 0x11 )
EN_DEFINE_SIGNAL( Signal_Read,   0x21, 0x31, 0x56, 0x8E )

} // engine

#endif // IR_SIGNAL_HPP
