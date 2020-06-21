#include "prefix.h"

namespace IR {

	InfinitRightUndoValue::InfinitRightUndoValue(const IRUUID& uuid, const IRObjectId& objectId)
		: fObjectUuid(uuid), fObjectId(objectId)
	{

	}

	InfinitRightObject* InfinitRightUndoValue::GetObject()
	{
		return InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(fObjectUuid);
	}

	void InfinitRightUndoValue::WriteCallbackJson(IRJson& json)
	{
		if (!JS_CON::HasObjectProperty(IR_CHANGE_TYPE_Change, json)) { json[IR_CHANGE_TYPE_Change] = IRJson::object(); }
		if (!JS_CON::HasObjectProperty(IR_CHANGE_TYPE_Create, json)) { json[IR_CHANGE_TYPE_Create] = IRJson::object(); }
		if (!JS_CON::HasObjectProperty(IR_CHANGE_TYPE_Delete, json)) { json[IR_CHANGE_TYPE_Delete] = IRJson::object(); }
	}
}