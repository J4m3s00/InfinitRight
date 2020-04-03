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
		IRString objectType;
		if (JS_CON::GetParamStringSafe("ObjectType", fJSObject, objectType))
		{
			InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(InfinitRightApp::gApp().new_object(objectType))->FromJs(fJSObject);
		}
	}

	void InfinitRightUndoValueDelete::Redo()
	{
		InfinitRightApp::gApp().GetActiveDrawing()->DeleteObject(fObjectUuid);
	}

}