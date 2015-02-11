//------------------------------------------------------------------------------
//

// STD
#include <cassert>
#include <iostream>

// Engine
#include <iron.hpp>

//------------------------------------------------------------------------------
//

bool tstIRBus()
{
#if 0
    engine::IRBusHeader header;

    for ( int i = 0; i < 16; ++i )
    {
        int b0 = header.data()[ i ];
        std::cout << i << ": " << b0 << std::endl;
    }

    header.setResolution( 640, 480 );
    assert( header.resolutionX() == 640 );
    assert( header.resolutionY() == 480 );
#endif
    engine::Bus< engine::IR, engine::CPU >::connect();
    engine::Bus< engine::IR, engine::CPU >::disconnect();

    return true;
}

//------------------------------------------------------------------------------
//

int main()
{
    assert( tstIRBus() );

    return 0;
}
