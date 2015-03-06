#ifndef IR_UTILITY_IPP
#define IR_UTILITY_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE void delay_ms( size_t ms )
{
#ifdef __AVR__
    delay( ms );
#endif // __AVR__
#ifdef LINUX
    usleep( ms * 1000U );
#endif // LINUX
#ifdef _WIN32
    Sleep( ms );
#endif // _WIN32
}

#ifdef __AVR__

//------------------------------------------------------------------------------
//

static void printf( const char *fmt, ... )
{
    char buf[ 128 ];
    va_list args;
    va_start( args, fmt );
    vsnprintf( buf, sizeof( buf ), fmt, args );
    va_end( args );
    buf[ sizeof( buf ) / sizeof( buf[ 0 ] ) - 1 ] = '\0';
    Serial.print( buf );
}

//------------------------------------------------------------------------------
//

static EN_INLINE void errorLED()
{
    DDRB |= B00100000; // Set as output

    // Wait for reset
    while ( 1 )
    {
        PORTB ^= B00100000; // Toggle LED
        delay( 100 );
    }
}

//------------------------------------------------------------------------------
//

EN_INLINE void disableI2CPullups()
{
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
    // deactivate internal pull-ups for twi
    // as per note from atmega8 manual pg167
    cbi( PORTC, 4 );
    cbi( PORTC, 5 );
#else
    // deactivate internal pull-ups for twi
    // as per note from atmega128 manual pg204
    cbi( PORTD, 0 );
    cbi( PORTD, 1 );
#endif
}

//------------------------------------------------------------------------------
//

EN_INLINE int scanI2CDevices()
{
    Serial.println( "Scanning I2C Devices..." );

    int nDevices = 0;

    for ( uint8_t addr = 1; addr < 127; addr++ )
    {
        Wire.beginTransmission( addr );

        if ( Wire.endTransmission() == 0 )
        {
            Serial.print( "\tDevice: 0x" );
            if ( addr < 16 ) Serial.print( "0" );
            Serial.println( addr, HEX );

            ++nDevices;
        }
    }

    Serial.print( nDevices );
    Serial.println( " devices found\n" );

    return nDevices;
}

#endif // __AVR__

#ifndef __AVR__

//------------------------------------------------------------------------------
//

EN_INLINE int strHexToDec( const std::string& s,
                           int base )
{
    return static_cast< int >( strtol( s.c_str(), NULL, base ) );
}

//------------------------------------------------------------------------------
//

EN_INLINE void removeChar( std::string& s,
                           char c )
{
    s.erase( std::remove( s.begin(), s.end(), c ), s.end() );
}

//------------------------------------------------------------------------------
//

EN_INLINE void removeWhitespace( std::string& s )
{
    s.erase( std::remove_if( s.begin(), s.end(), ::isspace ), s.end() );
}

//------------------------------------------------------------------------------
//

EN_INLINE void removePunct( std::string& s )
{
    s.erase( std::remove_if( s.begin(), s.end(), ::ispunct ), s.end() );
}

//------------------------------------------------------------------------------
//

EN_INLINE std::string& rtrim( std::string& s,
                              const char* t )
{
    s.erase( s.find_last_not_of( t ) + 1 );

    return s;
}

//------------------------------------------------------------------------------
//

EN_INLINE std::string& ltrim( std::string& s,
                              const char* t )
{
    s.erase( 0, s.find_first_not_of( t ) );

    return s;
}

//------------------------------------------------------------------------------
//

EN_INLINE std::string& trim( std::string& s,
                             const char* t )
{
    return ltrim( rtrim( s, t ), t );
}

//------------------------------------------------------------------------------
//

EN_INLINE void split( const std::string& s,
                      std::vector< std::string >& result,
                      char delimiter )
{
    const char* str = &s[ 0 ];

    do
    {
        const char* begin = str;

        while( *str != delimiter && *str ) ++str;

        result.push_back( std::string( begin, str ) );
    }

    while ( 0 != *str++ );
}

//------------------------------------------------------------------------------
//

EN_INLINE void join( const std::vector< std::string >& tokens,
                     std::string& result,
                     const std::string& delimiter )
{
    for ( size_t i = 0; i < tokens.size(); ++i )
    {
        result.append( tokens[ i ] );

        if ( i < tokens.size()-1 )
        {
            result.append( delimiter );
        }
    }
}

//------------------------------------------------------------------------------
//

EN_INLINE void makeUnixPath( std::string& path )
{
    static const char unixSeparator = '/';
    static const char windowsSeparator = '\\';

    std::replace( path.begin(),
                  path.end(),
                  windowsSeparator,
                  unixSeparator );
}

//------------------------------------------------------------------------------
//

EN_INLINE bool isDirectory( const std::string& path )
{
    struct stat sb;

    return ( stat( path.c_str(), &sb ) == 0
             && S_ISDIR( sb.st_mode ) );
}

//------------------------------------------------------------------------------
//

EN_INLINE std::string getCurrentDirectory()
{
    char buf[ PATH_MAX ];
    getcwd( buf, PATH_MAX );

    std::string path( buf );
    makeUnixPath( path );

    return path;
}

//------------------------------------------------------------------------------
//

EN_INLINE std::string getHomeDirectory()
{
    std::string path;
#ifdef _WIN32
    path = getenv( "USERPROFILE" );
    makeUnixPath( path );
#endif // _WIN32
#ifdef LINUX
    struct passwd* pwd = getpwuid( getuid() );

    if ( pwd ) path = pwd->pw_dir;
    else       path = getenv( "HOME" );
#endif // LINUX
    return path;
}

//------------------------------------------------------------------------------
//

EN_INLINE std::string getAppsDirectory()
{
    std::string path;
#ifdef _WIN32
    path = getenv( "ProgramFiles" );
    makeUnixPath( path );
#endif // _WIN32
#ifdef LINUX
    path = "/usr/local/bin";
#endif // LINUX
    return path;
}

//------------------------------------------------------------------------------
//

EN_INLINE void createDirectories( const std::string& path )
{
    struct stat st;

    for ( std::string::const_iterator iter = path.begin() ; iter != path.end(); )
    {
        std::string::const_iterator newIter = std::find( iter, path.end(), '/' );
        std::string newPath( path.begin(), newIter );

        if ( stat( newPath.c_str(), &st ) != 0 )
        {
            mkdir( newPath.c_str() );
        }

        else
        {
            if ( !S_ISDIR( st.st_mode ) )
            {
                errno = ENOTDIR;

                return;
            }
        }

        iter = newIter;
        if ( newIter != path.end() ) ++iter;
    }
}

//------------------------------------------------------------------------------
//

EN_INLINE void createDirectories( const std::vector< std::string >& paths )
{
    for ( auto it = paths.begin(); it != paths.end(); ++it )
    {
        createDirectories( *it );
    }
}

#endif // __AVR__

} // engine

#endif // IR_UTILITY_IPP
