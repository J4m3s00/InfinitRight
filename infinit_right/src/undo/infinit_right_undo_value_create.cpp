#include "prefix.h"

namespace IR {

	InfinitRightUndoValueCreate::InfinitRightUndoValueCreate(const IRUUID& objectUuid, const IRJson& jsObject)
		: InfinitRightUndoValue(objectUuid)
	{
		fJSObject = jsObject;
	}

	InfinitRightUndoValueCreate::~InfinitRightUndoValueCreate()
	{

	}

	void InfinitRightUndoValueCreate::Undo()
	{
		InfinitRightApp::gApp().GetActiveDrawing()->DeleteObject(fObjectUuid);
	}

	void InfinitRightUndoValueCreate::Redo()
	{
		u32 objectType;
		if (JS_CON::GetParamUintSafe("ObjectType", fJSObject, objectType))
		{
			InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(objectType)->FromJs(fJSObject);
		}
	}

}