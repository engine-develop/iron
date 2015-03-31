//------------------------------------------------------------------------------

// Arduino
#include <Arduino.h>

// Engine
#include <iron.hpp>

#include "camera.hpp"

using namespace engine;

// Global device object
Camera g_cam;

//------------------------------------------------------------------------------
//

bool testNodeAttributes()
{
    // Test attribute defaults
    //
    g_cam.setDefaults();

    uint8_t shutter = High;
    uint16_t zoom = 512;
    uint32_t model = 0;
    bool flash = false;
    uint8_t led = High;

    g_cam.get< 0 >( shutter );
    IRON_ASSERT( shutter == Low );

    g_cam.get< 1 >( zoom );
    IRON_ASSERT( zoom != 0 );

    g_cam.get< 2 >( model );
    IRON_ASSERT( model == 2389221 );

    g_cam.get< 3 >( flash );
    IRON_ASSERT( flash == true );

    g_cam.get< 4 >( led );
    IRON_ASSERT( led == Low );

    // Test get 'shutter'
    //
    shutter = High;
    g_cam.get< 0 >( shutter );
    IRON_ASSERT( shutter == Low );

    // Test get 'zoom'
    //
    zoom = 0;
    g_cam.get< 1 >( zoom );
    IRON_ASSERT( zoom != 0 );

    // Test set/get 'model'
    //
    model = 1590123;
    g_cam.set< 2 >( model );

    model = 0;
    g_cam.get< 2 >( model );
    IRON_ASSERT( model == 1590123 );

    // Test set/get 'flash'
    //
    flash = false;
    g_cam.set< 3 >( flash );

    flash = true;
    g_cam.get< 3 >( flash );
    IRON_ASSERT( flash == false );

    // Test set 'led'
    //
    g_cam.set< 4, High >();

    led = Low;
    g_cam.get< 4 >( led );
    IRON_ASSERT( led == High );

    delay_ms( 2000 );
    g_cam.set< 4, Low >();

    led = High;
    g_cam.get< 4 >( led );
    IRON_ASSERT( led == Low );

    return true;
}

//------------------------------------------------------------------------------
//

void setup()
{
    Serial.begin( 9600 );

    IRON_ASSERT( testNodeAttributes() );
}

//------------------------------------------------------------------------------
//

void loop()
{
    g_cam.evaluate();
}
