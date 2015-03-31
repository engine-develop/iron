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
    ( Camera, "Example camera node", "Sensors" ),
    (( shutter, Input,    Byte,  Low,     2    ))
    (( zoom,    Input,    Int,   512,     A0   ))
    (( model,   Internal, Ulong, 2389221, None ))
    (( flash,   Internal, Byte,  true,    None ))
    (( led,     Output,   Byte,  Low,     13   ))
)

//------------------------------------------------------------------------------
// Define node class
//

IRON_NODE_CLASS( Camera )
{
    void evaluate()
    {
    }
};

} // engine
