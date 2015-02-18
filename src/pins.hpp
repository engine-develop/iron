#ifndef PINS_HPP
#define PINS_HPP

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
#ifdef __AVR__
#include <Arduino.h>
#include <wiring_private.h>
#endif // __AVR__

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------
//

#ifndef __AVR__
#define EN_DEFINE_PIN( ... )
#define EN_DEFINE_PIN_PWM( ... )
#else

#define EN_DEFINE_PIN( N, P, BIT, PWM, ANALOG ) \
    template<> \
    struct TPin< N > \
    { \
        static const uint8_t bit = BIT; \
        static const bool pwm    = PWM; \
        static const bool analog = ANALOG; \
    }; \
    \
    template<> \
    struct FPinSetMode< N, INPUT > \
    { \
        static EN_INLINE void eval() \
        { \
            DDR##P &= ~( 1 << TPin< N >::bit ); \
        } \
    }; \
    template<> \
    struct FPinSetMode< N, OUTPUT > \
    { \
        static EN_INLINE void eval() \
        { \
            DDR##P |= ( 1 << TPin< N >::bit ); \
        } \
    }; \
    \
    template<> \
    struct FPinSetDigital< N, HIGH > \
    { \
        static EN_INLINE void eval() \
        { \
            PORT##P |= ( 1 << TPin< N >::bit ); \
        } \
    }; \
    \
    template<> \
    struct FPinSetDigital< N, LOW > \
    { \
        static EN_INLINE void eval() \
        { \
            PORT##P &= ~( 1 << TPin< N >::bit ); \
        } \
    }; \
    \
    template<> \
    struct FPinGetDigital< N > \
    { \
        static EN_INLINE uint8_t eval() \
        { \
            return ( PIN##P & ( 1 << TPin< N >::bit ) ) ? HIGH : LOW; \
        } \
    }; \

#define EN_DEFINE_PIN_PWM( N, TCCR, COM, OCR ) \
    template<> \
    struct FPinSetAnalog< N > \
    { \
        static EN_INLINE void eval( const int16_t& value ) \
        { \
            sbi( TCCR, COM ); \
            OCR = value; \
        } \
    }; \

namespace engine
{

//------------------------------------------------------------------------------
//

template< int N >
struct TPin
{
    static const uint8_t bit    = 0;
    static const bool    pwm    = false;
    static const bool    analog = false;
};

//------------------------------------------------------------------------------
//

template< int N, int V >
struct FPinSetMode
{
    static EN_INLINE void eval()
    {
    }
};

//------------------------------------------------------------------------------
//

template< int N, int V >
struct FPinSetDigital
{
    static EN_INLINE void eval()
    {
    }
};

//------------------------------------------------------------------------------
//

template< int N >
struct FPinGetDigital
{
    static EN_INLINE uint8_t eval()
    {
        return uint8_t();
    }
};

//------------------------------------------------------------------------------
//

template< int N >
struct FPinSetAnalog
{
    static_assert( TPin< N >::pwm, "invalid pin: must support PWM" );

    static EN_INLINE void eval( const int16_t& value )
    {
    }
};

//------------------------------------------------------------------------------
//

template< int N >
struct FPinGetAnalog
{
    static EN_INLINE uint16_t eval()
    {
        // Delegate to standard function
        return analogRead( N );
    }
};

//------------------------------------------------------------------------------
//

template< int N, int V >
EN_INLINE void setMode()
{
    FPinSetMode< N, V >::eval();
}

//------------------------------------------------------------------------------
//

template< int N, int V >
EN_INLINE void setDigital()
{
    FPinSetDigital< N, V >::eval();
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE void setDigital( const uint8_t& value )
{
    if ( value == Low ) FPinSetDigital< N, Low >::eval();
    else                FPinSetDigital< N, High >::eval();
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE uint8_t getDigital()
{
    return FPinGetDigital< N >::eval();
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE void setAnalog( const uint16_t& value )
{
    FPinSetAnalog< N >::eval( value );
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE uint16_t getAnalog()
{
    return FPinGetAnalog< N >::eval();
}

} // engine

#endif // __AVR__

//------------------------------------------------------------------------------
//
#if defined( __AVR_ATmega328P__ ) || defined( __AVR_ATmega168__ )
#include "pins_atmega328p.hpp"
#endif

#endif // PINS_HPP
