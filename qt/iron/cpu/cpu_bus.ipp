#ifndef CPU_Bus_IPP
#define CPU_Bus_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P >
serial::Serial* Bus< P, CPU >::s_port = 0x0;

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE std::vector< BusDevice< P, CPU > > Bus< P, CPU >::listDevices()
{
    std::vector< BusDevice< CPU > > devices;

    std::vector< serial::PortInfo > devices_found = serial::list_ports();

    for ( std::vector< serial::PortInfo >::const_iterator iter = devices_found.begin();
          iter != devices_found.end(); ++iter )
    {
        BusDevice< CPU > device;
        device.port = serial::Serial( iter->port,
                                      9600,
                                      serial::Timeout::simpleTimeout( 1000 ) );

        if ( device.port.isOpen() )
        {
            uint8_t data = 0;
            device.port.read( &data, 1 );

            if ( buffer == Bus< P, CPU >::traits_t::Device_Ready )
            {
                device.port.close();
                devices.push_back( device );
            }
        }
    }

    return devices;
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE Bus_Status Bus< P, CPU >::connect( const BusDevice< P, CPU >& device,
                                             const uint16_t& baudRate )
{
    if ( !device.port.isOpen() )
    {
        device.port.open();
    }

    uint8_t data = 0;
    data = Bus< P, CPU >::traits_t::Host_Connect;
    device.port.write( &data, 1 );

    return Bus_Status_Connected;
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE Bus_Status Bus< P, CPU >::disconnect( const BusDevice< P, CPU >& device )
{
    uint8_t buffer = Bus< P, CPU >::traits_t::Host_Disconnect;
    device.port.write( &buffer, 1 );
    device.port.close();

    return Bus_Status_Disconnected;
}

} // engine

#endif // CPU_Bus_IPP
