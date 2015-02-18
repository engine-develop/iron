//------------------------------------------------------------------------------

// Arduino
#include <Arduino.h>

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

} // engine

// Global device object, MCU architecture
//
Camera< MCU > g_cam;

//------------------------------------------------------------------------------
//

bool testAttributes()
{
    // Test attribute defaults
    //
    g_cam.setDefaults();

    bool state = false;

    uint8_t shutter = High;
    uint16_t zoom = 512;
    uint32_t model = 0;
    bool flash = false;
    uint8_t led = High;

    g_cam.get< 0 >( shutter );
    EN_ASSERT( shutter == Low, "invalid value" );

    g_cam.get< 1 >( zoom );
    EN_ASSERT( zoom != 0, "invalid value" );

    g_cam.get< 2 >( model );
    EN_ASSERT( model == 2389221, "invalid value" );

    g_cam.get< 3 >( flash );
    EN_ASSERT( flash == true, "invalid value" );

    g_cam.get< 4 >( led );
    EN_ASSERT( led == Low, "invalid value" );

    // Test get 'shutter'
    //
    shutter = High;
    g_cam.get< 0 >( shutter );
    EN_ASSERT( shutter == Low, "invalid value" );

    // Test get 'zoom'
    //
    zoom = 0;
    g_cam.get< 1 >( zoom );
    EN_ASSERT( zoom != 0, "invalid value" );

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

    // Test set 'led'
    //
    g_cam.set< 4, High >();

    led = Low;
    g_cam.get< 4 >( led );
    EN_ASSERT( led == High, "invalid value" );
    EN_ASSERT( state, "invalid value" );

    delay_ms( 2000 );
    g_cam.set< 4, Low >();

    led = High;
    g_cam.get< 4 >( led );
    EN_ASSERT( led == Low, "invalid value" );

    return true;
}

//------------------------------------------------------------------------------
//

void setup()
{
    Serial.begin( 9600 );

    g_cam.setup();

    testAttributes();
}

//------------------------------------------------------------------------------
//

void loop()
{
    // Test 'is' function. If 'shutter' is HIGH, set 'led' HIGH.
    //
    // Note: We use attribute aliases rather than indices.
    //
    if ( g_cam.is< Camera_shutter, High >() )
    {
        g_cam.set< Camera_led, High >();
    }

    else
    {
        g_cam.set< Camera_led, Low >();
    }
}
