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

// Define device
//
EN_DEFINE_DEVICE( Camera, "Example camera device", 0xB0, 0x7B, 0xA6, 0x43, 3 );

// Define attributes
//
EN_DEFINE_ATTRIBUTE( Camera, Input,    0, shutter, uint8_t,  Low,     None );
EN_DEFINE_ATTRIBUTE( Camera, Internal, 1, model,   uint32_t, 2389221, None );
EN_DEFINE_ATTRIBUTE( Camera, Output,   2, led,     uint8_t,  Low,     13   );

// Define device class
//
EN_DEVICE_CLASS( Camera )
{
};

} // engine

//------------------------------------------------------------------------------
//

bool testAttributes()
{
    int status_i = 1;

    // Test static info
    //
    status_i = strcmp( TDevice< Camera >::name(), "Camera" );
    assert( status_i == 0 );
    status_i = strcmp( TDevice< Camera >::description(), "Example camera device" );
    assert( status_i == 0 );
    assert( TDevice< Camera >::id()[ 0 ] == 0xB0 );
    assert( TDevice< Camera >::id()[ 1 ] == 0x7B );
    assert( TDevice< Camera >::id()[ 2 ] == 0xA6 );
    assert( TDevice< Camera >::id()[ 3 ] == 0x43 );
    static_assert( TDevice< Camera >::numAttributes == 3, "incorrect number" );
    static_assert( FAttributesBytes< Camera >::value == 6, "incorrect size" );

    // Test 'shutter'
    //
    status_i = strcmp( TAttribute< Camera, 0 >::name(), "shutter" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 0 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 0 >::begin == 0, "incorrect range" );
    static_assert( FAttributeRange< Camera, 0 >::end == 1, "incorrect range" );

    // Test 'model'
    //
    status_i = strcmp( TAttribute< Camera, 1 >::name(), "model" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 1 >::type_t ) == 4, "incorrect size" );
    static_assert( FAttributeRange< Camera, 1 >::begin == 1, "incorrect range" );
    static_assert( FAttributeRange< Camera, 1 >::end == 5, "incorrect range" );

    // Test 'led'
    //
    status_i = strcmp( TAttribute< Camera, 2 >::name(), "led" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 2 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 2 >::begin == 5, "incorrect range" );
    static_assert( FAttributeRange< Camera, 2 >::end == 6, "incorrect range" );

    // Test device
    //
    Camera< CPU > cam;

    // Test attribute defaults
    //
    cam.setDefaults();

    uint8_t shutter = High;
    uint32_t model = 0;
    uint8_t led = High;

    cam.get< 0 >( shutter );
    assert( shutter == Low );

    cam.get< 1 >( model );
    assert( model == 2389221 );

    cam.get< 2 >( led );
    assert( led == Low );

    // Test get 'shutter'
    //
    shutter = High;
    cam.get< 0 >( shutter );
    assert( shutter == Low );

    // Test set/get 'model'
    //
    model = 2390123;
    cam.set< 1 >( model );

    model = 0;
    cam.get< 1 >( model );
    assert( model == 2390123 );

    // Test set/get 'led'
    //
    cam.set< 2, High >();

    led = Low;
    cam.get< 2 >( led );
    assert( led == High );

    return true;
}

//------------------------------------------------------------------------------
//

bool testBus()
{
    std::vector< Camera< CPU > >& devices = Bus< Camera >::get().scan();

    for ( size_t i = 0; i < devices.size(); ++i )
    {
        Bus< Camera >::get().connect( devices[ i ] );
        assert( devices[ i ].state == Connected );
        sleep( 2 );
    }

    sleep( 2 );

    for ( size_t i = 0; i < devices.size(); ++i )
    {
        Bus< Camera >::get().disconnect( devices[ i ] );
        assert( devices[ i ].state == Disconnected );
        sleep( 2 );
    }

    return true;
}

//------------------------------------------------------------------------------
//

int main()
{
    std::cout << "Running unit tests for Iron library " IRON_API_VERSION_S << std::endl;

    assert( testAttributes() );
    assert( testBus() );

    return 0;
}
