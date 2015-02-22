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
#include <cassert>
#endif // __AVR__
#include <cstdio>

// Arduino
#ifdef __AVR__
#include <Wire/Wire.h>
#include <wiring_private.h>
#endif // __AVR__

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

#define EN_PACK4( A, B, C, D ) ((A) << 24) | ((B) << 16) | ((C) << 8) | ((D) << 0)
#define EN_UPACK4( X, A, B, C, D ) \
    (A) = ( (X) >> 24 ) & 0xFF; \
    (B) = ( (X) >> 16 ) & 0xFF; \
    (C) = ( (X) >> 8  ) & 0xFF; \
    (D) = ( (X) >> 0  ) & 0xFF; \

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

//------------------------------------------------------------------------------
//
#ifdef __AVR__
static void printf( const char *fmt, ... )
{
    char buf[ 128 ];
    va_list args;
    va_start( args, fmt );
    vsnprintf( buf, sizeof( buf ), fmt, args );
    va_end( args );
    buf[ sizeof( buf ) / sizeof( buf[ 0 ] ) - 1 ] = '\0';
    Serial.print( buf );
}
#endif // __AVR__

//------------------------------------------------------------------------------
//
#ifdef __AVR__
static EN_INLINE void errorLED()
{
    DDRB |= B00100000; // Set as output

    // Wait for reset
    while ( 1 )
    {
        PORTB ^= B00100000; // Toggle LED
        delay( 100 );
    }
}
#endif // __AVR__

//------------------------------------------------------------------------------
//
#ifdef __AVR__
EN_INLINE void disableI2CPullups()
{
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
    // deactivate internal pull-ups for twi
    // as per note from atmega8 manual pg167
    cbi( PORTC, 4 );
    cbi( PORTC, 5 );
#else
    // deactivate internal pull-ups for twi
    // as per note from atmega128 manual pg204
    cbi( PORTD, 0 );
    cbi( PORTD, 1 );
#endif
}
#endif // __AVR__

//------------------------------------------------------------------------------
//
#ifdef __AVR__
EN_INLINE int scanI2CDevices()
{
    Serial.println( "Scanning I2C Devices..." );

    int nDevices = 0;

    for ( uint8_t addr = 1; addr < 127; addr++ )
    {
        Wire.beginTransmission( addr );

        if ( Wire.endTransmission() == 0 )
        {
            Serial.print( "\tDevice: 0x" );
            if ( addr < 16 ) Serial.print( "0" );
            Serial.println( addr, HEX );

            ++nDevices;
        }
    }

    Serial.print( nDevices );
    Serial.println( " devices found\n" );

    return nDevices;
}
#endif // __AVR__

} // engine

#endif // UTILITY_HPP
