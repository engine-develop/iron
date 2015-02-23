//------------------------------------------------------------------------------
//

// STD
#include <unistd.h>
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
EN_DEFINE_DEVICE( Camera, "Example camera device", 0xB0, 0x7B, 0xA6, 0x43, 5 )

// Define device attributes
//
EN_DEFINE_ATTRIBUTE( Camera, 0, Input,    shutter, uint8_t,  Low,     2    )
EN_DEFINE_ATTRIBUTE( Camera, 1, Input,    zoom,    uint16_t, 512,     A0   )
EN_DEFINE_ATTRIBUTE( Camera, 2, Internal, model,   uint32_t, 2389221, None )
EN_DEFINE_ATTRIBUTE( Camera, 3, Internal, flash,   bool,     true,    None )
EN_DEFINE_ATTRIBUTE( Camera, 4, Output,   led,     uint8_t,  Low,     13   )

// Define device class
//
EN_DEVICE_CLASS( Camera )
{
};

// Register device
//
//EN_REGISTER_DEVICE( Camera )

} // engine

// Global device object, CPU view
//
Camera< CPU > g_cam;

//------------------------------------------------------------------------------
//

bool testBus()
{
    std::vector< Camera< CPU > > devices
            = Bus< CPU >::get().scan< Camera >();

    for ( size_t i = 0; i < devices.size(); ++i )
    {
        Bus< CPU >::get().connect( devices[ i ] );
        assert( devices[ i ].state() & Connected );
        sleep( 2 );
    }

    sleep( 2 );

    for ( size_t i = 0; i < devices.size(); ++i )
    {
        Bus< CPU >::get().disconnect( devices[ i ] );
        assert( !(devices[ i ].state() & Connected) );
        sleep( 2 );
    }

    Bus< CPU >::get().signal< Signal_ID >();
    Bus< CPU >::get().wait< Signal_ID >();

    return true;
}

//------------------------------------------------------------------------------
//

bool testDevice()
{
    int status_i = 0;

    // Test device static info
    //
    status_i = strcmp( TDevice< Camera >::name(), "Camera" );
    assert( status_i == 0 );
    status_i = strcmp( TDevice< Camera >::description(), "Example camera device" );
    assert( status_i == 0 );
    assert( TDevice< Camera >::id == 2960893507 );
    static_assert( TDevice< Camera >::numAttributes == 5, "incorrect number" );
    static_assert( FAttributesBytes< Camera >::value == 9, "incorrect size" );

    g_cam.state() |= Connected;
    assert( ( g_cam.state() & Connected ) );
    assert( !( g_cam.state() & Idle ) );

    g_cam.state() |= Idle;
    assert( ( g_cam.state() & Connected ) );
    assert( ( g_cam.state() & Idle ) );

    g_cam.state() &= ~Connected;
    assert( !( g_cam.state() & Connected ) );
    assert( ( g_cam.state() & Idle ) );

    g_cam.state() = Idle | Connected;
    assert( ( g_cam.state() & Connected ) );
    assert( ( g_cam.state() & Idle ) );

    return true;
}

//------------------------------------------------------------------------------
//

bool testDeviceAttributes()
{
    int status_i = 0;

    // Test 'shutter'
    //
    status_i = strcmp( TAttribute< Camera, 0 >::name(), "shutter" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 0 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 0 >::begin == 0, "incorrect range" );
    static_assert( FAttributeRange< Camera, 0 >::end == 1, "incorrect range" );

    // Test 'zoom'
    //
    status_i = strcmp( TAttribute< Camera, 1 >::name(), "zoom" );
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

    // Test 'flash'
    //
    status_i = strcmp( TAttribute< Camera, 3 >::name(), "flash" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 3 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 3 >::begin == 7, "incorrect range" );
    static_assert( FAttributeRange< Camera, 3 >::end == 8, "incorrect range" );

    // Test 'led'
    //
    status_i = strcmp( TAttribute< Camera, 4 >::name(), "led" );
    assert( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 4 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 4 >::begin == 8, "incorrect range" );
    static_assert( FAttributeRange< Camera, 4 >::end == 9, "incorrect range" );

    // Test attribute defaults
    //
    g_cam.setDefaults();

    uint8_t shutter = High;
    uint16_t zoom = 1;
    uint32_t model = 0;
    bool flash = false;
    uint8_t led = High;

    g_cam.get< 0 >( shutter );
    EN_ASSERT( shutter == Low, "invalid value" );

    g_cam.get< 1 >( zoom );
    EN_ASSERT( zoom == 512, "invalid value" );

    g_cam.get< 2 >( model );
    EN_ASSERT( model == 2389221, "invalid value" );

    g_cam.get< 3 >( flash );
    EN_ASSERT( flash == true, "invalid value" );

    g_cam.get< 4 >( led );
    EN_ASSERT( led == Low, "invalid value" );

    // Test set/get 'shutter'
    //
    shutter = High;
    g_cam.set< 0 >( shutter );

    shutter = Low;
    g_cam.get< 0 >( shutter );
    EN_ASSERT( shutter == High, "invalid value" );

    // Test set/get 'zoom'
    //
    zoom = 95;
    g_cam.set< 2 >( zoom );

    zoom = 0;
    g_cam.get< 2 >( zoom );
    EN_ASSERT( zoom == 95, "invalid value" );

    // Test set/get 'model'
    //
    model = 1590123;
    g_cam.set< 2 >( model );

    model = 0;
    g_cam.get< 2 >( model );
    EN_ASSERT( model == 1590123, "invalid value" );

    // Test set/get 'flash'
    //
    flash = false;
    g_cam.set< 3 >( flash );

    flash = true;
    g_cam.get< 3 >( flash );
    EN_ASSERT( flash == false, "invalid value" );

    // Test set/get 'led'
    //
    g_cam.set< 4, High >();

    led = Low;
    g_cam.get< 4 >( led );
    EN_ASSERT( led == High, "invalid value" );

    delay_ms( 2000 );
    g_cam.set< 4, Low >();

    led = High;
    g_cam.get< 4 >( led );
    EN_ASSERT( led == Low, "invalid value" );

    return true;
}

//------------------------------------------------------------------------------
//

bool testTypestore()
{
    typedef TypeStore< Types_Device > typestore_t;

    for ( typename typestore_t::iterator_t it = typestore_t::get().begin();
          it != typestore_t::get().end(); ++it )
    {
        std::cout << it->first << std::endl;
    }

    return true;
}

//------------------------------------------------------------------------------
//

int main()
{
    std::cout << "Running unit tests for Iron library " IRON_API_VERSION_S << std::endl;

    assert( testBus() );
    assert( testDevice() );
    assert( testDeviceAttributes() );
    assert( testTypestore() );

    return 0;
}
