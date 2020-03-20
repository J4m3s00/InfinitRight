#include "prefix.h"

namespace IR {

	InfinitRightDrawing::InfinitRightDrawing(const IRString& name)
		: InfinitRightObject()
	{
		SetName(name);
	}

	InfinitRightDrawing::~InfinitRightDrawing()
	{
		for (InfinitRightObject* object : fObjects) 
		{
			delete object;
		}
		fObjects.clear();
	}

	InfinitRightObject* InfinitRightDrawing::CreateNewObject(InfinitRightObject* object)
	{
		fObjects.push_back(object);
		//Handle create?
		return object;
	}

	void InfinitRightDrawing::DeleteObject(const IRUUID& uuid)
	{
		for (size_t i = 0; i < fObjects.size(); i++)
		{
			if (fObjects[i]->GetUuid() == uuid)
			{
				//Handle delete
				delete fObjects[i];
				fObjects.erase(fObjects.begin() + i);
				break;
			}
		}
	}

	InfinitRightObject* InfinitRightDrawing::GetObjectByUuid(const IRUUID& uuid)
	{
		for (size_t i = 0; i < fObjects.size(); i++)
		{
			if (fObjects[i]->GetUuid() == uuid)
			{
				return fObjects[i];
			}
		}
	}

}