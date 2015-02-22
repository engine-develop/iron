#ifndef BUS_CPU_IPP
#define BUS_CPU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE Bus< CPU >::Bus()
    : m_ports()
{
}

//------------------------------------------------------------------------------
//

EN_INLINE Bus< CPU >::~Bus()
{
    release();
}

//------------------------------------------------------------------------------
//

EN_INLINE Bus< CPU >& Bus< CPU >::get()
{
    static Bus< CPU > obj;

    return obj;
}

//------------------------------------------------------------------------------
//

EN_INLINE void Bus< CPU >::release()
{
    for ( std::vector< port_obj_t* >::iterator it = m_ports.begin();
          it != m_ports.end(); ++it )
    {
        if ( *it ) delete *it;
    }

    m_ports.clear();
}

//------------------------------------------------------------------------------
//

EN_INLINE std::vector< port_obj_t* >& Bus< CPU >::ports()
{
    return m_ports;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE std::vector< D< CPU > > Bus< CPU >::scan()
{
    release();

    std::vector< D< CPU > > devices;

    std::vector< PortInfo > devices_i = list_ports();

    for ( std::vector< PortInfo >::const_iterator it
            = devices_i.begin(); it != devices_i.end(); ++it )
    {
        EN_DEBUG( "Opening port: %s\n", it->port.c_str() );

        port_obj_t* port = new port_obj_t( it->port,
                                           9600,
                                           Timeout::simpleTimeout( 1000 ) );

        // Failed to open port
        //
        if ( !port->isOpen() )
        {
            EN_DEBUG( "Error: Failed to open port\n" );

            delete port;

            continue;
        }

        m_ports.push_back( port );

        // Signal ID
        //
        signal< Signal_ID >( port );

        // Wait for return ID
        //
        while ( wait< Signal_ID >( port ) ) {}

        EN_DEBUG( "-- Found device\n" );

        D< CPU > device;
        device.setPort( port );

        devices.push_back( device );
    }

    return devices;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status Bus< CPU >::connect( D< CPU >& device )
{
    if ( device.state() & Connected )
    {
        disconnect( device );
    }

    m_port = device.port();

    device.state() |= Connected;
    signal< Signal_Connect >( device.port() );

    EN_DEBUG( "Connected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status Bus< CPU >::disconnect( D< CPU >& device )
{
    if ( !( device.state() & Connected ) )
    {
        return Error;
    }

    device.state() &= ~Connected;
    signal< Signal_Disconnect >( device.port() );

    device.port()->close();
    m_port = 0x0;

    EN_DEBUG( "Disconnected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

} // engine

#endif // BUS_CPU_IPP
