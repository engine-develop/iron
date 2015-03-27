#ifndef IR_VARIABLE_HPP
#define IR_VARIABLE_HPP

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
#include "types.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEFINE_VARIABLE( CNAME, TYPE, DESC, CAT ) \
    struct CNAME {}; \
    \
    template<> \
    struct TVariable< CNAME > \
    { \
        typedef TYPE type_t; \
        static EN_INLINE const char* name()        { return EN_STRINGIZE( CNAME ); } \
        static EN_INLINE const char* description() { return DESC; } \
        static EN_INLINE const char* category()    { return CAT; } \
    }; \
    \
    template<> \
    struct TVariableRev< TYPE > \
    { \
        typedef CNAME type_t; \
    }; \

namespace engine
{

//------------------------------------------------------------------------------
//

template< class T >
struct TVariable
{
    typedef int type_t;
    static EN_INLINE const char* name()        { return ""; }
    static EN_INLINE const char* description() { return ""; }
    static EN_INLINE const char* category()    { return ""; }
};

//------------------------------------------------------------------------------
//

template< class T >
struct TVariableRev
{
    typedef int type_t;
};

//------------------------------------------------------------------------------
//

EN_DEFINE_VARIABLE( Byte,  uint8_t,  "8-bit unsigned number",  "Variable" )
EN_DEFINE_VARIABLE( Int,   int16_t,  "16-bit number",          "Variable" )
EN_DEFINE_VARIABLE( Uint,  uint16_t, "16-bit unsigned number", "Variable" )
EN_DEFINE_VARIABLE( Long,  int32_t,  "32-bit number",          "Variable" )
EN_DEFINE_VARIABLE( Ulong, uint32_t, "32-bit unsigned number", "Variable" )
EN_DEFINE_VARIABLE( Float, float,    "32-bit decimal number",  "Variable" )

} // engine

#endif // IR_VARIABLE_HPP
