#ifndef PORT_CPU_UNIX_HPP
#define PORT_CPU_UNIX_HPP

// Copyright (C) 2015 Engine Development
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Note: Source code incorporated from 'Serial' library:
//     https://github.com/wjwwood/serial
//
// Copyright (c) 2012 William Woodall, John Harrison
//

//------------------------------------------------------------------------------
//

// STD
#include <pthread.h>

#include "port_cpu.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

using std::size_t;
using std::string;
using std::invalid_argument;

//------------------------------------------------------------------------------
//

class MillisecondTimer {
public:
  MillisecondTimer(const uint32_t millis);
  int64_t remaining();

private:
  static timespec timespec_now();
  timespec expiry;
};

//------------------------------------------------------------------------------
//

class Serial::SerialImpl
{

public:

    SerialImpl( const string &port,
                unsigned long baudrate,
                bytesize_t bytesize,
                parity_t parity,
                stopbits_t stopbits,
                flowcontrol_t flowcontrol );

    virtual ~SerialImpl();

    void open();

    void close();

    bool isOpen() const;

    size_t available();

    bool waitReadable( uint32_t timeout );

    void waitByteTimes( size_t count );

    size_t read( uint8_t *buf, size_t size = 1 );

    size_t write( const uint8_t *data, size_t length );

    void flush();

    void flushInput();

    void flushOutput();

    void sendBreak( int duration );

    void setBreak( bool level );

    void setRTS( bool level );

    void setDTR( bool level );

    bool waitForChange();

    bool getCTS();

    bool getDSR();

    bool getRI();

    bool getCD();

    void setPort( const string &port );

    string getPort() const;

    void setTimeout( Timeout &timeout );

    Timeout getTimeout() const;

    void setBaudrate( unsigned long baudrate );

    unsigned long getBaudrate() const;

    void setBytesize( bytesize_t bytesize );

    bytesize_t getBytesize() const;

    void setParity( parity_t parity );

    parity_t getParity() const;

    void setStopbits( stopbits_t stopbits );

    stopbits_t getStopbits() const;

    void setFlowcontrol( flowcontrol_t flowcontrol );

    flowcontrol_t getFlowcontrol() const;

    void readLock();

    void readUnlock();

    void writeLock();

    void writeUnlock();

protected:

    void reconfigurePort();

private:

    string port_;               // Path to the file descriptor
    int fd_;                    // The current file descriptor

    bool is_open_;
    bool xonxoff_;
    bool rtscts_;

    Timeout timeout_;           // Timeout for read operations
    unsigned long baudrate_;    // Baudrate
    uint32_t byte_time_ns_;     // Nanoseconds to transmit/receive a single byte

    parity_t parity_;           // Parity
    bytesize_t bytesize_;       // Size of the bytes
    stopbits_t stopbits_;       // Stop Bits
    flowcontrol_t flowcontrol_; // Flow Control

    // Mutex used to lock the read functions
    pthread_mutex_t read_mutex;
    // Mutex used to lock the write functions
    pthread_mutex_t write_mutex;
};

} // engine

#endif // PORT_CPU_UNIX_HPP
