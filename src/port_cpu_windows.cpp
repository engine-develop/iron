//------------------------------------------------------------------------------
//

#include <tchar.h>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <cstring>
#include <initguid.h>
#include <clocale>
#include <cstdlib>

#include "port_cpu_windows.hpp"

//------------------------------------------------------------------------------
//

namespace engine
{

//------------------------------------------------------------------------------
//

static const DWORD port_name_max_length = 256;
static const DWORD friendly_name_max_length = 256;
static const DWORD hardware_id_max_length = 256;

//------------------------------------------------------------------------------
//

Serial::SerialImpl::SerialImpl( const std::string &port,
                                unsigned long baudrate,
                                bytesize_t bytesize,
                                parity_t parity,
                                stopbits_t stopbits,
                                flowcontrol_t flowcontrol )
    : port_( port.begin(), port.end() ),
      fd_( INVALID_HANDLE_VALUE ),
      is_open_( false ),
      baudrate_( baudrate ),
      parity_( parity ),
      bytesize_( bytesize ),
      stopbits_( stopbits ),
      flowcontrol_( flowcontrol )
{
    read_mutex = CreateMutex( NULL, false, NULL );
    write_mutex = CreateMutex( NULL, false, NULL );
    if ( port_.empty() == false )
        open();
}

//------------------------------------------------------------------------------
//

Serial::SerialImpl::~SerialImpl()
{
    this->close();
    CloseHandle( read_mutex );
    CloseHandle( write_mutex );
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::open()
{
    if ( port_.empty() )
    {
        throw std::invalid_argument ("Empty port is invalid.");
    }

    if ( is_open_ == true )
    {
        throw std::runtime_error ("Serial port already open.");
    }

    LPCWSTR lp_port = port_.c_str();
    fd_ = CreateFileW( lp_port,
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       0,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       0 );

    if ( fd_ == INVALID_HANDLE_VALUE )
    {
        DWORD errno_ = GetLastError();
        std::stringstream ss;
        switch ( errno_ )
        {
            case ERROR_FILE_NOT_FOUND:
              // Use this->getPort to convert to a std::string
              ss << "Specified port, " << this->getPort() << ", does not exist.";
              throw std::runtime_error( ss.str().c_str() );
              this->close();
            default:
              ss << "Unknown error opening the serial port: " << errno;
              throw std::runtime_error( ss.str().c_str() );
              this->close();
        }
    }

    else
    {
        reconfigurePort();
        is_open_ = true;
    }
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::reconfigurePort ()
{
    if ( fd_ == INVALID_HANDLE_VALUE )
    {
        // Can only operate on a valid file descriptor
        throw std::runtime_error( "Invalid file descriptor, is the serial port open?" );
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof( dcbSerialParams );

    if ( !GetCommState( fd_, &dcbSerialParams ) )
    {
        //error getting state
        throw std::runtime_error( "Error getting the serial port state." );
    }

    // setup baud rate
    switch ( baudrate_ )
    {
        #ifdef CBR_0
        case 0: dcbSerialParams.BaudRate = CBR_0; break;
        #endif
        #ifdef CBR_50
        case 50: dcbSerialParams.BaudRate = CBR_50; break;
        #endif
        #ifdef CBR_75
        case 75: dcbSerialParams.BaudRate = CBR_75; break;
        #endif
        #ifdef CBR_110
        case 110: dcbSerialParams.BaudRate = CBR_110; break;
        #endif
        #ifdef CBR_134
        case 134: dcbSerialParams.BaudRate = CBR_134; break;
        #endif
        #ifdef CBR_150
        case 150: dcbSerialParams.BaudRate = CBR_150; break;
        #endif
        #ifdef CBR_200
        case 200: dcbSerialParams.BaudRate = CBR_200; break;
        #endif
        #ifdef CBR_300
        case 300: dcbSerialParams.BaudRate = CBR_300; break;
        #endif
        #ifdef CBR_600
        case 600: dcbSerialParams.BaudRate = CBR_600; break;
        #endif
        #ifdef CBR_1200
        case 1200: dcbSerialParams.BaudRate = CBR_1200; break;
        #endif
        #ifdef CBR_1800
        case 1800: dcbSerialParams.BaudRate = CBR_1800; break;
        #endif
        #ifdef CBR_2400
        case 2400: dcbSerialParams.BaudRate = CBR_2400; break;
        #endif
        #ifdef CBR_4800
        case 4800: dcbSerialParams.BaudRate = CBR_4800; break;
        #endif
        #ifdef CBR_7200
        case 7200: dcbSerialParams.BaudRate = CBR_7200; break;
        #endif
        #ifdef CBR_9600
        case 9600: dcbSerialParams.BaudRate = CBR_9600; break;
        #endif
        #ifdef CBR_14400
        case 14400: dcbSerialParams.BaudRate = CBR_14400; break;
        #endif
        #ifdef CBR_19200
        case 19200: dcbSerialParams.BaudRate = CBR_19200; break;
        #endif
        #ifdef CBR_28800
        case 28800: dcbSerialParams.BaudRate = CBR_28800; break;
        #endif
        #ifdef CBR_57600
        case 57600: dcbSerialParams.BaudRate = CBR_57600; break;
        #endif
        #ifdef CBR_76800
        case 76800: dcbSerialParams.BaudRate = CBR_76800; break;
        #endif
        #ifdef CBR_38400
        case 38400: dcbSerialParams.BaudRate = CBR_38400; break;
        #endif
        #ifdef CBR_115200
        case 115200: dcbSerialParams.BaudRate = CBR_115200; break;
        #endif
        #ifdef CBR_128000
        case 128000: dcbSerialParams.BaudRate = CBR_128000; break;
        #endif
        #ifdef CBR_153600
        case 153600: dcbSerialParams.BaudRate = CBR_153600; break;
        #endif
        #ifdef CBR_230400
        case 230400: dcbSerialParams.BaudRate = CBR_230400; break;
        #endif
        #ifdef CBR_256000
        case 256000: dcbSerialParams.BaudRate = CBR_256000; break;
        #endif
        #ifdef CBR_460800
        case 460800: dcbSerialParams.BaudRate = CBR_460800; break;
        #endif
        #ifdef CBR_921600
        case 921600: dcbSerialParams.BaudRate = CBR_921600; break;
        #endif
        default:
            // Try to blindly assign it
            dcbSerialParams.BaudRate = baudrate_;
    }

    // setup char len
    if ( bytesize_ == eightbits )
        dcbSerialParams.ByteSize = 8;
    else if ( bytesize_ == sevenbits )
        dcbSerialParams.ByteSize = 7;
    else if ( bytesize_ == sixbits )
        dcbSerialParams.ByteSize = 6;
    else if ( bytesize_ == fivebits )
        dcbSerialParams.ByteSize = 5;
    else
        throw std::invalid_argument( "invalid char len" );

    // setup stopbits
    if ( stopbits_ == stopbits_one )
        dcbSerialParams.StopBits = ONESTOPBIT;
    else if ( stopbits_ == stopbits_one_point_five )
        dcbSerialParams.StopBits = ONE5STOPBITS;
    else if ( stopbits_ == stopbits_two )
        dcbSerialParams.StopBits = TWOSTOPBITS;
    else
        throw std::invalid_argument( "invalid stop bit" );

    // setup parity
    if ( parity_ == parity_none )
        dcbSerialParams.Parity = NOPARITY;
    else if ( parity_ == parity_even )
        dcbSerialParams.Parity = EVENPARITY;
    else if ( parity_ == parity_odd )
        dcbSerialParams.Parity = ODDPARITY;
    else if ( parity_ == parity_mark )
        dcbSerialParams.Parity = MARKPARITY;
    else if ( parity_ == parity_space )
        dcbSerialParams.Parity = SPACEPARITY;
    else
        throw std::invalid_argument ("invalid parity");

    // setup flowcontrol
    if ( flowcontrol_ == flowcontrol_none )
    {
        dcbSerialParams.fOutxCtsFlow = false;
        dcbSerialParams.fRtsControl = 0x00;
        dcbSerialParams.fOutX = false;
        dcbSerialParams.fInX = false;
    }

    if ( flowcontrol_ == flowcontrol_software )
    {
        dcbSerialParams.fOutxCtsFlow = false;
        dcbSerialParams.fRtsControl = 0x00;
        dcbSerialParams.fOutX = true;
        dcbSerialParams.fInX = true;
    }

    if ( flowcontrol_ == flowcontrol_hardware )
    {
        dcbSerialParams.fOutxCtsFlow = true;
        dcbSerialParams.fRtsControl = 0x03;
        dcbSerialParams.fOutX = false;
        dcbSerialParams.fInX = false;
    }

    // activate settings
    if ( !SetCommState( fd_, &dcbSerialParams ) )
    {
        CloseHandle( fd_ );
        throw std::runtime_error( "Error setting serial port settings." );
    }

    // Setup timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = timeout_.inter_byte_timeout;
    timeouts.ReadTotalTimeoutConstant = timeout_.read_timeout_constant;
    timeouts.ReadTotalTimeoutMultiplier = timeout_.read_timeout_multiplier;
    timeouts.WriteTotalTimeoutConstant = timeout_.write_timeout_constant;
    timeouts.WriteTotalTimeoutMultiplier = timeout_.write_timeout_multiplier;
    if ( !SetCommTimeouts(fd_, &timeouts))
    {
        throw std::runtime_error( "Error setting timeouts." );
    }
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::close()
{
  if (is_open_ == true) {
    if (fd_ != INVALID_HANDLE_VALUE) {
      int ret;
      ret = CloseHandle(fd_);
      if (ret == 0) {
        std::stringstream ss;
        ss << "Error while closing serial port: " << GetLastError();
        throw std::runtime_error( ss.str().c_str() );
      } else {
        fd_ = INVALID_HANDLE_VALUE;
      }
    }
    is_open_ = false;
  }
}

//------------------------------------------------------------------------------
//

bool Serial::SerialImpl::isOpen() const
{
  return is_open_;
}

//------------------------------------------------------------------------------
//

size_t Serial::SerialImpl::available()
{
    if (!is_open_) {
        return 0;
    }
    COMSTAT cs;
    if ( !ClearCommError( fd_, NULL, &cs ) )
    {
        std::stringstream ss;
        ss << "Error while checking status of the serial port: " << GetLastError();
        throw std::runtime_error( ss.str().c_str() );
    }

    return static_cast< size_t >( cs.cbInQue );
}

//------------------------------------------------------------------------------
//

bool Serial::SerialImpl::waitReadable( uint32_t timeout )
{
    throw std::runtime_error( "waitReadable is not implemented on Windows." );

    return false;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::waitByteTimes( size_t count )
{
    throw std::runtime_error( "waitByteTimes is not implemented on Windows." );
}

//------------------------------------------------------------------------------
//

size_t Serial::SerialImpl::read( uint8_t *buf, size_t size )
{
    if ( !is_open_ )
    {
        throw std::runtime_error( "Serial::read" );
    }

    DWORD bytes_read;

    if ( !ReadFile( fd_, buf, static_cast< DWORD >( size ), &bytes_read, NULL ) )
    {
        std::stringstream ss;
        ss << "Error while reading from the serial port: " << GetLastError();
        throw std::runtime_error( ss.str().c_str());
    }

    return (size_t) (bytes_read);
}

//------------------------------------------------------------------------------
//

size_t Serial::SerialImpl::write( const uint8_t *data, size_t length )
{
    if ( is_open_ == false )
    {
        throw std::runtime_error( "Serial::write" );
    }

    DWORD bytes_written;

    if ( !WriteFile( fd_, data, static_cast< DWORD >( length ), &bytes_written, NULL ) )
    {
        std::stringstream ss;
        ss << "Error while writing to the serial port: " << GetLastError();
        throw std::runtime_error( ss.str().c_str());
    }

    return (size_t) (bytes_written);
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setPort( const std::string &port )
{
    port_ = std::wstring( port.begin(), port.end() );
}

//------------------------------------------------------------------------------
//

std::string Serial::SerialImpl::getPort() const
{
    return std::string( port_.begin(), port_.end() );
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setTimeout( Timeout &timeout )
{
    timeout_ = timeout;

    if ( is_open_ )
    {
        reconfigurePort();
    }
}

//------------------------------------------------------------------------------
//

Timeout Serial::SerialImpl::getTimeout() const
{
    return timeout_;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setBaudrate( unsigned long baudrate )
{
    baudrate_ = baudrate;

    if ( is_open_ )
    {
        reconfigurePort();
    }
}

//------------------------------------------------------------------------------
//

unsigned long Serial::SerialImpl::getBaudrate() const
{
    return baudrate_;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setBytesize( bytesize_t bytesize )
{
    bytesize_ = bytesize;

    if ( is_open_ )
    {
        reconfigurePort();
    }
}

//------------------------------------------------------------------------------
//

bytesize_t Serial::SerialImpl::getBytesize() const
{
    return bytesize_;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setParity( parity_t parity )
{
    parity_ = parity;

    if ( is_open_ )
    {
        reconfigurePort();
    }
}

//------------------------------------------------------------------------------
//

parity_t Serial::SerialImpl::getParity() const
{
    return parity_;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setStopbits( stopbits_t stopbits )
{
    stopbits_ = stopbits;

    if ( is_open_ )
    {
        reconfigurePort();
    }
}

//------------------------------------------------------------------------------
//

stopbits_t Serial::SerialImpl::getStopbits() const
{
    return stopbits_;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setFlowcontrol( flowcontrol_t flowcontrol )
{
    flowcontrol_ = flowcontrol;

    if ( is_open_ )
    {
        reconfigurePort();
    }
}

//------------------------------------------------------------------------------
//

flowcontrol_t Serial::SerialImpl::getFlowcontrol() const
{
    return flowcontrol_;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::flush()
{
    if (is_open_ == false)
    {
        throw std::runtime_error ("Serial::flush");
    }

    FlushFileBuffers( fd_ );
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::flushInput()
{
  throw std::runtime_error( "flushInput is not supported on Windows." );
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::flushOutput ()
{
    throw std::runtime_error( "flushOutput is not supported on Windows." );
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::sendBreak( int duration )
{
    throw std::runtime_error( "sendBreak is not supported on Windows." );
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setBreak( bool level )
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::setBreak");
    }

    if ( level )
    {
        EscapeCommFunction( fd_, SETBREAK );
    }

    else
    {
        EscapeCommFunction( fd_, CLRBREAK );
    }
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setRTS( bool level )
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::setRTS");
    }

    if ( level )
    {
        EscapeCommFunction( fd_, SETRTS );
    }

    else
    {
        EscapeCommFunction( fd_, CLRRTS );
    }
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::setDTR( bool level )
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::setDTR");
    }

    if ( level )
    {
        EscapeCommFunction (fd_, SETDTR);
    }

    else
    {
        EscapeCommFunction (fd_, CLRDTR);
    }
}

//------------------------------------------------------------------------------
//

bool Serial::SerialImpl::waitForChange()
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::waitForChange");
    }

    DWORD dwCommEvent;

    if ( !SetCommMask( fd_, EV_CTS | EV_DSR | EV_RING | EV_RLSD ) )
    {
        // Error setting communications mask
        return false;
    }

    if ( !WaitCommEvent( fd_, &dwCommEvent, NULL ) )
    {
        // An error occurred waiting for the event.
        return false;
    }

    else
    {
        // Event has occurred.
        return true;
    }
}

//------------------------------------------------------------------------------
//

bool Serial::SerialImpl::getCTS()
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::getCTS");
    }

    DWORD dwModemStatus;

    if ( !GetCommModemStatus( fd_, &dwModemStatus ) )
    {
        throw std::runtime_error( "Error getting the status of the CTS line." );
    }

    return ( MS_CTS_ON & dwModemStatus ) != 0;
}

//------------------------------------------------------------------------------
//

bool Serial::SerialImpl::getDSR()
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::getDSR");
    }

    DWORD dwModemStatus;

    if ( !GetCommModemStatus( fd_, &dwModemStatus ) )
    {
        throw std::runtime_error( "Error getting the status of the DSR line." );
    }

    return ( MS_DSR_ON & dwModemStatus ) != 0;
}

//------------------------------------------------------------------------------
//

bool Serial::SerialImpl::getRI()
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::getRI");
    }

    DWORD dwModemStatus;

    if ( !GetCommModemStatus( fd_, &dwModemStatus ) )
    {
        throw std::runtime_error( "Error getting the status of the RI line." );
    }

    return ( MS_RING_ON & dwModemStatus ) != 0;
}

//------------------------------------------------------------------------------
//

bool Serial::SerialImpl::getCD()
{
    if ( is_open_ == false )
    {
        throw std::runtime_error ("Serial::getCD");
    }

    DWORD dwModemStatus;

    if ( !GetCommModemStatus( fd_, &dwModemStatus ) )
    {
        // Error in GetCommModemStatus;
        throw std::runtime_error( "Error getting the status of the CD line." );
    }

    return ( MS_RLSD_ON & dwModemStatus ) != 0;
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::readLock()
{
    if ( WaitForSingleObject( read_mutex, INFINITE ) != WAIT_OBJECT_0 )
    {
        throw std::runtime_error( "Error claiming read mutex." );
    }
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::readUnlock()
{
    if ( !ReleaseMutex( read_mutex ) )
    {
        throw std::runtime_error( "Error releasing read mutex." );
    }
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::writeLock()
{
    if ( WaitForSingleObject( write_mutex, INFINITE ) != WAIT_OBJECT_0 )
    {
        throw std::runtime_error( "Error claiming write mutex." );
    }
}

//------------------------------------------------------------------------------
//

void Serial::SerialImpl::writeUnlock()
{
    if ( !ReleaseMutex( write_mutex ) )
    {
        throw std::runtime_error( "Error releasing write mutex." );
    }
}

//------------------------------------------------------------------------------
//
// Remove every other character
//

std::string remove2ndChar( const std::string& src )
{
    std::string result;
    bool n = true;

    for ( std::string::const_iterator it = src.begin();
          it != src.end(); ++it )
    {
        if ( n ) result.push_back( *it );
        n = !n;
    }

    result.erase( result.size()-1 );

    return result;
}

//------------------------------------------------------------------------------
//

// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr)
{
    int size_needed = WideCharToMultiByte( CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL );
    std::string strTo( size_needed, 0 );
    WideCharToMultiByte                  ( CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL );

    return strTo;
}

//------------------------------------------------------------------------------
//

std::vector< PortInfo > list_ports()
{
    std::vector< PortInfo > devices_found;

    HDEVINFO device_info_set = SetupDiGetClassDevs(
                                    (const GUID *) &GUID_DEVCLASS_PORTS,
                                    NULL,
                                    NULL,
                                    DIGCF_PRESENT );

    unsigned int device_info_set_index = 0;
    SP_DEVINFO_DATA device_info_data;

    device_info_data.cbSize = sizeof( SP_DEVINFO_DATA );

    while ( SetupDiEnumDeviceInfo( device_info_set, device_info_set_index, &device_info_data ) )
    {
        device_info_set_index++;

        // Get port name
        HKEY hkey = SetupDiOpenDevRegKey(
            device_info_set,
            &device_info_data,
            DICS_FLAG_GLOBAL,
            0,
            DIREG_DEV,
            KEY_READ);

        TCHAR port_name[ port_name_max_length ];
        DWORD port_name_length = port_name_max_length;

        LPCWSTR port_name_lp = TEXT("PortName");
        LONG return_code = RegQueryValueEx(
                    hkey,
                    port_name_lp /*_T("PortName")*/,
                    NULL,
                    NULL,
                    (LPBYTE)port_name,
                    &port_name_length);

        RegCloseKey( hkey );

        if ( return_code != EXIT_SUCCESS )
            continue;

        if ( port_name_length > 0 && port_name_length <= port_name_max_length )
            port_name[ port_name_length-1 ] = '\0';
        else
            port_name[ 0 ] = '\0';

        // Ignore parallel ports

        if ( _tcsstr(port_name, _T("LPT")) != NULL )
            continue;

        // Get port friendly name

        TCHAR friendly_name[ friendly_name_max_length ];
        DWORD friendly_name_actual_length = 0;

        BOOL got_friendly_name = SetupDiGetDeviceRegistryProperty(
                    device_info_set,
                    &device_info_data,
                    SPDRP_FRIENDLYNAME,
                    NULL,
                    (PBYTE) friendly_name,
                    friendly_name_max_length,
                    &friendly_name_actual_length);

        if ( got_friendly_name == TRUE && friendly_name_actual_length > 0 )
            friendly_name[ friendly_name_actual_length-1 ] = '\0';
        else
            friendly_name[ 0 ] = '\0';

        // Get hardware ID

        TCHAR hardware_id[ hardware_id_max_length ];
        DWORD hardware_id_actual_length = 0;

        BOOL got_hardware_id = SetupDiGetDeviceRegistryProperty(
                    device_info_set,
                    &device_info_data,
                    SPDRP_HARDWAREID,
                    NULL,
                    (PBYTE)hardware_id,
                    hardware_id_max_length,
                    &hardware_id_actual_length);

        if ( got_hardware_id == TRUE && hardware_id_actual_length > 0 )
            hardware_id[ hardware_id_actual_length-1 ] = '\0';
        else
            hardware_id[ 0 ] = '\0';

        #ifdef UNICODE
            std::string port_name_ws( &port_name[0], &port_name[port_name_length] );
            std::string portName = remove2ndChar( port_name_ws );

            std::string friendly_name_ws( &friendly_name[0], &friendly_name[friendly_name_actual_length] );
            std::string friendlyName = remove2ndChar( friendly_name_ws );

            std::string hardware_id_ws( &hardware_id[0], &hardware_id[hardware_id_actual_length] );
            std::string hardwareId = remove2ndChar( hardware_id_ws );
        #else
            std::string portName = port_name;
            std::string friendlyName = friendly_name;
            std::string hardwareId = hardware_id;
        #endif

        // Prepend path characters
        // Ref: http://support.microsoft.com/kb/115831
        //
        portName = std::string( "\\\\.\\" ) + portName;

        PortInfo port_entry;
        port_entry.port = portName;
        port_entry.description = friendlyName;
        port_entry.hardware_id = hardwareId;

        devices_found.push_back( port_entry );
    }

    SetupDiDestroyDeviceInfoList( device_info_set );

    return devices_found;
}

} // engine
