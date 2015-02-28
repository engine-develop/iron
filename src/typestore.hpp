#ifndef TYPESTORE_HPP
#define TYPESTORE_HPP

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
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>

// Engine
#include "utility.hpp"
#include "signal.hpp"
#include "node.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

enum Types
{
    Types_Node   = 0,
    Types_Signal = 1
};

//------------------------------------------------------------------------------
//

struct BType
{
    std::string name;
    std::string description;
    std::string category;
    std::string id0;
    std::string id1;
    std::string id2;
    std::string id3;
};

//------------------------------------------------------------------------------
//

template< int T >
struct Type
    : public BType
{
};

//------------------------------------------------------------------------------
//

struct NodeTypeAttribute
{
    std::string type;
    std::string name;
    std::string dataType;
    std::string defaultValue;
    std::string pin;
};

//------------------------------------------------------------------------------
//

template<>
struct Type< Types_Node >
    : BType
{
    std::vector< NodeTypeAttribute > attributes;
    std::string classCode;
};

//------------------------------------------------------------------------------
//

template< int T >
struct FTypeStoreType
{
    static EN_INLINE void createTypes( std::string& file,
                                       std::vector< Type< T >* >& types )
    {
    }
};

//------------------------------------------------------------------------------
//

template<>
struct FTypeStoreType< Types_Node >
{
    static EN_INLINE void parseTypeInfo( std::string& block,
                                         Type< Types_Node >* type );

    static EN_INLINE void parseTypeClass( std::string& block,
                                          Type< Types_Node >* type );

    static EN_INLINE void createTypes( std::string& file,
                                       std::vector< Type< Types_Node >* >& types );
};

//------------------------------------------------------------------------------
//

template< int T >
class TypeStore
{

public:

    typedef std::map< uint32_t, Type< T >* > registry_t;
    typedef typename registry_t::iterator iterator_t;

    //----------
    //

    static EN_INLINE TypeStore& get();

    EN_INLINE void clear();

    EN_INLINE Status registerType( Type< T >* type );

    EN_INLINE bool scan( const std::string& directory );

    EN_INLINE void scan( const std::vector< std::string >& directories );

    //----------
    //

    EN_INLINE const registry_t& types() const;

    EN_INLINE iterator_t typesBegin();

    EN_INLINE iterator_t typesEnd();

protected:

    EN_INLINE TypeStore();
    EN_INLINE ~TypeStore();
    EN_INLINE TypeStore( const TypeStore& ) {}
    EN_INLINE TypeStore& operator=( const TypeStore& ) { return *this; }

    registry_t m_types;

};

} // engine

//------------------------------------------------------------------------------
//

#include "typestore.ipp"

#endif // TYPESTORE_HPP
