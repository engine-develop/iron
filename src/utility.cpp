//------------------------------------------------------------------------------
//

#include "utility.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//
#ifndef __AVR__
bool listDirectory( const std::string& path,
                    std::vector< std::string >& files,
                    const bool& recurse )
{
    DIR* dp = opendir( path.c_str() );
    if ( !dp ) { return false; }

    struct dirent* entry;

    while ( ( entry = readdir( dp ) ) )
    {
        std::string subPath = path + std::string( "/" ) + std::string( entry->d_name );

        if ( isDirectory( subPath )
             && recurse
             && strcmp( entry->d_name, "."  )
             && strcmp( entry->d_name, ".." ) )
        {
            listDirectory( subPath, files, recurse );
        }

        files.push_back( subPath );
    }

    closedir( dp );

    return true;
}
#endif // __AVR__

} // engine
