#include "prefix.h"

namespace IR {

	InfinitRightUndoValueDelete::InfinitRightUndoValueDelete(const IRUUID& objectUuid, const IRJson& jsObject, const IRObjectId& objectId)
		: InfinitRightUndoValue(objectUuid, objectId)
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


	void InfinitRightUndoValueDelete::WriteCallbackJson(IRJson& json)
	{
		InfinitRightUndoValue::WriteCallbackJson(json);
		
		IRString objectIdString = std::to_string(fObjectId);
		
		IRJson& deleteJson = json[IR_CHANGE_TYPE_Delete];
		if (!JS_CON::HasObjectProperty(objectIdString, deleteJson)) { deleteJson[objectIdString] = IRJson::array(); }
		deleteJson[objectIdString].push_back(JS_CON::ConvertValue(fObjectUuid));
	}
}