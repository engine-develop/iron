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

EN_DEFINE_NODE(
    ( Camera, "Example camera node", "Sensors" ),
    (( shutter, Input,    Byte,  LOW,     2    ))
    (( zoom,    Input,    Int,   512,     A0   ))
    (( model,   Internal, Ulong, 2389221, None ))
    (( flash,   Internal, Byte,  true,    None ))
    (( led,     Output,   Byte,  LOW,     13   ))
)

//------------------------------------------------------------------------------
// Define node class
//

EN_NODE_CLASS( Camera )
{
    void setup()
    {
    }

    void loop()
    {
    }
};

} // engine
