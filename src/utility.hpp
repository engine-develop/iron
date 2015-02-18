#ifndef UTILITY_HPP
#define UTILITY_HPP

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

// STD
#ifndef __AVR__
#ifdef LINUX
#include <unistd.h>
#endif // LINUX
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#endif // __AVR__
#include <stdio.h>

// Engine
#include "types.hpp"

//------------------------------------------------------------------------------
//

#define EN_STRINGIZE( X ) #X
#define EN_STRING( X ) EN_STRINGIZE( X )

#ifdef __AVR__
#define EN_PRINT( ... ) engine::printf( __VA_ARGS__ );
#else
#define EN_PRINT( ... ) printf( __VA_ARGS__ );
#endif // __AVR__

#ifdef NDEBUG
#define EN_DEBUG( ... )
#else
#ifdef __AVR__
#define EN_DEBUG( ... ) EN_PRINT( __VA_ARGS__ );
#else
#define EN_DEBUG( ... ) EN_PRINT( __VA_ARGS__ );
#endif // __AVR__
#endif // NDEBUG

#define EN_ASSERT( X, ... ) \
    if ( !(X) ) \
    { \
        EN_PRINT( "assertion failed: %s, line %d: %s\n", __FILE__, __LINE__, __VA_ARGS__ ) \
    } \

#define EN_INLINE    __attribute__( ( always_inline ) ) inline
#define EN_NO_INLINE __attribute__( ( noinline ) )

#define setBit( X, N )    (X) |= (1UL << (N));
#define clearBit( X, N )  (X) &= (1UL << (N));
#define toggleBit( X, N ) (X) ^= (1UL << (N));

#define byteLow( X ) ( (uint8_t) ( (X) & 0xFF ) )
#define byteHigh( X ) ( (uint8_t) ( (X) >> 8 ) )
#define bytesJoin( H, L ) ( ( (H) << 8 ) | (L) )

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE void delay_ms( size_t ms )
{
#ifdef __AVR__
    delay( ms );
#endif // __AVR__
#ifdef LINUX
    usleep( ms * 1000U );
#endif // LINUX
#ifdef _WIN32
    Sleep( ms );
#endif // _WIN32
}

} // engine

#endif // UTILITY_HPP
