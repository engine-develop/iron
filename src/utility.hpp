#ifndef IR_UTILITY_HPP
#define IR_UTILITY_HPP

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

//------------------------------------------------------------------------------
//

// STD
#ifndef __AVR__
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#ifdef LINUX
#include <pwd.h>
#endif // LINUX
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#endif // __AVR__

// Chaos
#include <chaos/preprocessor.h>

// Arduino
#ifdef __AVR__
#include <Wire/Wire.h>
#include <wiring_private.h>
#endif // __AVR__

// Engine
#include "types.hpp"

//------------------------------------------------------------------------------
//

#define EN_STRINGIZE( X ) #X
#define EN_STRING( X ) EN_STRINGIZE( X )

#ifdef __AVR__
#define EN_PRINT( ... ) engine::printf( __VA_ARGS__ );
#else
#define EN_PRINT( ... ) printf( __VA_ARGS__ );
#endif // __AVR__

#ifdef NDEBUG
#define EN_DEBUG( ... )
#else
#define EN_DEBUG( ... ) EN_PRINT( __VA_ARGS__ );
#endif // NDEBUG

#ifdef NDEBUG
#define EN_ASSERT( ... )
#else
#define EN_ASSERT( X ) \
    if ( !(X) ) \
    { \
        EN_PRINT( "assertion failed: %s, line %d: %s\n", __FILE__, __LINE__ ) \
    }
#endif // NDEBUG

#define EN_INLINE    __attribute__( ( always_inline ) ) inline
#define EN_NO_INLINE __attribute__( ( noinline ) )

#define EN_PACK4( A, B, C, D ) \
    ((uint32_t)(A) << 24) \
  | ((uint32_t)(B) << 16) \
  | ((uint32_t)(C) <<  8) \
  | ((uint32_t)(D) <<  0) \

#define EN_UPACK4( X, A, B, C, D ) \
    (A) = ( (X) >> 24 ) & 0xFF; \
    (B) = ( (X) >> 16 ) & 0xFF; \
    (C) = ( (X) >> 8  ) & 0xFF; \
    (D) = ( (X) >> 0  ) & 0xFF; \

#define setBit( X, N )    (X) |= (1UL << (N));
#define clearBit( X, N )  (X) &= (1UL << (N));
#define toggleBit( X, N ) (X) ^= (1UL << (N));

#define byteLow( X ) ( (uint8_t) ( (X) & 0xFF ) )
#define byteHigh( X ) ( (uint8_t) ( (X) >> 8 ) )
#define bytesJoin( H, L ) ( ( (H) << 8 ) | (L) )

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE void delay_ms( size_t ms );

#ifdef __AVR__

//------------------------------------------------------------------------------
//

static void printf( const char *fmt, ... );

//------------------------------------------------------------------------------
//

static EN_INLINE void errorLED();

//------------------------------------------------------------------------------
//

EN_INLINE void disableI2CPullups();

//------------------------------------------------------------------------------
//

EN_INLINE int scanI2CDevices();

#endif // __AVR__

#ifndef __AVR__

//------------------------------------------------------------------------------
//

EN_INLINE int strHexToDec( const std::string& s,
                           int base = 0 );

//------------------------------------------------------------------------------
//

EN_INLINE void removeChar( std::string& s,
                           char c = ' ' );

//------------------------------------------------------------------------------
//

EN_INLINE void removeWhitespace( std::string& s );

//------------------------------------------------------------------------------
//

EN_INLINE void removePunct( std::string& s );

//------------------------------------------------------------------------------
//

EN_INLINE std::string& rtrim( std::string& s,
                              const char* t = " \t\n\r\f\v" );

//------------------------------------------------------------------------------
//

EN_INLINE std::string& ltrim( std::string& s,
                              const char* t = " \t\n\r\f\v" );

//------------------------------------------------------------------------------
//

EN_INLINE std::string& trim( std::string& s,
                             const char* t = " \t\n\r\f\v" );

//------------------------------------------------------------------------------
//

EN_INLINE void split( const std::string& s,
                      std::vector< std::string >& result,
                      char delimiter = ' ' );

//------------------------------------------------------------------------------
//

EN_INLINE void join( const std::vector< std::string >& tokens,
                     std::string& result,
                     const std::string& delimiter = "," );

//------------------------------------------------------------------------------
//

EN_INLINE void makeUnixPath( std::string& path );

//------------------------------------------------------------------------------
//

EN_INLINE bool isDirectory( const std::string& path );

//------------------------------------------------------------------------------
//

EN_INLINE std::string getCurrentDirectory();

//------------------------------------------------------------------------------
//

EN_INLINE std::string getHomeDirectory();

//------------------------------------------------------------------------------
//

EN_INLINE std::string getAppsDirectory();

//------------------------------------------------------------------------------
//

EN_INLINE void createDirectories( const std::string& path );

//------------------------------------------------------------------------------
//

EN_INLINE void createDirectories( const std::vector< std::string >& paths );

//------------------------------------------------------------------------------
//

bool listDirectory( const std::string& path,
                    std::vector< std::string >& files,
                    const bool& recursive = false );

#endif // __AVR__

} // engine

//------------------------------------------------------------------------------
//

#include "utility.ipp"

#endif // IR_UTILITY_HPP
