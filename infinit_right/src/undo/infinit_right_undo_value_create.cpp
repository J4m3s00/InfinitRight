#include "prefix.h"

namespace IR {

	InfinitRightUndoValueCreate::InfinitRightUndoValueCreate(const IRUUID& objectUuid, const IRJson& jsObject, const IRObjectId& objectId)
		: InfinitRightUndoValue(objectUuid, objectId)
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

	void InfinitRightUndoValueCreate::WriteCallbackJson(IRJson& json)
	{
		InfinitRightUndoValue::WriteCallbackJson(json);
		
		IRString objectIdString = std::to_string(fObjectId);

		IRJson& createJson = json[IR_CHANGE_TYPE_Create];
		if (!JS_CON::HasObjectProperty(objectIdString, createJson)) { createJson[objectIdString] = IRJson::array(); }
		createJson[objectIdString].push_back(JS_CON::ConvertValue(fObjectUuid));
	}

}