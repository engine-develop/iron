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
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#endif

//------------------------------------------------------------------------------
//

#define EN_STRINGIZE( A ) #A
#define EN_STRING( A ) EN_STRINGIZE( A )

#define EN_INLINE    __attribute__( ( always_inline ) ) inline
#define EN_NO_INLINE __attribute__( ( noinline ) )

#define setBit( X, N )    (X) |= (1UL << (N));
#define clearBit( X, N )  (X) &= (1UL << (N));
#define toggleBit( X, N ) (X) ^= (1UL << (N));

#define byteLow( X ) ( (uint8_t) ( (X) & 0xFF ) )
#define byteHigh( X ) ( (uint8_t) ( (X) >> 8 ) )
#define bytesJoin( H, L ) ( ( (H) << 8 ) | (L) )

#ifdef NDEBUG
#define EN_DEBUG( ... )
#else
#ifdef __AVR__
#define EN_DEBUG( ... ) Serial.printf( __VA_ARGS__ );
#else
#define EN_DEBUG( ... ) printf( __VA_ARGS__ );
#endif // __AVR__
#endif // NDEBUG

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE void delay( size_t ms )
{
#ifdef __AVR__
    ::delay( ms );
#endif
#ifdef LINUX
    usleep( ms * 1000U );
#endif
#ifdef _WIN32
    Sleep( ms );
#endif
}

} // engine

#endif // UTILITY_HPP
