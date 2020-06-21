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

		IRString objectIdString = std::to_string(fObjectId);
		
		IRJson& changeJson = json[IR_CHANGE_TYPE_Change];
		if (!JS_CON::HasObjectProperty(objectIdString, changeJson)) { changeJson[objectIdString] = IRJson::array(); }
		changeJson[objectIdString].push_back(JS_CON::ConvertValue(fObjectUuid));
	}
}