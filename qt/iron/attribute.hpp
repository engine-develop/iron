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

#define EN_DEFINE_ATTRIBUTES( CNAME, NUM ) \
    struct CNAME; \
    \
    template<> \
    struct TAttributes< CNAME > \
    { \
        static const uint8_t num = NUM; \
    }; \

#define EN_DEFINE_ATTRIBUTE( CNAME, I, NAME, TYPE, DVALUE ) \
    \
    template<> \
    struct TAttribute< CNAME, I > \
    { \
        static EN_INLINE const char* name(); \
        typedef TYPE type_t; \
        static const type_t dvalue = DVALUE; \
    }; \
    \
    EN_INLINE const char* TAttribute< Camera, I >::name() { return EN_PP_STRINGIZE( NAME ); } \

namespace engine
{

//------------------------------------------------------------------------------
//

//------------------------------------------------------------------------------
//

template< class T, int A >
struct TAttribute
{
    static EN_INLINE const char* name();
    typedef int type_t;
    static const type_t dvalue = type_t();
};

template< class T, int A >
EN_INLINE const char* TAttribute< T, A >::name() { return ""; }

//------------------------------------------------------------------------------
//

enum AttributeNames
{
};

template< class T >
struct TAttributes
{
    static const uint16_t num = 0;
};

//------------------------------------------------------------------------------
//

template< class T, int A, bool E = true >
struct IFAttributesBytes
{
    static const uint16_t value = 0;
};

template< class T, int A >
struct IFAttributesBytes< T, A, false >
{
    static const uint16_t value = sizeof( typename TAttribute< T, A >::type_t )
        + IFAttributesBytes< T, A+1, A+1 == TAttributes< T >::num >::value;
};

template< class T >
struct FAttributesBytes
    : IFAttributesBytes< T, 0, 0 == TAttributes< T >::num >
{
};

//------------------------------------------------------------------------------
//

template< class T, int A, int I, bool E = true >
struct IFAttributeOffset
{
    static const uint16_t value = 0;
};

template< class T, int A, int I >
struct IFAttributeOffset< T, A, I, false >
{
    static const uint16_t value = sizeof( typename TAttribute< T, I >::type_t )
        + IFAttributeOffset< T, A, I+1, I+1 == A || I+1 == TAttributes< T >::num >::value;
};

template< class T, int A >
struct FAttributeOffset
    : IFAttributeOffset< T, A, 0, 0 == A >
{
};

//------------------------------------------------------------------------------
//

template< class T, int A >
struct FAttributeRange
{
    static const uint16_t begin = FAttributeOffset< T, A >::value;
    static const uint16_t end   = begin + sizeof( typename TAttribute< T, A >::type_t );
};

//------------------------------------------------------------------------------
//

template< class V >
EN_INLINE void setAttribute( const V& value,
                             uint8_t* buffer );

//------------------------------------------------------------------------------
//

template< class V >
EN_INLINE void getAttribute( const uint8_t* buffer,
                             V& value );

//------------------------------------------------------------------------------
//

template< class T >
struct AttributeContainer
{
    typedef TAttributes< T > traits_t;
    static const uint32_t nbytes = FAttributesBytes< T >::value;

    //------
    //

    EN_INLINE AttributeContainer();

    EN_INLINE ~AttributeContainer();

    //------
    //

    template< int A, class V >
    EN_INLINE void set( const V& value );

    template< int A, class V >
    EN_INLINE void get( V& value ) const;

    //EN_INLINE void write();

    //------
    //

    uint8_t m_buffer[ nbytes ];

};

} // engine

//------------------------------------------------------------------------------
//

#include "attribute.ipp"

#endif // ATTRIBUTE_HPP
