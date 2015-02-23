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
    if ( !port ) { return Error; }

    typedef TSignal< S > traits_t;
    static_assert( traits_t::valid, "signal type not defined" );

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
    if ( !port ) { return Error; }

    typedef TSignal< S > traits_t;
    static_assert( traits_t::valid, "signal type not defined" );

    Timer tm( true );

    while ( 1 )
    {
        // Read signal id
        //
        if ( APort::available( port ) > 0 )
        {
            uint8_t id0, id1, id2, id3;
            APort::read( port, id0 );
            APort::read( port, id1 );
            APort::read( port, id2 );
            APort::read( port, id3 );

            if ( id0 == traits_t::id[ 0 ]
              && id1 == traits_t::id[ 1 ]
              && id2 == traits_t::id[ 2 ]
              && id3 == traits_t::id[ 3 ] )
            {
                return Success;
            }
        }

        if ( tm.elapsed() > timeout ) return Error;
    }

    return Error;
}

//------------------------------------------------------------------------------
//

template< class S >
EN_INLINE Status BBus::signal()
{
    return signal< S >( m_port );
}

//------------------------------------------------------------------------------
//

template< class S >
EN_INLINE Status BBus::wait( uint32_t timeout )
{
    return wait< S >( m_port );
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
EN_INLINE Status wait( uint32_t timeout = uint32_t( -1 ) )
{
    return Bus< A >::get().template wait< S >( timeout );
}

} // engine

#endif // BUS_IPP
