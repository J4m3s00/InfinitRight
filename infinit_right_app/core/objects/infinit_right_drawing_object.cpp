#include "prefix.h"
#include "infinit_right_drawing_object.h"

using namespace IR;

InfinitRightDrawingObject::InfinitRightDrawingObject(const IRUUID& uuid)
    : InfinitRightObject(uuid),
        IR_INIT_PROPERTY(Count)
    {

    }