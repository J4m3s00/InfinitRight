#include "prefix.h"

namespace IR {

	InfinitRightDrawing::InfinitRightDrawing(const IRString& name)
		: InfinitRightObject()
	{
		SetName(name);
	}

	InfinitRightDrawing::~InfinitRightDrawing()
	{
		for (auto& object : fObjects) 
		{
			delete object.second;
		}
		fObjects.clear();
	}

	InfinitRightObject* InfinitRightDrawing::CreateNewObject(u32 objectType, InfinitRightObject* parent, const IRUUID& uuid)
	{
		InfinitRightUndoAction* currentUndoAction = InfinitRightApp::gApp().GetUndoManager().GetActiveAction();
		InfinitRightObject* newObject = InfinitRightApp::new_object(objectType, uuid);
		fObjects[uuid] = newObject;

		IRJson objectJson = IRJson::object();
		newObject->SetJs(objectJson);
		if (currentUndoAction)
		{
			currentUndoAction->AddObjectCreateValue(newObject, objectJson);
		}
		return newObject;
	}

	void InfinitRightDrawing::DeleteObject(const IRUUID& uuid)
	{
		InfinitRightUndoAction* undoAction = InfinitRightApp::gApp().GetUndoManager().GetActiveAction();
		InfinitRightObject* object = GetObjectByUuid(uuid);
		IRJson objectJson = IRJson::object();
		if (object)
		{
			object->SetJs(objectJson);
			if (undoAction)
			{
				undoAction->AddObjectDeleteValue(object, objectJson);
			}
			fObjects.erase(uuid);
		}
		delete object;
	}

	InfinitRightObject* InfinitRightDrawing::GetObjectByUuid(const IRUUID& uuid)
	{
		return fObjects[uuid];
	}


}