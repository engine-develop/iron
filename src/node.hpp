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

//------------------------------------------------------------------------------
//

#define EN_DEFINE_NODE( CNAME, CODE ) \
    template<> \
    struct TNode< CNAME > \
    { \
        static EN_INLINE const char* code() \
        { \
            return EN_STRING( CHAOS_PP_SEQ_ELEM( 0, CODE ) ); \
        } \
    }; \
    \
    template<> \
    struct FNodeEvaluate< CNAME > \
    { \
        static EN_INLINE void eval() \
        { \
            CHAOS_PP_SEQ_ELEM( 0, CODE ) \
        } \
    }; \

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
struct TNode
{
    static EN_INLINE const char* code() { return ""; }
};

//------------------------------------------------------------------------------
//

template< template< int > class D >
struct FNodeEvaluate
{
    static EN_INLINE void eval() {}
};

} // engine

#endif // NODE_HPP
