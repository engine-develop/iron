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
    ( GetDigital, "Example node", "Pins" ),
    (( pin,   Input,  Byte, 0,   None ))
    (( value, Output, Byte, LOW, None ))
)

//------------------------------------------------------------------------------
// Define node class
//

IRON_NODE_CLASS( GetDigital )
{
    void evaluate()
    {
    }
};

} // engine
