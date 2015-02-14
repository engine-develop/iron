#ifndef CPU_DEVICE_IPP
#define CPU_DEVICE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE BDevice< D, CPU >::BDevice()
    : state( Disconnected )
    , id( 0 )
    , baudrate( 9600 )
    , port( 0x0 )
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE BDevice< D, CPU >::~BDevice()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< class T >
size_t BDevice< D, CPU >::write( const T& value )
{
    return port->write( value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< class T >
size_t BDevice< D, CPU >::write( const T* buffer,
                                 size_t size )
{
    return port->write( buffer, size );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< class T >
void BDevice< D, CPU >::read( T& value )
{
    port->read( value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< class T >
void BDevice< D, CPU >::read( T* buffer,
                              size_t size )
{
    port->read( buffer, size );
}

} // engine

#endif // CPU_DEVICE_IPP
