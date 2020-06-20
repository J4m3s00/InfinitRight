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

	InfinitRightObject* InfinitRightDrawing::CreateNewObject(const IRString& objectType, InfinitRightObject* parent, const IRUUID& uuid)
	{
		InfinitRightUndoAction* currentUndoAction = InfinitRightApp::gApp().GetUndoManager().GetActiveAction();
		InfinitRightObject* newObject = InfinitRightApp::new_object(objectType, uuid);
		fObjects[uuid] = newObject;

		IRJson objectJson = IRJson::object();
		newObject->SetJs(objectJson);
		if (currentUndoAction)
		{
			currentUndoAction->AddObjectCreateValue(uuid, objectJson);
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
				undoAction->AddObjectDeleteValue(uuid, objectJson);
			}
			fObjects.erase(uuid);
		}
	}

	InfinitRightObject* InfinitRightDrawing::GetObjectByUuid(const IRUUID& uuid)
	{
		return fObjects[uuid];
	}


}