#include "prefix.h"

namespace IR {

	InfinitRightUndoAction::InfinitRightUndoAction(const IRString& name, bool isUndoAction)
		: fName(name), fIsUndoAction(isUndoAction)
	{
		InfinitRightApp::gApp().GetUndoManager().StartUndo(this);
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
		InfinitRightApp::gApp().GetUndoManager().EndUndo(this);
		InfinitRightApp::gApp().StartChangeCallback(callbackJson);
	}


	const IRVector<InfinitRightUndoValue*>& InfinitRightUndoAction::GetUndoValueList() const
	{
		return fValues;
	}

	const IRString& InfinitRightUndoAction::GetName() const
	{
		return fName;
	}

	bool InfinitRightUndoAction::IsUndoAction() const
	{
		return fIsUndoAction;
	}

	void InfinitRightUndoAction::AddObjectChangeValue(InfinitRightObject* object, const IRJson& oldValue, const IRJson& newValue)
	{
		IR_INFO("Add object change value for object " + object->GetUuid().ToString() + "! OldValue: " + oldValue.dump() + "\nNewValue: " + newValue.dump());
		fValues.push_back(new InfinitRightUndoValueChange(object->GetUuid(), oldValue, newValue, object->GetObjectSuperId()));
	}

	void InfinitRightUndoAction::AddObjectCreateValue(InfinitRightObject* object, const IRJson& js_obj)
	{
		IR_INFO("Add objectcreate change for object " + object->GetUuid().ToString() + "! Object: " + js_obj.dump());
		fValues.push_back(new InfinitRightUndoValueCreate(object->GetUuid(), js_obj, object->GetObjectSuperId()));
	}

	void InfinitRightUndoAction::AddObjectDeleteValue(InfinitRightObject* object, const IRJson& js_obj)
	{
		IR_INFO("Add object delete change for object " + object->GetUuid().ToString() + "! Object: " + js_obj.dump());
		fValues.push_back(new InfinitRightUndoValueDelete(object->GetUuid(), js_obj, object->GetObjectSuperId()));
	}


	InfinitRightUndoActionStorage::InfinitRightUndoActionStorage(InfinitRightUndoAction* action)
	{
		for (InfinitRightUndoValue* undoValue : action->GetUndoValueList())
		{
			fValues.push_back(undoValue);
		}
	}

	InfinitRightUndoActionStorage::~InfinitRightUndoActionStorage()
	{
		for (InfinitRightUndoValue* undoValue : fValues)
		{
			delete undoValue;
		}
		fValues.clear();
	}

	const IRVector<InfinitRightUndoValue*> InfinitRightUndoActionStorage::GetUndoValues()
	{
		return fValues;
	}
}
