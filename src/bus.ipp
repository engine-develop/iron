#ifndef BUS_IPP
#define BUS_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE BBus::BBus()
    : m_port( 0x0 )
{
}

//------------------------------------------------------------------------------
//

EN_INLINE BBus::~BBus()
{
}

//------------------------------------------------------------------------------
//

EN_INLINE void BBus::setPort( port_obj_t* port )
{
    m_port = port;
}

//------------------------------------------------------------------------------
//

EN_INLINE port_obj_t* BBus::port()
{
    return m_port;
}

//------------------------------------------------------------------------------
//

template< class S >
EN_INLINE Status BBus::signal( port_obj_t* port )
{
    typedef TSignal< S > traits_t;
    static_assert( traits_t::valid, "signal type not defined" );

    EN_ASSERT( port != 0x0 );

    // Write signal id
    //
    APort::write( port, traits_t::id[ 0 ] );
    APort::write( port, traits_t::id[ 1 ] );
    APort::write( port, traits_t::id[ 2 ] );
    APort::write( port, traits_t::id[ 3 ] );

    return Success;
}

//------------------------------------------------------------------------------
//

template< class S >
EN_INLINE Status BBus::wait( port_obj_t* port,
                             uint32_t timeout )
{
    typedef TSignal< S > traits_t;
    static_assert( traits_t::valid, "signal type not defined" );

    EN_ASSERT( port != 0x0 );

    static Timer tm( true );

    while ( 1 )
    {
        while ( APort::available( port ) > 0 )
        {
            uint8_t buf[ signal_size ];
            APort::read( port, buf, signal_size );

            if (    buf[ 0 ] == traits_t::id[ 0 ]
                 && buf[ 1 ] == traits_t::id[ 1 ]
                 && buf[ 2 ] == traits_t::id[ 2 ]
                 && buf[ 3 ] == traits_t::id[ 3 ] )
            {
                return Success;
            }
        }

        if ( tm.elapsed() > timeout ) return TimeOut;
    }

    return Error;
}

//------------------------------------------------------------------------------
//

template< class S >
EN_INLINE Status BBus::signal()
{
    if ( !m_port ) { return Error; }

    return signal< S >( m_port );
}

//------------------------------------------------------------------------------
//

template< class S >
EN_INLINE Status BBus::wait( uint32_t timeout )
{
    if ( !m_port ) { return Error; }

    return wait< S >( m_port, timeout );
}

//------------------------------------------------------------------------------
//

template< int A, class S >
EN_INLINE Status signal()
{
    return Bus< A >::get().template signal< S >();
}

//------------------------------------------------------------------------------
//

template< int A, class S >
EN_INLINE Status wait( uint32_t timeout )
{
    return Bus< A >::get().template wait< S >( timeout );
}

} // engine

#endif // BUS_IPP
