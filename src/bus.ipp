#ifndef BUS_CPU_IPP
#define BUS_CPU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Bus< D >::~Bus()
{
    release();
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Bus< D >& Bus< D >::get()
{
    static Bus< D > b;

    return b;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void Bus< D >::release()
{
    for ( typename std::vector< D< CPU > >::iterator it
            = devices().begin(); it != devices().end(); ++it )
    {
        disconnect( *it );
    }

    m_devices.clear();
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE std::vector< D< CPU > >& Bus< D >::scan()
{
    release();

    std::vector< PortInfo > devices_i = list_ports();

    for ( std::vector< PortInfo >::const_iterator it
            = devices_i.begin(); it != devices_i.end(); ++it )
    {
        EN_DEBUG( "Opening port: %s\n", it->port.c_str() );

        Serial port = new Serial( it->port,
                                  9600,
                                  Timeout::simpleTimeout( 1000 ) ) );

        // Failed to open port
        //
        if ( !port->isOpen() )
        {
            EN_DEBUG( "Error: Failed to open port\n" );

            delete port;

            continue;
        }

        // Request ID
        //
        signal< D, ID >( port );
        delay_ms( 100 );

        // Read ID
        //
        while ( wait< D, ID >( port ) ) {}

        if ( signal == traits_t::ID )
        {
            EN_DEBUG( "-- Found device\n" );

            D< CPU > device;
            device.setPort( port );

            m_devices.push_back( device );
        }
    }

    return m_devices;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE std::vector< D< CPU > >& Bus< D >::devices()
{
    return m_devices;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status Bus< D >::connect( D< CPU >& device )
{
    if ( !device.port()->isOpen() )
    {
        device.port()->open();
    }

    device.port()->setBaudrate( device.baudrate );

    device.state = Connected;
    uint8_t signal = traits_t::Connect;
    device.port()->write( &signal, 1 );

    EN_DEBUG( "Connected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status Bus< D >::disconnect( D< CPU >& device )
{
    if ( !device.port()->isOpen() )
    {
        return Error;
    }

    device.state = Disconnected;
    uint8_t signal = traits_t::Disconnect;
    device.port()->write( &signal, 1 );

    device.port()->close();

    EN_DEBUG( "Disconnected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

} // engine

#endif // BUS_CPU_IPP
