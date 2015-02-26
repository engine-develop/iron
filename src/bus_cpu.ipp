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
        if ( *it )
        {
            APort::close( *it );
            delete *it;
        }
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

        D< CPU > device;

        m_port = new port_obj_t( it->port,
                                 device.baudrate(),
                                 Timeout::simpleTimeout( 1000 ) );

        // Failed to open port
        //
        if ( !m_port->isOpen() )
        {
            EN_DEBUG( "Error: Failed to open port\n" );

            delete m_port;

            continue;
        }

        m_ports.push_back( m_port );

        // Signal ID
        //
        signal< Signal_ID >( m_port );

        // Wait for return ID
        //
        if ( wait< Signal_ID >( m_port, 1000 ) == Success )
        {
            EN_DEBUG( "-- Found device\n" );

            device.setPort( m_port );
            devices.push_back( device );
        }
    }

    m_port = 0x0;

    return devices;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status Bus< CPU >::select( D< CPU >& device )
{
    if ( device.state() & Selected )
    {
        deselect( device );
    }

    m_port = device.port();

    device.state() |= Selected;
    signal< Signal_Select >( device.port() );

    EN_DEBUG( "Selected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status Bus< CPU >::deselect( D< CPU >& device )
{
    if ( !( device.state() & Selected ) )
    {
        return Error;
    }

    device.state() &= ~Selected;
    signal< Signal_Select >( device.port() );

    m_port = 0x0;

    EN_DEBUG( "Deselected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE std::vector< D< CPU > > scan()
{
    return Bus< CPU >::get().scan< D >();
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status select( D< CPU >& device )
{
    return Bus< CPU >::get().select( device );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status deselect( D< CPU >& device )
{
    return Bus< CPU >::get().deselect( device );
}

} // engine

#endif // BUS_CPU_IPP
