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
#include "port.hpp"
#include "bus.hpp"
#include "attribute.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEFINE_DEVICE( CNAME, DESC, ID_0, ID_1, ID_2, ID_3, NATTR ) \
    template< int A > class CNAME; \
    \
    template<> \
    struct TDevice< CNAME > \
    { \
        static EN_INLINE const char* name(); \
        static EN_INLINE const char* description(); \
        static const uint32_t id = EN_PACK4( ID_0, ID_1, ID_2, ID_3 ); \
        static const uint16_t numAttributes = NATTR; \
    }; \
    \
    EN_INLINE const char* TDevice< CNAME >::name() { return EN_STRINGIZE( CNAME ); } \
    \
    EN_INLINE const char* TDevice< CNAME >::description() { return DESC; } \

#define EN_DEVICE_CLASS( CNAME ) \
    template< int A = CPU > \
    class CNAME \
        : public BDevice< CNAME, A > \

#define EN_REGISTER_DEVICE( CNAME ) \
    static const Status CNAME ## _ ## status = TypeStore< Types_Device >::get().registerType( new DeviceType< CNAME >() ); \

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int A > class D >
struct TDevice
{
    static EN_INLINE const char* name();
    static EN_INLINE const char* description();
    static const uint32_t id = 0;
    static const uint16_t numAttributes = 0;
};

template< template< int > class D >
EN_INLINE const char* TDevice< D >::name() { return ""; }

template< template< int > class D >
EN_INLINE const char* TDevice< D >::description() { return ""; }

//------------------------------------------------------------------------------
//

template< template< int A > class D, int A = CPU >
class BDevice
{

public:

    enum { Arch = A };
    typedef TDevice< D > traits_t;
    static const uint32_t nAttrBytes = FAttributesBytes< D >::value;

    //------
    //

    EN_INLINE BDevice();

    EN_INLINE ~BDevice();

    //------
    // Fields
    //

    uint8_t& state();

    EN_INLINE void setPort( port_obj_t* port );

    EN_INLINE port_obj_t* port();

    //------
    // Evaluation
    //

    EN_INLINE void setup();

    EN_INLINE Status preEvaluate();

    EN_INLINE Status evaluate();

    //------
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

    //------
    //

    uint8_t m_state;
    port_obj_t* m_port;
    uint8_t m_attributes[ nAttrBytes ];

};

} // engine

//------------------------------------------------------------------------------
//

#include "device.ipp"

#endif // DEVICE_HPP
