//------------------------------------------------------------------------------
//

#include <iron.hpp>

//------------------------------------------------------------------------------
//

namespace engine
{

//------------------------------------------------------------------------------
// Define node
//

IRON_DEFINE_NODE(
    ( PinMode, "Example node", "Pins" ),
    (( pin,  Input, Byte, 0,   None ))
    (( mode, Input, Byte, LOW, None ))
)

//------------------------------------------------------------------------------
// Define node class
//

IRON_NODE_CLASS( PinMode )
{
    void evaluate()
    {
    }
};

} // engine
