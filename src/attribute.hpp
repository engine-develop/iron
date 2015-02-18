#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

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
#include <string.h>

// Engine
#include "utility.hpp"
#include "pins.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEFINE_ATTRIBUTE( CNAME, I, MODE, NAME, TYPE, DVALUE, PIN ) \
    enum CNAME ## _ ## ATTRIBUTE ## _ ## I { CNAME ## _ ## NAME = I }; \
    \
    template< int A > class CNAME; \
    \
    template<> \
    struct TAttribute< CNAME, I > \
    { \
        static const bool valid = true; \
        static const uint8_t mode = MODE; \
        static EN_INLINE const char* name(); \
        typedef TYPE type_t; \
        static const type_t defaultValue = DVALUE; \
        static const uint8_t pin = PIN; \
        \
    }; \
    \
    EN_INLINE const char* TAttribute< CNAME, I >::name() { return EN_STRINGIZE( NAME ); } \

namespace engine
{

//------------------------------------------------------------------------------
//

enum AttributeMode
{
    Input       = 0x0,
    Output      = 0x1,
    Internal    = 0x2
};

//------------------------------------------------------------------------------
//

template< template< int A > class D >
struct TDevice;

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT >
struct TAttribute
{
    static const bool valid = false;
    static const uint8_t mode = Input;
    static EN_INLINE const char* name();
    typedef uint8_t type_t;
    static const type_t defaultValue = type_t();
    static const uint8_t pin = None;
};

template< template< int > class D, int AT >
EN_INLINE const char* TAttribute< D, AT >::name() { return ""; }

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT, bool E = false >
struct IFAttributesCount
{
    static const uint16_t value = 0;
};

template< template< int > class D, int AT >
struct IFAttributesCount< D, AT, true >
{
    static const uint16_t value = 1
        + IFAttributesCount< D, AT+1, TAttribute< D, AT+1 >::valid >::value;
};

template< template< int > class D >
struct FAttributesCount
    : IFAttributesCount< D, 0, TAttribute< D, 0+1 >::valid >
{
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT, bool E = true >
struct IFAttributesBytes
{
    static const uint32_t value = 0;
};

template< template< int > class D, int AT >
struct IFAttributesBytes< D, AT, false >
{
    static const uint32_t value = sizeof( typename TAttribute< D, AT >::type_t )
        + IFAttributesBytes< D, AT+1, AT+1 == TDevice< D >::numAttributes >::value;
};

template< template< int > class D >
struct FAttributesBytes
    : IFAttributesBytes< D, 0, 0 == TDevice< D >::numAttributes >
{
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT, int I, bool E = true >
struct IFAttributeOffset
{
    static const uint32_t value = 0;
};

template< template< int > class D, int AT, int I >
struct IFAttributeOffset< D, AT, I, false >
{
    static const uint32_t value = sizeof( typename TAttribute< D, I >::type_t )
        + IFAttributeOffset< D, AT, I+1, I+1 == AT || I+1 == TDevice< D >::numAttributes >::value;
};

template< template< int > class D, int AT >
struct FAttributeOffset
    : IFAttributeOffset< D, AT, 0, 0 == AT >
{
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT >
struct FAttributeRange
{
    static const uint32_t begin = FAttributeOffset< D, AT >::value;
    static const uint32_t end   = begin + sizeof( typename TAttribute< D, AT >::type_t );
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT >
struct FSetAttribute
{
    template< class T >
    static EN_INLINE void eval( uint8_t* buffer,
                                const T& value )
    {
        memcpy( buffer + FAttributeRange< D, AT >::begin,
                &value,
                sizeof( typename TAttribute< D, AT >::type_t ) );
    }
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT >
struct FGetAttribute
{
    template< class T >
    static EN_INLINE T eval( const uint8_t* buffer )
    {
        T value = T();
        memcpy( &value,
                buffer + FAttributeRange< D, AT >::begin,
                sizeof( typename TAttribute< D, AT >::type_t ) );

        return value;
    }
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int AT, bool E = true >
struct IFAttributesSetDefaults
{
    static EN_INLINE void eval( uint8_t* buffer )
    {
    }
};

template< template< int > class D, int AT >
struct IFAttributesSetDefaults< D, AT, false >
{
    static EN_INLINE void eval( uint8_t* buffer )
    {
        typename TAttribute< D, AT >::type_t value( TAttribute< D, AT >::defaultValue );
        FSetAttribute< D, AT >::eval( buffer, value );

        IFAttributesSetDefaults< D, AT+1, AT+1 == TDevice< D >::numAttributes >::eval( buffer );
    }
};

template< template< int > class D >
struct FAttributesSetDefaults
    : IFAttributesSetDefaults< D, 0, 0 == TDevice< D >::numAttributes >
{
};

//------------------------------------------------------------------------------
//

template< int M, int P = None >
struct IIsAttributePinSettable
{
    static const bool value = false;
};

template< int P >
struct IIsAttributePinSettable< Output, P >
{
    static const bool value = true;
};

template< template< int > class D, int AT >
struct IsAttributePinSettable
    : IIsAttributePinSettable< TAttribute< D, AT >::mode,
                               TAttribute< D, AT >::pin >
{
};

//------------------------------------------------------------------------------
//

template< int M, int P = None >
struct IIsAttributePinGettable
{
    static const bool value = false;
};

template< int P >
struct IIsAttributePinGettable< Input, P >
{
    static const bool value = true;
};

template< template< int > class D, int AT >
struct IsAttributePinGettable
    : IIsAttributePinGettable< TAttribute< D, AT >::mode,
                               TAttribute< D, AT >::pin >
{
};

//------------------------------------------------------------------------------
//
#ifdef __AVR__
template< template< int > class D, int AT, bool IN = true >
struct IFAttributeSetPinMode
{
    static EN_INLINE void eval()
    {
    }
};

template< template< int > class D, int AT >
struct IFAttributeSetPinMode< D, AT, false >
{
    static EN_INLINE void eval()
    {
        setMode< TAttribute< D, AT >::pin, TAttribute< D, AT >::mode >();
    }
};

template< template< int > class D, int AT, bool E = true >
struct IFAttributesSetPinModes
{
    static EN_INLINE void eval()
    {
    }
};

template< template< int > class D, int AT >
struct IFAttributesSetPinModes< D, AT, false >
{
    static EN_INLINE void eval()
    {
        IFAttributeSetPinMode< D, AT, TAttribute< D, AT >::mode == Internal
                                || TAttribute< D, AT >::pin == None >::eval();

        IFAttributesSetPinModes< D, AT+1, AT+1 == TDevice< D >::numAttributes >::eval();
    }
};

template< template< int > class D >
struct FAttributesSetPinModes
    : IFAttributesSetPinModes< D, 0, 0 == TDevice< D >::numAttributes >
{
};
#endif // __AVR__

//------------------------------------------------------------------------------
//
#ifdef __AVR__
template< int N, bool AN, bool SET = false >
struct IFAttributeSetPin
{
    template< int V >
    static EN_INLINE void eval()
    {
    }

    template< class T >
    static EN_INLINE void eval( const T& value )
    {
    }
};

template< int N >
struct IFAttributeSetPin< N, true, true >
{
    template< int V >
    static EN_INLINE void eval()
    {
        setAnalog< N >( int16_t( V ) );
    }

    template< class T >
    static EN_INLINE void eval( const T& value )
    {
        setAnalog< N >( value );
    }
};

template< int N >
struct IFAttributeSetPin< N, false, true >
{
    template< int V >
    static EN_INLINE void eval()
    {
        setDigital< N, V >();
    }

    template< class T >
    static EN_INLINE void eval( const T& value )
    {
        setDigital< N >( value );
    }
};

template< template< int > class D, int AT >
struct FAttributeSetPin
    : IFAttributeSetPin< TAttribute< D, AT >::pin,
                         TPin< TAttribute< D, AT >::pin >::analog,
                         IsAttributePinSettable< D, AT >::value >
{
};
#endif // __AVR__

//------------------------------------------------------------------------------
//
#ifdef __AVR__
template< template< int > class D, int AT, int N, bool AN, bool SET = false >
struct IFAttributeGetPin
{
    template< class T >
    static EN_INLINE void eval( T& value, uint8_t* buffer )
    {
    }
};

template< template< int > class D, int AT, int N >
struct IFAttributeGetPin< D, AT, N, true, true >
{
    template< class T >
    static EN_INLINE void eval( T& value, uint8_t* buffer )
    {
        value = getAnalog< N >();

        FSetAttribute< D, AT >::eval( buffer, value );
    }
};

template< template< int > class D, int AT, int N >
struct IFAttributeGetPin< D, AT, N, false, true >
{
    template< class T >
    static EN_INLINE void eval( T& value, uint8_t* buffer )
    {
        value = getDigital< N >();

        FSetAttribute< D, AT >::eval( buffer, value );
    }
};

template< template< int > class D, int AT >
struct FAttributeGetPin
    : IFAttributeGetPin< D, AT,
                         TAttribute< D, AT >::pin,
                         TPin< TAttribute< D, AT >::pin >::analog,
                         IsAttributePinGettable< D, AT >::value >
{
};
#endif // __AVR__

} // engine

#endif // ATTRIBUTE_HPP
