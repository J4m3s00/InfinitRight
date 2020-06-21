#include "prefix.h"

namespace IR {

	InfinitRightUndoValue::InfinitRightUndoValue(const IRUUID& uuid, const IRObjectId& objectId)
		: fObjectUuid(uuid), fObjectId(objectId)
	{

	}

	InfinitRightObject* InfinitRightUndoValue::GetObject()
	{
		return InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(fObjectUuid);
	}

}