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

//------------------------------------------------------------------------------
//

#define EN_DEFINE_ATTRIBUTE( CNAME, I, NAME, TYPE, DVALUE ) \
    \
    template<> \
    struct TAttribute< CNAME, I > \
    { \
        static EN_INLINE const char* name(); \
        typedef TYPE type_t; \
        static const type_t defaultValue = DVALUE; \
    }; \
    \
    EN_INLINE const char* TAttribute< CNAME, I >::name() { return EN_STRINGIZE( NAME ); } \

namespace engine
{

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void setAttribute( uint8_t* buffer,
                             const T& value );

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void getAttribute( const uint8_t* buffer,
                             T& value );

//------------------------------------------------------------------------------
//

template< template< int A > class D >
struct TDevice;

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
struct TAttribute
{
    static EN_INLINE const char* name();
    typedef int type_t;
    static const type_t defaultValue = type_t();
};

template< template< int > class D, int A >
EN_INLINE const char* TAttribute< D, A >::name() { return ""; }

//------------------------------------------------------------------------------
//

template< template< int > class D, int A, bool E = true >
struct IFAttributesBytes
{
    static const uint16_t value = 0;
};

template< template< int > class D, int A >
struct IFAttributesBytes< D, A, false >
{
    static const uint16_t value = sizeof( typename TAttribute< D, A >::type_t )
        + IFAttributesBytes< D, A+1, A+1 == TDevice< D >::numAttributes >::value;
};

template< template< int > class D >
struct FAttributesBytes
    : IFAttributesBytes< D, 0, 0 == TDevice< D >::numAttributes >
{
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int A, int I, bool E = true >
struct IFAttributeOffset
{
    static const uint16_t value = 0;
};

template< template< int > class D, int A, int I >
struct IFAttributeOffset< D, A, I, false >
{
    static const uint16_t value = sizeof( typename TAttribute< D, I >::type_t )
        + IFAttributeOffset< D, A, I+1, I+1 == A || I+1 == TDevice< D >::numAttributes >::value;
};

template< template< int > class D, int A >
struct FAttributeOffset
    : IFAttributeOffset< D, A, 0, 0 == A >
{
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
struct FAttributeRange
{
    static const uint16_t begin = FAttributeOffset< D, A >::value;
    static const uint16_t end   = begin + sizeof( typename TAttribute< D, A >::type_t );
};

//------------------------------------------------------------------------------
//

template< template< int > class D, int A, bool E = true >
struct IFAttributesSetDefaults
{
    static EN_INLINE void eval( uint8_t* buffer )
    {
    }
};

template< template< int > class D, int A >
struct IFAttributesSetDefaults< D, A, false >
{
    static EN_INLINE void eval( uint8_t* buffer )
    {
        setAttribute( buffer + FAttributeRange< D, A >::begin,
                      TAttribute< D, A >::defaultValue );

        IFAttributesSetDefaults< D, A+1, A+1 == TDevice< D >::numAttributes >::eval( buffer );
    }
};

template< template< int > class D >
struct FAttributesSetDefaults
    : IFAttributesSetDefaults< D, 0, 0 == TDevice< D >::numAttributes >
{
};

} // engine

//------------------------------------------------------------------------------
//

#include "attribute.ipp"

#endif // ATTRIBUTE_HPP
