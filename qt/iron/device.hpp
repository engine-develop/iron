#ifndef DEVICE_HPP
#define DEVICE_HPP

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
#include "attribute.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEFINE_DEVICE( CNAME, S_ID, S_CONN, S_DCONN, NA ) \
    template< int A > class CNAME; \
    \
    template<> \
    struct TDevice< CNAME > \
    { \
        enum Signal \
        { \
            ID         = S_ID, \
            Connect    = S_CONN, \
            Disconnect = S_DCONN \
        }; \
    \
        static const uint16_t numAttributes = NA; \
    }; \

#define EN_DEVICE_CLASS( CNAME ) \
    template< int A > \
    struct CNAME : Device< CNAME > \

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int A > class D >
struct TDevice
{
    enum Signal
    {
        ID         = 0x0,
        Connect    = 0x0,
        Disconnect = 0x0
    };

    static const uint16_t numAttributes = 0;
};

//------------------------------------------------------------------------------
//

template< template< int A > class D >
struct BDevice
{
    typedef TDevice< D > traits_t;
    static const size_t nbytes = FAttributesBytes< D >::value;

    //------
    //

    EN_INLINE BDevice();

    EN_INLINE ~BDevice();

    //------
    // Attribute accessors & modifiers
    //

    template< int A >
    EN_INLINE void setDefault();

    EN_INLINE void setDefaults();

    template< int A, class T >
    EN_INLINE void set( const T& value );

    template< int A, class T >
    EN_INLINE void get( T& value ) const;

    EN_INLINE Status write() const;

    EN_INLINE Status read();

    //------
    //

    Connectivity state;
    uint8_t id;
    uint32_t baudrate;

    uint8_t buffer[ nbytes ];

};

//------------------------------------------------------------------------------
//

template< template< int A > class D, int A = CPU >
struct Device : BDevice< D >
{
};

} // engine

//------------------------------------------------------------------------------
//

#include "device.ipp"

#endif // DEVICE_HPP
