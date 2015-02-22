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
#include <map>

// Engine
#include "utility.hpp"
#include "signal.hpp"
#include "device.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

enum TypeStoreType
{
    TypeStoreType_Device = 0,
    TypeStoreType_Signal = 1
};

//------------------------------------------------------------------------------
//

template< int T >
struct Type
{
};

//------------------------------------------------------------------------------
//

template<>
struct Type< TypeStoreType_Device >
{
    typedef void* (*create_fn_t)();
    typedef void (*evaluate_fn_t)();

    Type( std::string name_ = "",
          std::string description_ = "",
          uint32_t id_ = 0,
          create_fn_t create_fn_ = 0x0,
          evaluate_fn_t evaluate_fn_ = 0x0 )
        : name( name_ )
        , description( description_ )
        , id( id_ )
        , create_fn( create_fn_ )
        , evaluate_fn( evaluate_fn_ )
    {
    }

    std::string name;
    std::string description;
    uint32_t id;
    //std::vector<> attributes;
    create_fn_t create_fn;
    evaluate_fn_t evaluate_fn;
};

//------------------------------------------------------------------------------
//

template< int T >
class TypeStore
{

public:

    typedef std::map< uint32_t, Type< T > > registry_t;

    //------
    //

    static EN_INLINE TypeStore& get();

    //------
    //

    EN_INLINE Status registerType( Type< T > type );

    EN_INLINE typename registry_t::iterator begin();

    EN_INLINE typename registry_t::iterator end();

protected:

    EN_INLINE TypeStore() {}
    EN_INLINE ~TypeStore();
    EN_INLINE TypeStore( const TypeStore& ) {}
    EN_INLINE TypeStore& operator=( const TypeStore& ) {}

    EN_INLINE void release();

    registry_t m_types;

};

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void registerDeviceType();

} // engine

#endif // TYPESTORE_HPP
