#ifndef IR_ENVIRONMENT_HPP
#define IR_ENVIRONMENT_HPP

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

#include "utility.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

class Environment
{

public:

    //----------
    //

    static IRON_INLINE Environment& get();

    IRON_INLINE void reload();

    //----------
    //

    IRON_INLINE const std::string& installDirectory();

    IRON_INLINE const std::string& userDirectory();

    IRON_INLINE const std::vector< std::string >& pathDirectories();

protected:

    IRON_INLINE Environment();
    IRON_INLINE ~Environment();
    IRON_INLINE Environment( const Environment& ) {}
    IRON_INLINE Environment& operator=( const Environment& ) { return *this; }

    IRON_INLINE void release();
    IRON_INLINE void init();

    std::string m_installDirectory;
    std::string m_userDirectory;
    std::vector< std::string > m_pathDirectories;

};

} // engine

//------------------------------------------------------------------------------
//

#include "environment.ipp"

#endif // IR_ENVIRONMENT_HPP
