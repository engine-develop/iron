#ifndef UTILITY_MCU_HPP
#define UTILITY_MCU_HPP

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

// Arduino
#include <Arduino.h>

// AVR
#include <util/delay.h>

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------
//

namespace engine
{

//------------------------------------------------------------------------------
//

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

//------------------------------------------------------------------------------
//

static EN_INLINE void errorLED()
{
    DDRB |= B00100000; // Set as output

    // Wait for reset
    while ( 1 )
    {
        PORTB ^= B00100000; // Toggle LED
        _delay_ms( 100 );
    }
}

} // engine

#endif // UTILITY_MCU_HPP
