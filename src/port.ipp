#ifndef IR_PORT_IPP
#define IR_PORT_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

IRON_INLINE void APort::close( port_obj_t* port )
{
#ifdef __AVR__
    port->flush();
    port->end();
#else
    port->close();
#endif
}

//------------------------------------------------------------------------------
//

IRON_INLINE void APort::setBaudrate( port_obj_t* port,
                                     const uint32_t& baudrate )
{
#ifdef __AVR__
    port->begin( baudrate );
#else
    port->setBaudrate( baudrate );
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

IRON_INLINE uint32_t APort::available( port_obj_t* port )
{
    return port->available();
}

//------------------------------------------------------------------------------
//

IRON_INLINE size_t APort::write( port_obj_t* port,
                                 const uint8_t* buffer,
                                 size_t size )
{
    return port->write( buffer, size );
}

//------------------------------------------------------------------------------
//

template< class T >
IRON_INLINE void APort::write( port_obj_t* port,
                               const T& value )
{
    port->write( &value, sizeof( T ) );
}

//------------------------------------------------------------------------------
//

template< class T >
IRON_INLINE void APort::read( port_obj_t* port,
                              T& value )
{
#ifdef __AVR__
    value = port->read();
#else
    port->read( &value, sizeof( T ) );
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

IRON_INLINE size_t APort::read( port_obj_t* port,
                                uint8_t* buffer,
                                size_t size )
{
#ifdef __AVR__
    return port->readBytes( reinterpret_cast< char* >( buffer ), size );
#else
    return port->read( buffer, size );
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

template< int S >
IRON_INLINE PortBuffer< S >::PortBuffer( port_obj_t* port_ )
    : port( port_ )
    , i( 0 )
{
    reset();
}

//------------------------------------------------------------------------------
//

template< int S >
IRON_INLINE void PortBuffer< S >::reset()
{
    i = 0;
}

//------------------------------------------------------------------------------
//

template< int S >
IRON_INLINE void PortBuffer< S >::write()
{
    APort::write( data, S );
}

//------------------------------------------------------------------------------
//

template< int S >
IRON_INLINE void PortBuffer< S >::read()
{
    while ( APort::available( port ) > 0 && i < S )
    {
        APort::read( port, data[ i++ ] );
    }
}

} // engine

#endif // IR_PORT_IPP
