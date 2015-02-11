#ifndef BUS_HPP
#define BUS_HPP

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
//#include <cstring>

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEFINE_BUS_PROTOCOL( NAME, HS, S_DEV_READY, S_HOST_CONN, S_HOST_DCONN ) \
    struct NAME; \
    \
    template<> \
    struct TBus< NAME > \
    { \
        static const uint8_t headerSize = HS; \
    \
        enum Signal \
        { \
            Device_Ready    = S_DEV_READY, \
            Host_Connect    = S_HOST_CONN, \
            Host_Disconnect = S_HOST_DCONN \
        }; \
    }; \

namespace engine
{

//------------------------------------------------------------------------------
//

enum Bus_Status
{
    Bus_Status_Error        = 0,
    Bus_Status_Ok           = 1,
    Bus_Status_Connected    = 2,
    Bus_Status_Disconnected = 3
};

//------------------------------------------------------------------------------
//

template< class P >
struct TBus
{
    static const uint8_t headerSize = 16;

    enum Signal
    {
        Device_Ready    = 0x0,
        Host_Connect    = 0x0,
        Host_Disconnect = 0x0
    };
};

//------------------------------------------------------------------------------
//
#if 0
template< class P >
struct BusHeader
{
    typedef TBus< P > traits_t;

    EN_INLINE BusHeader();

    EN_INLINE ~BusHeader();

    //------

    EN_INLINE unsigned char* data();

    EN_INLINE void reset();

    EN_INLINE bool set( char* header );

    EN_INLINE bool set( char* begin,
                        char* end );

    //------

    EN_INLINE void setResolution( const uint16_t& rx,
                                  const uint16_t& ry );

    EN_INLINE uint16_t resolutionX();

    EN_INLINE uint16_t resolutionY();

    //------

    unsigned char m_data[ traits_t::headerSize ];
};
#endif
//------------------------------------------------------------------------------
//

template< class P, int A >
struct BBusDevice
{
};

//------------------------------------------------------------------------------
//

template< class P, int A >
struct BusDevice : BBusDevice< P, A >
{
};

//------------------------------------------------------------------------------
//

struct BBus
{
    static EN_INLINE Bus_Status status();

    static Bus_Status s_status;
};

//------------------------------------------------------------------------------
//

template< class P, int A >
struct Bus : BBus
{
    typedef TBus< P > traits_t;
};

} // engine

//------------------------------------------------------------------------------
//

#include "bus.ipp"

#endif // BUS_HPP
