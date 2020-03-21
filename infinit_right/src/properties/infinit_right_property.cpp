#include "prefix.h"

namespace IR {

	void HandleValueChange(InfinitRightObject* object, const IRJson& oldValue, const IRJson& newValue)
	{
		InfinitRightUndoAction* currentAction = InfinitRightApp::gApp().GetUndoManager().GetActiveAction();
		if (currentAction && object)
		{
			currentAction->AddObjectChangeValue(object->GetUuid(), oldValue, newValue);
		}
	}

	InfinitRightProperty::InfinitRightProperty(const IRString& name, InfinitRightObject* object)
		: fName(name), fObject(object)
	{
		object->PushProperty(this);
	}
	
}