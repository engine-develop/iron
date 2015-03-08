#ifndef IR_TYPESTORE_HPP
#define IR_TYPESTORE_HPP

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
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <algorithm>

// Engine
#include "utility.hpp"
#include "environment.hpp"
#include "signal.hpp"
#include "node.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

enum Types
{
    Types_Variable = 0,
    Types_Node     = 1
};

//------------------------------------------------------------------------------
//

template< int T >
struct TTypes
{
    static EN_INLINE const char* label() { return ""; }
};

//------------------------------------------------------------------------------
//

struct BType
{
    std::string name;
    std::string description;
    std::string category;
    uint32_t id;
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

template< int T >
EN_INLINE bool operator<( const Type< T >& lhs,
                          const Type< T >& rhs );

//------------------------------------------------------------------------------
//

template<>
struct Type< Types_Variable >
    : BType
{
    std::string dataType;
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
    static EN_INLINE Status verifyType( Type< T >* type )
    {
        return Success;
    }

    static EN_INLINE void createTypes( std::string& file,
                                       std::vector< Type< T >* >& types )
    {
    }
};

//------------------------------------------------------------------------------
//

template<>
struct FTypeStoreType< Types_Variable >
{
    typedef Type< Types_Variable > type_t;

    static EN_INLINE Status verifyType( type_t* type );

    static EN_INLINE Status parseTypeInfo( std::string& block,
                                           type_t* type );

    static EN_INLINE void createTypes( std::string& file,
                                       std::vector< type_t* >& types );
};

//------------------------------------------------------------------------------
//

template<>
struct FTypeStoreType< Types_Node >
{
    typedef Type< Types_Node > type_t;

    static EN_INLINE Status verifyType( type_t* type );

    static EN_INLINE Status parseTypeInfo( std::string& block,
                                           type_t* type );

    static EN_INLINE Status parseTypeClass( std::string& block,
                                            type_t* type );

    static EN_INLINE void createTypes( std::string& file,
                                       std::vector< type_t* >& types );
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

    EN_INLINE void reload();

    EN_INLINE Status registerType( Type< T >* type );

    EN_INLINE void registerTypes( const std::string& directory );

    EN_INLINE void registerTypes( const std::vector< std::string >& directories );

    //----------
    //

    EN_INLINE const registry_t& types() const;

    EN_INLINE Type< T >* type( const uint32_t& id );

    EN_INLINE std::vector< std::string > categories();

    EN_INLINE std::vector< Type< T >* > typesByCategory( const std::string& category );

protected:

    EN_INLINE TypeStore();
    EN_INLINE ~TypeStore();
    EN_INLINE TypeStore( const TypeStore& ) {}
    EN_INLINE TypeStore& operator=( const TypeStore& ) { return *this; }

    EN_INLINE void clear();

    EN_INLINE void init();

    EN_INLINE Status verifyType( Type< T >* type );

    registry_t m_types;

};

} // engine

//------------------------------------------------------------------------------
//

#include "typestore.ipp"

#endif // IR_TYPESTORE_HPP
