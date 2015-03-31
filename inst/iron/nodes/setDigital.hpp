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
    ( SetDigital, "Example node", "Pins" ),
    (( pin,   Input, Byte, 0,   None ))
    (( value, Input, Byte, LOW, None ))
)

//------------------------------------------------------------------------------
// Define node class
//

IRON_NODE_CLASS( SetDigital )
{
    void evaluate()
    {
    }
};

} // engine
