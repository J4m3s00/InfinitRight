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
		InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(new InfinitRightObject(fObjectUuid))->FromJs(fJSObject);
	}

	void InfinitRightUndoValueDelete::Redo()
	{
		InfinitRightApp::gApp().GetActiveDrawing()->DeleteObject(fObjectUuid);
	}

}