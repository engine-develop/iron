#ifndef MCU_PINS_HPP
#define MCU_PINS_HPP

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

#define EN_DEFINE_PIN( N, P, BIT, PWM ) \
    template<> \
    struct TPin< N > \
    { \
        static const uint8_t bit = BIT; \
        static const bool pwm    = PWM; \
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
    struct FPinSet< N, HIGH > \
    { \
        static EN_INLINE void eval() \
        { \
            PORT##P |= ( 1 << TPin< N >::bit ); \
        } \
    }; \
    \
    template<> \
    struct FPinSet< N, LOW > \
    { \
        static EN_INLINE void eval() \
        { \
            PORT##P &= ~( 1 << TPin< N >::bit ); \
        } \
    }; \
    \
    template<> \
    struct FPinGet< N > \
    { \
        static EN_INLINE uint8_t eval() \
        { \
            return ( PIN##P & ( 1 << TPin< N >::bit ) ) ? HIGH : LOW; \
        } \
    }; \

#define EN_DEFINE_PIN_PWM( N, TCCR, COM, OCR ) \
    template<> \
    struct FPinSetA< N > \
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
    static const uint8_t bit = 0;
    static const bool pwm    = false;
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
struct FPinSet
{
    static EN_INLINE void eval()
    {
    }
};

//------------------------------------------------------------------------------
//

template< int N >
struct FPinSetA
{
    //static_assert( TPin< N >::pwm, "pin must support PWM" );

    static EN_INLINE void eval( const int16_t& value )
    {
    }
};

//------------------------------------------------------------------------------
//

template< int N >
struct FPinGet
{
    static EN_INLINE uint8_t eval()
    {
        return uint8_t();
    }
};

//------------------------------------------------------------------------------
//

template< int N >
struct FPinGetA
{
    static EN_INLINE int16_t eval()
    {
        return int16_t();
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
EN_INLINE void set()
{
    FPinSet< N, V >::eval();
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE void seta( const int16_t& value )
{
    FPinSetA< N >::eval( value );
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE uint8_t get()
{
    return FPinGet< N >::eval();
}

//------------------------------------------------------------------------------
//

template< int N >
EN_INLINE int16_t geta()
{
    //return FPinGetA< N >::eval();

    // Delegate to standard function
    return analogRead( N );
}

//------------------------------------------------------------------------------
// ATmega168
//

#if defined( __AVR_ATmega8__ )
#else

// Port B
//
EN_DEFINE_PIN( 8,  B, 0, false )
EN_DEFINE_PIN( 9,  B, 1, true  )
EN_DEFINE_PIN( 10, B, 2, true  )
EN_DEFINE_PIN( 11, B, 3, true  )
EN_DEFINE_PIN( 12, B, 4, false )
EN_DEFINE_PIN( 13, B, 5, false )
EN_DEFINE_PIN_PWM( 9,  TCCR1A, COM1A1, OCR1A )
EN_DEFINE_PIN_PWM( 10, TCCR1A, COM1B1, OCR1B )
EN_DEFINE_PIN_PWM( 11, TCCR2A, COM2A1, OCR2A )

// Port C
//
EN_DEFINE_PIN( A0, C, 0, false )
EN_DEFINE_PIN( A1, C, 1, false )
EN_DEFINE_PIN( A2, C, 2, false )
EN_DEFINE_PIN( A3, C, 3, false )
EN_DEFINE_PIN( A4, C, 4, false )
EN_DEFINE_PIN( A5, C, 5, false )

// Port D
//
EN_DEFINE_PIN( 0, D, 0, false )
EN_DEFINE_PIN( 1, D, 1, false )
EN_DEFINE_PIN( 2, D, 2, false )
EN_DEFINE_PIN( 3, D, 3, true  )
EN_DEFINE_PIN( 4, D, 4, false )
EN_DEFINE_PIN( 5, D, 5, true  )
EN_DEFINE_PIN( 6, D, 6, true  )
EN_DEFINE_PIN( 7, D, 7, false )
EN_DEFINE_PIN_PWM( 3, TCCR2A, COM2B1, OCR2B )
EN_DEFINE_PIN_PWM( 5, TCCR0A, COM0B1, OCR0B )
EN_DEFINE_PIN_PWM( 6, TCCR0A, COM0A1, OCR0A )

#endif // __AVR_ATmega8__

} // engine

#endif // MCU_PINS_HPP
