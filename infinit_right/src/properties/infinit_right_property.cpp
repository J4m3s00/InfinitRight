#include "prefix.h"

namespace IR {

	InfinitRightProperty::InfinitRightProperty(const IRString& name, InfinitRightObject* object)
		: fName(name)
	{
		object->PushProperty(this);
	}

}