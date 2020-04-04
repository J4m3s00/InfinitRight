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
		IRString objectType;
		if (JS_CON::GetParamStringSafe("ObjectType", fJSObject, objectType))
		{
			InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(objectType)->FromJs(fJSObject);
		}
	}

}