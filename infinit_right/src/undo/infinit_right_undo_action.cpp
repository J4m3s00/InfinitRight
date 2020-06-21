#include "prefix.h"

namespace IR {

	InfinitRightUndoAction::InfinitRightUndoAction(const IRString& name)
		: fName(name)
	{
		InfinitRightApp::gApp().GetUndoManager().SetActiveAction(this);
	}

	InfinitRightUndoAction::~InfinitRightUndoAction()
	{
		//End action
		//Deff between object types
		//	->  Diff between create / change / delete

		// Loop all values
		IRJson callbackJson = IRJson::object();
		for (InfinitRightUndoValue* undoValue : fValues)
		{
			undoValue->WriteCallbackJson(callbackJson);
		}
		InfinitRightApp::gApp().StartChangeCallback(callbackJson);
	}

	void InfinitRightUndoAction::AddObjectChangeValue(InfinitRightObject* object, const IRJson& oldValue, const IRJson& newValue)
	{
		IR_INFO("Add object change value for object " + object->GetUuid().ToString() + "! OldValue: " + oldValue.dump() + "\nNewValue: " + newValue.dump());
		fValues.push_back(new InfinitRightUndoValueChange(object->GetUuid(), oldValue, newValue, object->GetObjectId()));
	}

	void InfinitRightUndoAction::AddObjectCreateValue(InfinitRightObject* object, const IRJson& js_obj)
	{
		IR_INFO("Add objectcreate change for object " + object->GetUuid().ToString() + "! Object: " + js_obj.dump());
		fValues.push_back(new InfinitRightUndoValueCreate(object->GetUuid(), js_obj, object->GetObjectId()));
	}

	void InfinitRightUndoAction::AddObjectDeleteValue(InfinitRightObject* object, const IRJson& js_obj)
	{
		IR_INFO("Add object delete change for object " + object->GetUuid().ToString() + "! Object: " + js_obj.dump());
		fValues.push_back(new InfinitRightUndoValueDelete(object->GetUuid(), js_obj, object->GetObjectId()));
	}

}
