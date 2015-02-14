//------------------------------------------------------------------------------
//

// STD
#include <cassert>
#include <iostream>

// Engine
#include <iron.hpp>

using namespace engine;

//------------------------------------------------------------------------------
//

namespace engine
{

// Define attributes
//
EN_DEFINE_ATTRIBUTES( Camera, 3 );
EN_DEFINE_ATTRIBUTE( Camera, 0, id,          uint8_t,  0 );
EN_DEFINE_ATTRIBUTE( Camera, 1, resolutionX, uint16_t, 0 );
EN_DEFINE_ATTRIBUTE( Camera, 2, model,       uint32_t, 0 );

} // engine

//------------------------------------------------------------------------------
//

bool testAttributes()
{
    int status_i = 1;

    static_assert( TAttributes< Camera >::num == 3, "incorrect size" );
    static_assert( FAttributesBytes< Camera >::value == 7, "incorrect size" );

    // Test 'id'
    //
    status_i = strcmp( TAttribute< Camera, 0 >::name(), "id" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 0 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 0 >::begin == 0, "incorrect range" );
    static_assert( FAttributeRange< Camera, 0 >::end == 1, "incorrect range" );

    // Test 'resolutionX'
    //
    status_i = strcmp( TAttribute< Camera, 1 >::name(), "resolutionX" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 1 >::type_t ) == 2, "incorrect size" );
    static_assert( FAttributeRange< Camera, 1 >::begin == 1, "incorrect range" );
    static_assert( FAttributeRange< Camera, 1 >::end == 3, "incorrect range" );

    // Test 'model'
    //
    status_i = strcmp( TAttribute< Camera, 2 >::name(), "model" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 2 >::type_t ) == 4, "incorrect size" );
    static_assert( FAttributeRange< Camera, 2 >::begin == 3, "incorrect range" );
    static_assert( FAttributeRange< Camera, 2 >::end == 7, "incorrect range" );

    // Test container
    //
    AttributeContainer< Camera > attrc;

    // Test set/get 'id'
    //
    uint8_t id = 0xB0;
    attrc.set< 0 >( id );

    id = 0;
    attrc.get< 0 >( id );
    assert( id == 0xB0 );

    // Test set/get 'resolutionX'
    //
    uint16_t resolutionX = 640;
    attrc.set< 1 >( resolutionX );

    resolutionX = 0;
    attrc.get< 1 >( resolutionX );
    assert( resolutionX == 640 );

    // Test set/get 'model'
    //
    uint32_t model = 2390123;
    attrc.set< 2 >( model );

    model = 0;
    attrc.get< 2 >( model );
    assert( model == 2390123 );

    return true;
}

//------------------------------------------------------------------------------
//

bool testBus()
{
    std::vector< Device< IR, CPU > >& devices = Bus< IR >::get().scan();

    for ( size_t i = 0; i < devices.size(); ++i )
    {
        Bus< IR >::get().connect( devices[ i ] );
        assert( devices[ i ].state == Connected );
        sleep( 2 );
    }

    sleep( 2 );

    for ( size_t i = 0; i < devices.size(); ++i )
    {
        Bus< IR >::get().disconnect( devices[ i ] );
        assert( devices[ i ].state == Disconnected );
        sleep( 2 );
    }

    return true;
}

//------------------------------------------------------------------------------
//

int main()
{
    assert( testAttributes() );
    //assert( testBus() );

    return 0;
}
