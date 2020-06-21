#include "prefix.h"

namespace IR {

	InfinitRightUndoValueChange::InfinitRightUndoValueChange(const IRUUID& objectUuid, const IRJson& oldValue, const IRJson& newValue, const IRObjectId& objectId)
		: InfinitRightUndoValue(objectUuid, objectId)
	{
		fOldValue = oldValue;
		fNewValue = newValue;
	}

	InfinitRightUndoValueChange::~InfinitRightUndoValueChange()
	{

	}

	void InfinitRightUndoValueChange::Redo()
	{
		InfinitRightObject* obj = GetObject();
		IR_ASSERT(obj, "The undo value \"" + fNewValue.dump() + "\" has not found its object!");
		if (obj)
		{
			obj->FromJs(fNewValue);
		}
	}

	void InfinitRightUndoValueChange::Undo()
	{
		InfinitRightObject* obj = GetObject();
		IR_ASSERT(obj, "The undo value \"" + fOldValue.dump() + "\" has not found its object!");
		if (obj)
		{
			obj->FromJs(fOldValue);
		}
	}

	void InfinitRightUndoValueChange::WriteCallbackJson(IRJson& json)
	{
		InfinitRightUndoValue::WriteCallbackJson(json);
		json["ChangeType"] = JS_CON::ConvertValue("change");
		json["ObjectType"] = JS_CON::ConvertValue(fObjectId);
		json["UUID"] = JS_CON::ConvertValue(fObjectUuid);
		json[""];
	}
}