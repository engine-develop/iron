#ifndef IR_BUS_CPU_IPP
#define IR_BUS_CPU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

IRON_INLINE Bus< CPU >::Bus()
    : m_ports()
{
}

//------------------------------------------------------------------------------
//

IRON_INLINE Bus< CPU >::~Bus()
{
    release();
}

//------------------------------------------------------------------------------
//

IRON_INLINE Bus< CPU >& Bus< CPU >::get()
{
    static Bus< CPU > obj;

    return obj;
}

//------------------------------------------------------------------------------
//

IRON_INLINE void Bus< CPU >::release()
{
    for ( std::vector< port_obj_t* >::iterator it = m_ports.begin();
            it != m_ports.end(); ++it )
    {
        if ( *it )
        {
            IRON_DEBUG( "Closing port: %s\n", (*it)->getPort().c_str() );

            APort::close( *it );
            delete *it;
        }
    }

    m_ports.clear();
}

//------------------------------------------------------------------------------
//

IRON_INLINE std::vector< port_obj_t* >& Bus< CPU >::ports()
{
    return m_ports;
}

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE std::vector< N > Bus< CPU >::scan()
{
    release();

    std::vector< N > devices;

    std::vector< PortInfo > devices_i = list_ports();

    for ( std::vector< PortInfo >::const_iterator it
            = devices_i.begin(); it != devices_i.end(); ++it )
    {
        IRON_DEBUG( "Opening port: %s\n", it->port.c_str() );

        N device;

        m_port = new port_obj_t( it->port,
                                 /*device.baudrate()*/ 9600,
                                 Timeout::simpleTimeout( 1000 ) );

        // Failed to open port
        //
        if ( !m_port->isOpen() )
        {
            IRON_DEBUG( "Error: Failed to open port\n" );

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
            IRON_DEBUG( "-- Found device\n" );

            //device.setPort( m_port );
            devices.push_back( device );
        }
    }

    m_port = 0x0;

    return devices;
}

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE Status Bus< CPU >::select( N& device )
{
    if ( device.state() & Selected )
    {
        deselect( device );
    }

    //m_port = device.port();

    device.state() |= Selected;
    //signal< Signal_Select >( device.port() );

    //IRON_DEBUG( "Selected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE Status Bus< CPU >::deselect( N& device )
{
    if ( !( device.state() & Selected ) )
    {
        return Error;
    }

    device.state() &= ~Selected;
    //signal< Signal_Select >( device.port() );

    m_port = 0x0;

    //IRON_DEBUG( "Deselected: %s\n", device.port()->getPort().c_str() );

    return Success;
}

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE std::vector< N > scan()
{
    return Bus< CPU >::get().scan< N >();
}

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE Status select( N& device )
{
    return Bus< CPU >::get().select( device );
}

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE Status deselect( N& device )
{
    return Bus< CPU >::get().deselect( device );
}

} // engine

#endif // IR_BUS_CPU_IPP
