#ifndef I2C_HPP
#define I2C_HPP

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
#include <Wire/Wire.h>
#include <wiring_private.h>

// Engine
#include "utility.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

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

//------------------------------------------------------------------------------
//

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

} // engine

#endif // I2C_HPP
