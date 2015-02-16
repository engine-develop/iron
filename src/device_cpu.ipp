#ifndef DEVICE_CPU_IPP
#define DEVICE_CPU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Device< D, CPU >::Device()
    : m_port( 0x0 )
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Device< D, CPU >::~Device()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void Device< D, CPU >::setup( uint32_t baudrate )
{
    this->baudrate = baudrate;

    if ( m_port ) m_port->setBaudrate( this->baudrate );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void Device< D, CPU >::setPort( port_t* port )
{
    m_port = port;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE typename Device< D, CPU >::port_t* Device< D, CPU >::port()
{
    return m_port;
}

} // engine

#endif // DEVICE_CPU_IPP
