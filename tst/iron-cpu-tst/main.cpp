//------------------------------------------------------------------------------
//

// STD
#include <unistd.h>
#include <cassert>
#include <iostream>

// Engine
#include <iron.hpp>

#include "camera.hpp"

using namespace engine;

// Global node object
Camera g_cam;

//------------------------------------------------------------------------------
//

bool testEnvironment()
{
    std::string userDir = Environment::get().userDirectory();
    EN_ASSERT( isDirectory( userDir ) == true );

    const std::vector< std::string >& pathDirs
        = Environment::get().pathDirectories();
    EN_ASSERT( pathDirs.size() == 3 );

    return true;
}

//------------------------------------------------------------------------------
//

bool testTypeStore()
{
    typedef TypeStore< Types_Variable > v_typestore_t;
    typedef Type< Types_Variable > v_type_t;

    typedef TypeStore< Types_Node > n_typestore_t;
    typedef Type< Types_Node > n_type_t;

    // Test directory scan
    //
    v_typestore_t::get().registerTypes( "../../tst/iron-cpu-tst" );
    n_typestore_t::get().registerTypes( "../../tst/iron-cpu-tst" );
    //EN_ASSERT( n_typestore_t::get().types().size() == 1 );

    // Test registry of user node type
    //
    n_type_t* userNodeType = new n_type_t();

    userNodeType->name = "TempSensor";
    userNodeType->description = "Temperature sensor";
    userNodeType->category = "Sensors";
    userNodeType->classCode = "void setup() {} void loop() {}";

    n_typestore_t::get().registerType( userNodeType );
    //EN_ASSERT( n_typestore_t::get().types().size() == 2 );

    // Print out key/name pairs
    //
    for ( auto it = n_typestore_t::get().types().begin();
          it != n_typestore_t::get().types().end(); ++it )
    {
        std::cout << "key: " << it->first << " value: " << it->second->name << std::endl;
    }

    // Get type categories
    //
    std::vector< std::string > categories = n_typestore_t::get().categories();
    //EN_ASSERT( categories.size() == 2 );

    for ( size_t i = 0 ; i < categories.size(); ++i )
    {
        std::cout << i << ": " << categories[ i ] << std::endl;
    }

    // Get types by category
    //
    std::vector< n_type_t* > types = n_typestore_t::get().typesByCategory( "Sensors" );
    EN_ASSERT( types.size() == 2 );

    for ( size_t i = 0 ; i < types.size(); ++i )
    {
        std::cout << i << ": " << types[ i ]->name << std::endl;
    }

    return true;
}

//------------------------------------------------------------------------------
//

bool testNodeTraits()
{
    int status_i = 0;

    // Test node static info
    //
    status_i = strcmp( TNode< Camera >::name(), "Camera" );
    EN_ASSERT( status_i == 0 );
    status_i = strcmp( TNode< Camera >::description(), "Example camera node" );
    EN_ASSERT( status_i == 0 );
    static_assert( TNode< Camera >::numAttributes == 5, "incorrect number" );
    static_assert( FAttributesBytes< Camera >::value == 9, "incorrect size" );

    g_cam.state() |= Selected;
    EN_ASSERT( ( g_cam.state() & Selected ) );
    EN_ASSERT( !( g_cam.state() & Idle ) );

    g_cam.state() |= Idle;
    EN_ASSERT( ( g_cam.state() & Selected ) );
    EN_ASSERT( ( g_cam.state() & Idle ) );

    g_cam.state() &= ~Selected;
    EN_ASSERT( !( g_cam.state() & Selected ) );
    EN_ASSERT( ( g_cam.state() & Idle ) );

    g_cam.state() = Idle | Selected;
    EN_ASSERT( ( g_cam.state() & Selected ) );
    EN_ASSERT( ( g_cam.state() & Idle ) );

    return true;
}

//------------------------------------------------------------------------------
//

bool testNodeAttributes()
{
    int status_i = 0;

    // Test 'shutter'
    //
    status_i = strcmp( TAttribute< Camera, 0 >::name(), "shutter" );
    EN_ASSERT( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 0 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 0 >::begin == 0, "incorrect range" );
    static_assert( FAttributeRange< Camera, 0 >::end == 1, "incorrect range" );

    // Test 'zoom'
    //
    status_i = strcmp( TAttribute< Camera, 1 >::name(), "zoom" );
    EN_ASSERT( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 1 >::type_t ) == 2, "incorrect size" );
    static_assert( FAttributeRange< Camera, 1 >::begin == 1, "incorrect range" );
    static_assert( FAttributeRange< Camera, 1 >::end == 3, "incorrect range" );

    // Test 'model'
    //
    status_i = strcmp( TAttribute< Camera, 2 >::name(), "model" );
    EN_ASSERT( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 2 >::type_t ) == 4, "incorrect size" );
    static_assert( FAttributeRange< Camera, 2 >::begin == 3, "incorrect range" );
    static_assert( FAttributeRange< Camera, 2 >::end == 7, "incorrect range" );

    // Test 'flash'
    //
    status_i = strcmp( TAttribute< Camera, 3 >::name(), "flash" );
    EN_ASSERT( status_i == 0 );
    static_assert( sizeof( TAttribute< Camera, 3 >::type_t ) == 1, "incorrect size" );
    static_assert( FAttributeRange< Camera, 3 >::begin == 7, "incorrect range" );
    static_assert( FAttributeRange< Camera, 3 >::end == 8, "incorrect range" );

    // Test 'led'
    //
    status_i = strcmp( TAttribute< Camera, 4 >::name(), "led" );
    EN_ASSERT( status_i == 0 );
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
    EN_ASSERT( shutter == Low );

    g_cam.get< 1 >( zoom );
    EN_ASSERT( zoom == 512 );

    g_cam.get< 2 >( model );
    EN_ASSERT( model == 2389221 );

    g_cam.get< 3 >( flash );
    EN_ASSERT( flash == true );

    g_cam.get< 4 >( led );
    EN_ASSERT( led == Low );

    // Test set/get 'shutter'
    //
    shutter = High;
    g_cam.set< 0 >( shutter );

    shutter = Low;
    g_cam.get< 0 >( shutter );
    EN_ASSERT( shutter == High );

    // Test set/get 'zoom'
    //
    zoom = 95;
    g_cam.set< 2 >( zoom );

    zoom = 0;
    g_cam.get< 2 >( zoom );
    EN_ASSERT( zoom == 95 );

    // Test set/get 'model'
    //
    model = 1590123;
    g_cam.set< 2 >( model );

    model = 0;
    g_cam.get< 2 >( model );
    EN_ASSERT( model == 1590123 );

    // Test set/get 'flash'
    //
    flash = false;
    g_cam.set< 3 >( flash );

    flash = true;
    g_cam.get< 3 >( flash );
    EN_ASSERT( flash == false );

    // Test set/get 'led'
    //
    g_cam.set< 4, High >();

    led = Low;
    g_cam.get< 4 >( led );
    EN_ASSERT( led == High );

    delay_ms( 2000 );
    g_cam.set< 4, Low >();

    led = High;
    g_cam.get< 4 >( led );
    EN_ASSERT( led == Low );

    return true;
}

//------------------------------------------------------------------------------
//

int main()
{
    std::cout << "Running unit tests for Iron library " IRON_API_VERSION_S << std::endl;

    EN_ASSERT( testEnvironment() );
    EN_ASSERT( testTypeStore() );
    EN_ASSERT( testNodeTraits() );
    EN_ASSERT( testNodeAttributes() );

    return 0;
}
