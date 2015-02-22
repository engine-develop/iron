#ifndef PORT_IPP
#define PORT_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE uint32_t APort::available( port_obj_t* port )
{
    return port->available();
}

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void APort::write( port_obj_t* port,
                             const T& value )
{
    port->write( &value, sizeof( T ) );
}

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void APort::read( port_obj_t* port,
                            T& value )
{
#ifdef __AVR__
    value = port->read();
#else
    port->read( &value, sizeof( T ) );
#endif // __AVR__
}

} // engine

#endif // PORT_IPP
