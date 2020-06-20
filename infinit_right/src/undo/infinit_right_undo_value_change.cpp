#include "prefix.h"

namespace IR {

	InfinitRightUndoValueChange::InfinitRightUndoValueChange(const IRUUID& objectUuid, const IRJson& oldValue, const IRJson& newValue)
		: InfinitRightUndoValue(objectUuid)
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
		if (!JS_CON::HasObjectProperty("Changes", json)) { json["Changes"] = IRJson::object(); }
		if (!JS_CON::HasObjectProperty());
	}
}