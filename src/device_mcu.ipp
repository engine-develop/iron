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
EN_INLINE void Device< D, MCU >::setup()
{
    FAttributesSetPinModes< D >::eval();
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE typename Device< D, MCU >::port_t& Device< D, MCU >::port()
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
        case Device< D, MCU >::traits_t::ID:
            Serial.write( Device< D, MCU >::traits_t::ID );
            break;
        case Device< D, MCU >::traits_t::Connect:
            this->state = Connected;
            break;
        default:
            break;
    }

    return ( this->state != Connected );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE bool Device< D, MCU >::waitDisconnect()
{
    switch ( Serial.read() )
    {
        case Device< D, MCU >::traits_t::ID:
            Serial.write( Device< D, MCU >::traits_t::ID );
            break;
        case Device< D, MCU >::traits_t::Disconnect:
            this->state = Disconnected;
            break;
        default:
            break;
    }

    return ( this->state != Disconnected );
}

} // engine

#endif // DEVICE_MCU_IPP
