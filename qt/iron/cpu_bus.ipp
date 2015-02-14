#ifndef CPU_BUS_IPP
#define CPU_BUS_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE Bus< P >::~Bus()
{
    release();
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE Bus< P >& Bus< P >::get()
{
    static Bus< P > b;

    return b;
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE void Bus< P >::release()
{
    for ( typename std::vector< Device< P, CPU > >::iterator it
            = devices().begin(); it != devices().end(); ++it )
    {
        disconnect( *it );
    }

    m_devices.clear();
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE std::vector< Device< P, CPU > >& Bus< P >::scan()
{
    release();

    std::vector< serial::PortInfo > devices_i = serial::list_ports();

    for ( std::vector< serial::PortInfo >::const_iterator it
            = devices_i.begin(); it != devices_i.end(); ++it )
    {
        EN_DEBUG( "Opening port: %s\n", it->port.c_str() );

        Device< P, CPU > device;
        device.port = new serial::Serial( it->port,
                                          9600,
                                          serial::Timeout::simpleTimeout( 1000 ) );

        // Failed to open port
        //
        if ( !device.port->isOpen() )
        {
            EN_DEBUG( "-- Failed to open port\n" );

            delete device.port;
            device.port = 0x0;

            continue;
        }

        // Request ID
        //
        uint8_t signal = traits_t::ID;
        device.port->write( &signal, 1 );
        delay( 100 );

        // Read ID
        //
        signal = 0;
        device.port->read( &signal, 1 );

        if ( signal == traits_t::ID )
        {
            EN_DEBUG( "-- Found device\n" );

            m_devices.push_back( device );
        }
    }

    return m_devices;
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE std::vector< Device< P, CPU > >& Bus< P >::devices()
{
    return m_devices;
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE Status Bus< P >::connect( Device< P, CPU >& device )
{
    if ( !device.port->isOpen() )
    {
        device.port->open();
    }

    device.port->setBaudrate( device.baudrate );

    device.state = Connected;
    uint8_t signal = traits_t::Connect;
    device.port->write( &signal, 1 );

    EN_DEBUG( "Connected: %s\n", device.port->getPort().c_str() );

    return Status_Ok;
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE Status Bus< P >::disconnect( Device< P, CPU >& device )
{
    if ( !device.port->isOpen() )
    {
        return Status_Error;
    }

    device.state = Disconnected;
    uint8_t signal = traits_t::Disconnect;
    device.port->write( &signal, 1 );

    device.port->close();

    EN_DEBUG( "Disconnected: %s\n", device.port->getPort().c_str() );

    return Status_Ok;
}

} // engine

#endif // CPU_BUS_IPP
