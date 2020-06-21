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
		if (!JS_CON::HasObjectProperty("Creations", json)) { json["Changes"] = IRJson::object();}


		IRString objectIdString = std::to_string(fObjectId);

		if (json["Creations"].find(objectIdString) == json["Creations"].end())
		{
			json["Creations"][objectIdString] = IRJson::object();
		}

		IRJson& creationsJson = json["Creations"][objectIdString];

		if (creationsJson.find("Value") == creationsJson.end()) 
		{
			creationsJson["Value"] = IRJson::object();
		}

		for (auto& item : fJSObject.items())
		{
			creationsJson["Value"][item.key()] = item.value();
		}
	}

}