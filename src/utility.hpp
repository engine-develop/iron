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

#define IRON_STRINGIZE( X ) #X
#define IRON_STRING( X ) IRON_STRINGIZE( X )

#ifdef __AVR__
#define IRON_PRINT( ... ) engine::printf( __VA_ARGS__ );
#else
#define IRON_PRINT( ... ) printf( __VA_ARGS__ );
#endif // __AVR__

#ifdef NDEBUG
#define IRON_DEBUG( ... )
#else
#define IRON_DEBUG( ... ) IRON_PRINT( __VA_ARGS__ );
#endif // NDEBUG

#ifdef NDEBUG
#define IRON_ASSERT( ... )
#else
#define IRON_ASSERT( X ) \
    if ( !(X) ) \
    { \
        IRON_PRINT( "assertion failed: %s, line %d: %s\n", __FILE__, __LINE__ ) \
    }
#endif // NDEBUG

#define IRON_INLINE    __attribute__( ( always_inline ) ) inline
#define IRON_NO_INLINE __attribute__( ( noinline ) )

#define IRON_PACK4( A, B, C, D ) \
    ((uint32_t)(A) << 24) \
  | ((uint32_t)(B) << 16) \
  | ((uint32_t)(C) <<  8) \
  | ((uint32_t)(D) <<  0) \

#define IRON_UPACK4( X, A, B, C, D ) \
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

IRON_INLINE void delay_ms( size_t ms );

#ifdef __AVR__

//------------------------------------------------------------------------------
//

static void printf( const char *fmt, ... );

//------------------------------------------------------------------------------
//

static IRON_INLINE void errorLED();

//------------------------------------------------------------------------------
//

IRON_INLINE void disableI2CPullups();

//------------------------------------------------------------------------------
//

IRON_INLINE int scanI2CDevices();

#endif // __AVR__

#ifndef __AVR__

//------------------------------------------------------------------------------
//

IRON_INLINE int strHexToDec( const std::string& s,
                             int base = 0 );

//------------------------------------------------------------------------------
//

IRON_INLINE void removeChar( std::string& s,
                             char c = ' ' );

//------------------------------------------------------------------------------
//

IRON_INLINE void removeWhitespace( std::string& s );

//------------------------------------------------------------------------------
//

IRON_INLINE void removePunct( std::string& s );

//------------------------------------------------------------------------------
//

IRON_INLINE std::string& rtrim( std::string& s,
                                const char* t = " \t\n\r\f\v" );

//------------------------------------------------------------------------------
//

IRON_INLINE std::string& ltrim( std::string& s,
                                const char* t = " \t\n\r\f\v" );

//------------------------------------------------------------------------------
//

IRON_INLINE std::string& trim( std::string& s,
                               const char* t = " \t\n\r\f\v" );

//------------------------------------------------------------------------------
//

IRON_INLINE void split( const std::string& s,
                        std::vector< std::string >& result,
                        char delimiter = ' ' );

//------------------------------------------------------------------------------
//

IRON_INLINE void join( const std::vector< std::string >& tokens,
                       std::string& result,
                       const std::string& delimiter = "," );

//------------------------------------------------------------------------------
//

IRON_INLINE bool beginsWith( const std::string& s,
                             const std::string& text );

//------------------------------------------------------------------------------
//

IRON_INLINE bool endsWith( const std::string& s,
                           const std::string& text );

//------------------------------------------------------------------------------
//

IRON_INLINE void makeUnixPath( std::string& path );

//------------------------------------------------------------------------------
//

IRON_INLINE bool isDirectory( const std::string& path );

//------------------------------------------------------------------------------
//

IRON_INLINE std::string getCurrentDirectory();

//------------------------------------------------------------------------------
//

IRON_INLINE std::string getHomeDirectory();

//------------------------------------------------------------------------------
//

IRON_INLINE std::string getAppsDirectory();

//------------------------------------------------------------------------------
//

IRON_INLINE void createDirectories( const std::string& path );

//------------------------------------------------------------------------------
//

IRON_INLINE void createDirectories( const std::vector< std::string >& paths );

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
