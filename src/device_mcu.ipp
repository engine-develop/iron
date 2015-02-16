#ifndef DEVICE_MCU_IPP
#define DEVICE_MCU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Device< D, MCU >::Device()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Device< D, MCU >::~Device()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void Device< D, MCU >::setup( uint32_t baudrate )
{
    this->baudrate = baudrate;

    Serial.begin( this->baudrate );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE port_t& Device< D, MCU >::port()
{
    return Serial;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE bool Device< D, MCU >::waitConnect()
{
    switch ( Serial.read() )
    {
        case traits_t::ID:
            Serial.write( traits_t::ID );
            break;
        case traits_t::Connect:
            state = Connected;
            break;
        default:
            break;
    }

    return ( state != Connected );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE bool Device< D, MCU >::waitDisconnect()
{
    switch ( Serial.read() )
    {
        case traits_t::ID:
            Serial.write( traits_t::ID );
            break;
        case traits_t::Disconnect:
            state = Disconnected;
            break;
        default:
            break;
    }

    return ( state != Disconnected );
}

} // engine

#endif // DEVICE_MCU_IPP
