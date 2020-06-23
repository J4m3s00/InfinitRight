#include "prefix.h"
#include "infinit_right_drawing_object.h"

using namespace IR;

InfinitRightDrawingObject::InfinitRightDrawingObject(const IRUUID& uuid)
    : InfinitRightObject(uuid),
        IR_INIT_PROPERTY(Count),
        IR_INIT_PROPERTY(Selected)
    {

    }


InfinitRightSymbol::InfinitRightSymbol(const IRUUID& uuid)
    : InfinitRightDrawingObject(uuid)
{
    
}