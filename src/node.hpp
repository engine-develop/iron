#ifndef IR_NODE_HPP
#define IR_NODE_HPP

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

// Engine
#include "utility.hpp"
#include "port.hpp"
#include "bus.hpp"
#include "attribute.hpp"

//------------------------------------------------------------------------------
//

#define IRON_NODE_CLASS( CNAME ) \
    struct CNAME \
        : BNode< CNAME > \

#define IRON_DEFINE_TNODE( CNAME, DESC, CAT, NATTR ) \
    template<> \
    struct TNode< CNAME > \
    { \
        static IRON_INLINE const char* name()        { return IRON_STRINGIZE( CNAME ); } \
        static IRON_INLINE const char* description() { return DESC; } \
        static IRON_INLINE const char* category()    { return CAT; } \
        static const uint16_t numAttributes = NATTR; \
    }; \

#define IRON_DEFINE_NODE_ATTR_I( S, I, ELEM, DATA ) \
    IRON_DEFINE_ATTRIBUTE( \
        DATA, \
        I, \
        CHAOS_PP_TUPLE_ELEM( 5, 0, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 1, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 2, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 3, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 4, ELEM ) \
    ) \

#define IRON_DEFINE_NODE_ATTRS( CNAME, ATTRS ) \
    CHAOS_PP_EXPR( CHAOS_PP_SEQ_FOR_EACH_I( IRON_DEFINE_NODE_ATTR_I, ATTRS, CNAME ) ) \

#define IRON_DEFINE_NODE_E( CNAME, DESC, CAT, INFO, ATTRS ) \
    class CNAME; \
    \
    IRON_DEFINE_TNODE( \
        CNAME, \
        DESC, \
        CAT, \
        CHAOS_PP_SEQ_SIZE( ATTRS ) \
    ) \
    \
    IRON_DEFINE_NODE_ATTRS( CNAME, ATTRS ) \

#define IRON_DEFINE_NODE( INFO, ATTRS ) \
    IRON_DEFINE_NODE_E( \
        CHAOS_PP_TUPLE_ELEM( 3, 0, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 3, 1, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 3, 2, INFO ), \
        INFO, \
        ATTRS \
    ) \

namespace engine
{

//------------------------------------------------------------------------------
//

template< class N >
struct TNode
{
    static IRON_INLINE const char* name()        { return ""; }
    static IRON_INLINE const char* description() { return ""; }
    static IRON_INLINE const char* category()    { return ""; }
    static const uint16_t numAttributes = 0;
};

//------------------------------------------------------------------------------
//

template< class N >
struct BNode
{

    typedef TNode< N > traits_t;
    static const uint32_t nAttrBytes = FAttributesBytes< N >::value;

    //----------
    //

    IRON_INLINE BNode();

    IRON_INLINE ~BNode();

    //----------
    // Fields
    //

    IRON_INLINE void setState( const uint8_t& state );

    IRON_INLINE uint8_t& state();

    //----------
    // Evaluation
    //

    IRON_INLINE void evaluate();

    //----------
    // Attributes
    //

    template< int AT >
    IRON_INLINE void setDefault();

    IRON_INLINE void setDefaults();

    template< int AT, int V >
    IRON_INLINE void set();

    template< int AT, class T >
    IRON_INLINE void set( const T& value );

    template< int AT, class T >
    IRON_INLINE void get( T& value );

    template< int AT, int V >
    IRON_INLINE bool is();

    template< int AT, class T >
    IRON_INLINE bool is( const T& value );

protected:

    //----------
    //

    uint8_t m_state;
    uint8_t m_attributes[ nAttrBytes ];

};

} // engine

//------------------------------------------------------------------------------
//

#include "node.ipp"

#endif // IR_NODE_HPP
