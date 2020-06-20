#include "prefix.h"

namespace IR {

	InfinitRightUndoValueDelete::InfinitRightUndoValueDelete(const IRUUID& objectUuid, const IRJson& jsObject)
		: InfinitRightUndoValue(objectUuid)
	{
		fJSObject = jsObject;
	}

	InfinitRightUndoValueDelete::~InfinitRightUndoValueDelete()
	{

	}

	void InfinitRightUndoValueDelete::Undo()
	{
		u32 objectType;
		if (JS_CON::GetParamUintSafe("ObjectType", fJSObject, objectType))
		{
			InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(objectType)->FromJs(fJSObject);
		}
	}

	void InfinitRightUndoValueDelete::Redo()
	{
		InfinitRightApp::gApp().GetActiveDrawing()->DeleteObject(fObjectUuid);
	}

}