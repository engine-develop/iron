#ifndef CPU_DEVICE_IPP
#define CPU_DEVICE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE BDevice< P, CPU >::BDevice()
    : state( Disconnected )
    , id( 0 )
    , baudrate( 9600 )
    , port( 0x0 )
{
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE BDevice< P, CPU >::~BDevice()
{
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
size_t BDevice< P, CPU >::write( const T& value )
{
    return port->write( value );
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
size_t BDevice< P, CPU >::write( const T* buffer,
                                 size_t size )
{
    return port->write( buffer, size );
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
void BDevice< P, CPU >::read( T& value )
{
    port->read( value );
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
void BDevice< P, CPU >::read( T* buffer,
                              size_t size )
{
    port->read( buffer, size );
}

} // engine

#endif // CPU_DEVICE_IPP
