#ifndef SIGNAL_HPP
#define SIGNAL_HPP

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

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEFINE_SIGNAL( CNAME, NAME, DESC, ID_0, ID_1, ID_2, ID_3 ) \
    enum CNAME ## _ ## TSIGNAL ## _ ## NAME { NAME = ID_0 }; \
    \
    template<> \
    struct TSignal< CNAME, NAME > \
    { \
        static const bool valid = true; \
        static EN_INLINE const char* name(); \
        static EN_INLINE const char* description(); \
        static const uint32_t id = EN_PACK4( ID_0, ID_1, ID_2, ID_3 ); \
    }; \
    \
    EN_INLINE const char* TSignal< NAME >::name() { return EN_STRINGIZE( NAME ); } \
    \
    EN_INLINE const char* TSignal< NAME >::description() { return DESC; } \

namespace engine
{

//------------------------------------------------------------------------------
//

enum Signal
{
    Signal_ID         = EN_PACK4( 0x2B, 0x43, 0x6,  0xD  ),
    Signal_Connect    = EN_PACK4( 0x3,  0x16, 0x93, 0x63 ),
    Signal_Disconnect = EN_PACK4( 0x5B, 0x4C, 0x1F, 0x19 ),
    Signal_Write      = EN_PACK4( 0x3E, 0x3A, 0x59, 0x11 ),
    Signal_Read       = EN_PACK4( 0x21, 0x31, 0x56, 0x8E )
};

//------------------------------------------------------------------------------
//

template< template< int A > class D, int S >
struct TSignal
{
    static const bool valid = false;
    static EN_INLINE const char* name();
    static EN_INLINE const char* description();
    static const uint32_t id = 0;
};

template< template< int A > class D, int S >
EN_INLINE const char* TSignal< D, S >::name() { return ""; }

template< template< int A > class D, int S >
EN_INLINE const char* TSignal< D, S >::description() { return ""; }

//------------------------------------------------------------------------------
//

template< template< int > class D, int S, class P >
EN_INLINE void signal( P* port )
{
    typedef TSignal< D, S > traits_t;

    static_assert( traits_t::valid, "signal type not defined" );

    // Write signal id, MSB format
    //
    uint8_t id0, id1, id2, id3;
    EN_UPACK4( traits_t::id, id0, id1, id2, id3 );

    port->write( id0 );
    port->write( id1 );
    port->write( id2 );
    port->write( id3 );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int S, class P >
EN_INLINE bool wait( P* port )
{
    typedef TSignal< D, S > traits_t;

    static_assert( traits_t::valid, "signal type not defined" );

    // Read signal id, MSB format
    //
    if ( port->available() )
    {
        uint8_t id0 = port->read();
        uint8_t id1 = port->read();
        uint8_t id2 = port->read();
        uint8_t id3 = port->read();
        uint32_t id = EN_PACK4( id0, id1, id2, id3 );

        if ( id == traits_t::id )
        {
            // set status

            return false;
        }
    }

    return true;
}

} // engine

#endif // SIGNAL_HPP
