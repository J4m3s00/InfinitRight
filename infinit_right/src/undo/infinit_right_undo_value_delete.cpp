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
		if (!JS_CON::HasObjectProperty("Deletions", json)) { json["Changes"] = IRJson::object();}

		IRString objectIdString = std::to_string(fObjectId);

		if (json["Deletions"].find(objectIdString) == json["Deletions"].end())
		{
			json["Deletions"][objectIdString] = IRJson::object();
		}

		IRJson& deletionsJson = json["Deletions"][objectIdString];

		if (deletionsJson.find("Value") == deletionsJson.end()) 
		{
			deletionsJson["Value"] = IRJson::object();
		}

		for (auto& item : fJSObject.items())
		{
			deletionsJson["Value"][item.key()] = item.value();
		}
	}
}