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
    template<> \
    struct TAttribute< CNAME, I > \
    { \
        static const bool valid = true; \
        static const uint8_t mode = MODE; \
        static EN_INLINE const char* name() { return EN_STRINGIZE( NAME ); } \
        typedef TYPE type_t; \
        static const type_t defaultValue = DVALUE; \
        static const uint8_t pin = PIN; \
        \
    }; \

namespace engine
{

//------------------------------------------------------------------------------
//

enum AttributeMode
{
    Input    = 0x0,
    Output   = 0x1,
    Internal = 0x2
};

//------------------------------------------------------------------------------
//

template< class N >
struct TNode;

//------------------------------------------------------------------------------
//

template< class N, int AT >
struct TAttribute
{
    static const bool valid = false;
    static const uint8_t mode = Input;
    static EN_INLINE const char* name() { return ""; }
    typedef uint8_t type_t;
    static const type_t defaultValue = type_t();
    static const uint8_t pin = None;
};

//------------------------------------------------------------------------------
//

template< class N, int AT, bool E = false >
struct IFAttributesCount
{
    static const uint16_t value = 0;
};

template< class N, int AT >
struct IFAttributesCount< N, AT, true >
{
    static const uint16_t value = 1
        + IFAttributesCount< N, AT+1, TAttribute< N, AT+1 >::valid >::value;
};

template< class N >
struct FAttributesCount
    : IFAttributesCount< N, 0, TAttribute< N, 0+1 >::valid >
{
};

//------------------------------------------------------------------------------
//

template< class N, int AT, bool E = true >
struct IFAttributesBytes
{
    static const uint32_t value = 0;
};

template< class N, int AT >
struct IFAttributesBytes< N, AT, false >
{
    static const uint32_t value = sizeof( typename TAttribute< N, AT >::type_t )
        + IFAttributesBytes< N, AT+1, AT+1 == TNode< N >::numAttributes >::value;
};

template< class N >
struct FAttributesBytes
    : IFAttributesBytes< N, 0, 0 == TNode< N >::numAttributes >
{
};

//------------------------------------------------------------------------------
//

template< class N, int AT, int I, bool E = true >
struct IFAttributeOffset
{
    static const uint32_t value = 0;
};

template< class N, int AT, int I >
struct IFAttributeOffset< N, AT, I, false >
{
    static const uint32_t value = sizeof( typename TAttribute< N, I >::type_t )
        + IFAttributeOffset< N, AT, I+1, I+1 == AT || I+1 == TNode< N >::numAttributes >::value;
};

template< class N, int AT >
struct FAttributeOffset
    : IFAttributeOffset< N, AT, 0, 0 == AT >
{
};

//------------------------------------------------------------------------------
//

template< class N, int AT >
struct FAttributeRange
{
    static const uint32_t begin = FAttributeOffset< N, AT >::value;
    static const uint32_t end   = begin + sizeof( typename TAttribute< N, AT >::type_t );
};

//------------------------------------------------------------------------------
//

template< class N, int AT >
struct FSetAttribute
{
    template< class T >
    static EN_INLINE void eval( uint8_t* buffer,
                                const T& value )
    {
        memcpy( buffer + FAttributeRange< N, AT >::begin,
                &value,
                sizeof( typename TAttribute< N, AT >::type_t ) );
    }
};

//------------------------------------------------------------------------------
//

template< class N, int AT >
struct FGetAttribute
{
    template< class T >
    static EN_INLINE T eval( const uint8_t* buffer )
    {
        T value = T();
        memcpy( &value,
                buffer + FAttributeRange< N, AT >::begin,
                sizeof( typename TAttribute< N, AT >::type_t ) );

        return value;
    }
};

//------------------------------------------------------------------------------
//

template< class N, int AT, bool E = true >
struct IFAttributesSetDefaults
{
    static EN_INLINE void eval( uint8_t* buffer )
    {
    }
};

template< class N, int AT >
struct IFAttributesSetDefaults< N, AT, false >
{
    static EN_INLINE void eval( uint8_t* buffer )
    {
        typename TAttribute< N, AT >::type_t value( TAttribute< N, AT >::defaultValue );
        FSetAttribute< N, AT >::eval( buffer, value );

        IFAttributesSetDefaults< N, AT+1, AT+1 == TNode< N >::numAttributes >::eval( buffer );
    }
};

template< class N >
struct FAttributesSetDefaults
    : IFAttributesSetDefaults< N, 0, 0 == TNode< N >::numAttributes >
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

template< class N, int AT >
struct IsAttributePinSettable
    : IIsAttributePinSettable< TAttribute< N, AT >::mode,
                               TAttribute< N, AT >::pin >
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

template< class N, int AT >
struct IsAttributePinGettable
    : IIsAttributePinGettable< TAttribute< N, AT >::mode,
                               TAttribute< N, AT >::pin >
{
};

//------------------------------------------------------------------------------
//
#ifdef __AVR__
template< class N, int AT, bool IN = true >
struct IFAttributeSetPinMode
{
    static EN_INLINE void eval()
    {
    }
};

template< class N, int AT >
struct IFAttributeSetPinMode< N, AT, false >
{
    static EN_INLINE void eval()
    {
        setMode< TAttribute< N, AT >::pin, TAttribute< N, AT >::mode >();
    }
};

template< class N, int AT, bool E = true >
struct IFAttributesSetPinModes
{
    static EN_INLINE void eval()
    {
    }
};

template< class N, int AT >
struct IFAttributesSetPinModes< N, AT, false >
{
    static EN_INLINE void eval()
    {
        IFAttributeSetPinMode< N, AT, TAttribute< N, AT >::mode == Internal
                                || TAttribute< N, AT >::pin == None >::eval();

        IFAttributesSetPinModes< N, AT+1, AT+1 == TNode< N >::numAttributes >::eval();
    }
};

template< class N >
struct FAttributesSetPinModes
    : IFAttributesSetPinModes< N, 0, 0 == TNode< N >::numAttributes >
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

template< class N, int AT >
struct FAttributeSetPin
    : IFAttributeSetPin< TAttribute< N, AT >::pin,
                         TPin< TAttribute< N, AT >::pin >::analog,
                         IsAttributePinSettable< N, AT >::value >
{
};
#endif // __AVR__

//------------------------------------------------------------------------------
//
#ifdef __AVR__
template< class N, int AT, int P, bool AN, bool SET = false >
struct IFAttributeGetPin
{
    template< class T >
    static EN_INLINE void eval( T& value, uint8_t* buffer )
    {
    }
};

template< class N, int AT, int P >
struct IFAttributeGetPin< N, AT, P, true, true >
{
    template< class T >
    static EN_INLINE void eval( T& value, uint8_t* buffer )
    {
        value = getAnalog< P >();

        FSetAttribute< N, AT >::eval( buffer, value );
    }
};

template< class N, int AT, int P >
struct IFAttributeGetPin< N, AT, P, false, true >
{
    template< class T >
    static EN_INLINE void eval( T& value, uint8_t* buffer )
    {
        value = getDigital< P >();

        FSetAttribute< N, AT >::eval( buffer, value );
    }
};

template< class N, int AT >
struct FAttributeGetPin
    : IFAttributeGetPin< N, AT,
                         TAttribute< N, AT >::pin,
                         TPin< TAttribute< N, AT >::pin >::analog,
                         IsAttributePinGettable< N, AT >::value >
{
};
#endif // __AVR__

} // engine

#endif // ATTRIBUTE_HPP
