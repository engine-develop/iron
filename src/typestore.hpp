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

enum Types
{
    Types_Device = 0,
    Types_Signal = 1
};

//------------------------------------------------------------------------------
//

template< int T >
class Type
{
};

//------------------------------------------------------------------------------
//

template<>
class Type< Types_Device >
{

public:
    virtual ~Type() {}

    virtual std::string name() = 0;
    virtual std::string description() = 0;
    virtual uint32_t id() = 0;
    virtual void* create() = 0;
    virtual void destroy( void* obj ) = 0;
    virtual void evaluate( void* obj ) = 0;
};

//------------------------------------------------------------------------------
//

template< template< int A > class D >
class DeviceType
    : public Type< Types_Device >
{

public:

    typedef TDevice< D > traits_t;

    virtual EN_INLINE std::string name();
    virtual EN_INLINE std::string description();
    virtual EN_INLINE uint32_t id();
    virtual EN_INLINE void* create();
    virtual EN_INLINE void destroy( void* obj );
    virtual EN_INLINE void evaluate( void* obj );
};

//------------------------------------------------------------------------------
//

template< int T >
class TypeStore
{

public:

    typedef std::map< uint32_t, Type< T >* > registry_t;
    typedef typename registry_t::iterator iterator_t;

    //------
    //

    static EN_INLINE TypeStore& get();

    //------
    //

    EN_INLINE Status registerType( Type< T >* type );

    EN_INLINE const registry_t& types() const;

    EN_INLINE iterator_t typesBegin();

    EN_INLINE iterator_t typesEnd();

protected:

    EN_INLINE TypeStore();
    EN_INLINE ~TypeStore();
    EN_INLINE TypeStore( const TypeStore& ) {}
    EN_INLINE TypeStore& operator=( const TypeStore& ) { return *this; }

    EN_INLINE void release();

    registry_t m_types;

};

} // engine

//------------------------------------------------------------------------------
//

#include "typestore.ipp"

#endif // TYPESTORE_HPP
