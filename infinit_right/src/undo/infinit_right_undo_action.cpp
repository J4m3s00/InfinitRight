#include "prefix.h"

namespace IR {

	InfinitRightUndoAction::InfinitRightUndoAction(const IRString& name)
		: fName(name)
	{
		InfinitRightApp::gApp().GetUndoManager().SetActiveAction(this);
	}

	InfinitRightUndoAction::~InfinitRightUndoAction()
	{
	}

	void InfinitRightUndoAction::AddObjectChangeValue(const IRUUID& objectUuid, const IRJson& oldValue, const IRJson& newValue)
	{
		IR_INFO("Add object change value for object " + objectUuid.ToString() + "! OldValue: " + oldValue.dump() + "\nNewValue: " + newValue.dump());
		fValues.push_back(new InfinitRightUndoValueChange(objectUuid, oldValue, newValue));
	}

	void InfinitRightUndoAction::AddObjectCreateValue(const IRUUID& objectUuid, const IRJson& object)
	{
		IR_INFO("Add objectcreate change for object " + objectUuid.ToString() + "! Object: " + object.dump());
		fValues.push_back(new InfinitRightUndoValueCreate(objectUuid, object));
	}

	void InfinitRightUndoAction::AddObjectDeleteValue(const IRUUID& objectUuid, const IRJson& object)
	{
		IR_INFO("Add object delete change for object " + objectUuid.ToString() + "! Object: " + object.dump());
		fValues.push_back(new InfinitRightUndoValueDelete(objectUuid, object));
	}

}
