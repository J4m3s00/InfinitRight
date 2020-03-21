#include "prefix.h"

namespace IR {

	InfinitRightUndoValue::InfinitRightUndoValue(const IRUUID& uuid)
		: fObjectUuid(uuid)
	{

	}

	InfinitRightObject* InfinitRightUndoValue::GetObject()
	{
		return InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(fObjectUuid);
	}

}