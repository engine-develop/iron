#ifndef PINS_MCU_HPP
#define PINS_MCU_HPP

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

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------
//

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
    static_assert( TPin< N >::pwm, "pin must support PWM" );

    static EN_INLINE void eval( const int16_t& value )
    {
    }
};

//------------------------------------------------------------------------------
//

template< int N >
struct FPinGetAnalog
{
    static EN_INLINE int16_t eval()
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
EN_INLINE uint8_t getDigital()
{
    return FPinGetDigital< N >::eval();
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE void setAnalog( const int16_t& value )
{
    FPinSetAnalog< N >::eval( value );
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE int16_t getAnalog()
{
    return FPinGetAnalog< N >::eval();
}

//------------------------------------------------------------------------------
// ATmega168
//

#if defined( __AVR_ATmega8__ )
#else

// Port B
//
EN_DEFINE_PIN( 8,  B, 0, false, false )
EN_DEFINE_PIN( 9,  B, 1, true,  false )
EN_DEFINE_PIN( 10, B, 2, true,  false )
EN_DEFINE_PIN( 11, B, 3, true,  false )
EN_DEFINE_PIN( 12, B, 4, false, false )
EN_DEFINE_PIN( 13, B, 5, false, false )
EN_DEFINE_PIN_PWM( 9,  TCCR1A, COM1A1, OCR1A )
EN_DEFINE_PIN_PWM( 10, TCCR1A, COM1B1, OCR1B )
EN_DEFINE_PIN_PWM( 11, TCCR2A, COM2A1, OCR2A )

// Port C
//
EN_DEFINE_PIN( A0, C, 0, false, true )
EN_DEFINE_PIN( A1, C, 1, false, true )
EN_DEFINE_PIN( A2, C, 2, false, true )
EN_DEFINE_PIN( A3, C, 3, false, true )
EN_DEFINE_PIN( A4, C, 4, false, true )
EN_DEFINE_PIN( A5, C, 5, false, true )

// Port D
//
EN_DEFINE_PIN( 0, D, 0, false, false )
EN_DEFINE_PIN( 1, D, 1, false, false )
EN_DEFINE_PIN( 2, D, 2, false, false )
EN_DEFINE_PIN( 3, D, 3, true,  false )
EN_DEFINE_PIN( 4, D, 4, false, false )
EN_DEFINE_PIN( 5, D, 5, true,  false )
EN_DEFINE_PIN( 6, D, 6, true,  false )
EN_DEFINE_PIN( 7, D, 7, false, false )
EN_DEFINE_PIN_PWM( 3, TCCR2A, COM2B1, OCR2B )
EN_DEFINE_PIN_PWM( 5, TCCR0A, COM0B1, OCR0B )
EN_DEFINE_PIN_PWM( 6, TCCR0A, COM0A1, OCR0A )

#endif // __AVR_ATmega8__

} // engine

#endif // PINS_MCU_HPP
