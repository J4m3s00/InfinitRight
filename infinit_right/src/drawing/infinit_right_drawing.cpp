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

	InfinitRightObject* InfinitRightDrawing::CreateNewObject(InfinitRightObject* object)
	{
		InfinitRightUndoAction* currentUndoAction = InfinitRightApp::gApp().GetUndoManager().GetActiveAction();
		fObjects[object->GetUuid()] = object;
		IRJson objectJson = IRJson::object();
		object->SetJs(objectJson);
		if (currentUndoAction)
		{
			currentUndoAction->AddObjectCreateValue(object->GetUuid(), objectJson);
		}
		//Handle create?
		return object;
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