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
		InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(new InfinitRightObject(fObjectUuid))->FromJs(fJSObject);
	}

}