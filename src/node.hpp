#ifndef NODE_HPP
#define NODE_HPP

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

#define EN_NODE_CLASS( CNAME ) \
    template< int A = CPU > \
    struct CNAME \
        : BNode< CNAME, A > \

#define EN_DEFINE_TNODE( CNAME, DESC, CAT, ID_0, ID_1, ID_2, ID_3, NATTR ) \
    template<> \
    struct TNode< CNAME > \
    { \
        static const uint32_t id = EN_PACK4( ID_0, ID_1, ID_2, ID_3 ); \
        static const uint16_t numAttributes = NATTR; \
        static EN_INLINE const char* name()        { return EN_STRINGIZE( CNAME ); } \
        static EN_INLINE const char* description() { return DESC; } \
        static EN_INLINE const char* category()    { return CAT; } \
    }; \

#define EN_DEFINE_NODE_ATTR_I( S, I, ELEM, DATA ) \
    EN_DEFINE_ATTRIBUTE( \
        DATA, \
        I, \
        CHAOS_PP_TUPLE_ELEM( 5, 0, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 1, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 2, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 3, ELEM ), \
        CHAOS_PP_TUPLE_ELEM( 5, 4, ELEM ) \
    ) \

#define EN_DEFINE_NODE_ATTRS( CNAME, ATTRS ) \
    CHAOS_PP_EXPR( CHAOS_PP_SEQ_FOR_EACH_I( EN_DEFINE_NODE_ATTR_I, ATTRS, CNAME ) ) \

#define EN_DEFINE_NODE_E( CNAME, DESC, CAT, ID_0, ID_1, ID_2, ID_3, INFO, ATTRS ) \
    template< int > class CNAME; \
    \
    EN_DEFINE_TNODE( \
        CNAME, \
        DESC, \
        CAT, \
        ID_0, \
        ID_1, \
        ID_2, \
        ID_3, \
        CHAOS_PP_SEQ_SIZE( ATTRS ) \
    ) \
    \
    EN_DEFINE_NODE_ATTRS( CNAME, ATTRS ) \

#define EN_DEFINE_NODE( INFO, ATTRS ) \
    EN_DEFINE_NODE_E( \
        CHAOS_PP_TUPLE_ELEM( 7, 0, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 7, 1, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 7, 2, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 7, 3, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 7, 4, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 7, 5, INFO ), \
        CHAOS_PP_TUPLE_ELEM( 7, 6, INFO ), \
        INFO, \
        ATTRS \
    ) \

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int A > class D >
struct TNode
{
    static const uint32_t id = 0;
    static const uint16_t numAttributes = 0;
    static EN_INLINE const char* name()        { return ""; }
    static EN_INLINE const char* description() { return ""; }
    static EN_INLINE const char* category()    { return ""; }
};

//------------------------------------------------------------------------------
//

template< template< int A > class D, int A = CPU >
struct BNode
{

    enum { arch_t = A };
    typedef TNode< D > traits_t;
    static const uint32_t nAttrBytes = FAttributesBytes< D >::value;

    //----------
    //

    EN_INLINE BNode();

    EN_INLINE ~BNode();

    //----------
    // Fields
    //

    EN_INLINE uint8_t& state();

    //----------
    // Evaluation
    //

    EN_INLINE void setup();

    EN_INLINE void loop();

    //----------
    // Attributes
    //

    template< int AT >
    EN_INLINE void setDefault();

    EN_INLINE void setDefaults();

    template< int AT, int V >
    EN_INLINE void set();

    template< int AT, class T >
    EN_INLINE void set( const T& value );

    template< int AT, class T >
    EN_INLINE void get( T& value );

    template< int AT, int V >
    EN_INLINE bool is();

    template< int AT, class T >
    EN_INLINE bool is( const T& value );

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

#endif // NODE_HPP
